#include <be/core/native.hpp>
#ifdef BE_NATIVE_VC_WIN

#include "../native_monitor.hpp"
#include BE_NATIVE_CORE(vc_win_win32.hpp)
#include "native/vc_win/glfw.hpp"

#include "monitor_id_types.hpp"
#include <be/core/buf.hpp>
#include <be/core/alg.hpp>
#include <be/core/byte_order.hpp>
#include <be/util/utf16_widen_narrow.hpp>
#include <be/util/hex_encode.hpp>
#include <glm/vector_relational.hpp>
#include <glm/common.hpp>
#include <SetupApi.h>

namespace be::platform::detail {
namespace {

//////////////////////////////////////////////////////////////////////////////
struct AdapterInfo {
   U32 index;
   ::DISPLAY_DEVICEW dd = { sizeof(::DISPLAY_DEVICEW) };
   ::HMONITOR mon = nullptr;
};

//////////////////////////////////////////////////////////////////////////////
struct DisplayInfo {
   U32 index;
   ::DISPLAY_DEVICEW dd = { sizeof(::DISPLAY_DEVICEW) };
   S adapter_name;
   std::u16string device_interface_path;
};

//////////////////////////////////////////////////////////////////////////////
std::unordered_map<S, AdapterInfo>& get_adapters() {
   static std::unordered_map<S, AdapterInfo> map;
   return map;
}

//////////////////////////////////////////////////////////////////////////////
std::unordered_map<S, DisplayInfo>& get_displays() {
   static std::unordered_map<S, DisplayInfo> map;
   return map;
}

//////////////////////////////////////////////////////////////////////////////
struct EdidInfo {
   U64 edid_signature;
   U16 mfr_id;
   U16 product_id;
   U32 serial_number;
   U8 mfr_week;
   U8 mfr_year;
   U8 edid_version_major;
   U8 edid_version_minor;
   U8 video_input_params;
   U8 h_size_cm;
   U8 v_size_cm;
   U8 gamma;
   U8 supported_features;
   U8 chroma_rg_xy_lsb;
   U8 chroma_bw_xy_lsb;
   U8 chroma_r_x_msb;
   U8 chroma_r_y_msb;
   U8 chroma_g_x_msb;
   U8 chroma_g_y_msb;
   U8 chroma_b_x_msb;
   U8 chroma_b_y_msb;
   U8 chroma_w_x_msb;
   U8 chroma_w_y_msb;
   U8 established_timings[3];
   struct EdidStandardTiming {
      U8 xres;
      U8 aspect_ratio_vfreq;
   } standard_timings[8];
   struct EdidDetailedTimingDescriptor {
      U16 pixel_clock_10khz;
      U8 h_size_px_lsb;
      U8 h_blanking_px_lsb;
      U8 h_size_blanking_px_msb;
      U8 v_size_px_lsb;
      U8 v_blanking_px_lsb;
      U8 v_size_blanking_px_msb;
      U8 h_front_porch_lsb;
      U8 h_sync_pulse_lsb;
      U8 v_front_porch_sync_pulse_lsb;
      U8 front_porch_sync_pulse_msb;
      U8 h_size_mm_lsb;
      U8 v_size_mm_lsb;
      U8 size_mm_msb;
      U8 h_border_px;
      U8 v_border_px;
      U8 features;
   } detailed_timing_descriptor[4];
   U8 num_extensions;
   U8 checksum;
};

//////////////////////////////////////////////////////////////////////////////
constexpr ::GUID guid_devinterface_monitor = { 0xe6f07b5f, 0xee97, 0x4a90, 0xb0, 0x76, 0x33, 0xf5, 0x7b, 0xf4, 0xea, 0xa7 };

//////////////////////////////////////////////////////////////////////////////
bool get_edid(std::u16string_view device_interface_path, EdidInfo& edid) {
   ::HDEVINFO di = ::SetupDiGetClassDevsW(&guid_devinterface_monitor, nullptr, nullptr, DIGCF_DEVICEINTERFACE);
   if (!di || di == INVALID_HANDLE_VALUE) {
      return false;
   }

   bool result = false;
   Buf<UC> buffer = make_buf<UC>(sizeof(::SP_DEVICE_INTERFACE_DETAIL_DATA_W) + MAX_PATH * sizeof(::WCHAR));

   for (::DWORD i = 0; i >= 0; ++i) {
      ::SP_DEVICE_INTERFACE_DATA did = { sizeof(::SP_DEVICE_INTERFACE_DATA) };
      if (FALSE == ::SetupDiEnumDeviceInterfaces(di, nullptr, &guid_devinterface_monitor, i, &did)) {
         break;
      }
      
      std::memset(buffer.get(), 0, buffer.size());
      ::PSP_DEVICE_INTERFACE_DETAIL_DATA_W didd = reinterpret_cast<::PSP_DEVICE_INTERFACE_DETAIL_DATA_W>(buffer.get());
      didd->cbSize = sizeof(::SP_DEVICE_INTERFACE_DETAIL_DATA_W);
      ::DWORD size = static_cast<::DWORD>(buffer.size()) - sizeof(::SP_DEVICE_INTERFACE_DETAIL_DATA_W) + sizeof(didd->DevicePath);
      ::DWORD required_size = 0;

      if (FALSE == ::SetupDiGetDeviceInterfaceDetailW(di, &did, didd, size, &required_size, nullptr)) {
         if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError()) {
            buffer = make_buf<UC>(required_size);
            std::memset(buffer.get(), 0, buffer.size());
            didd = reinterpret_cast<::PSP_DEVICE_INTERFACE_DETAIL_DATA_W>(buffer.get());
            didd->cbSize = sizeof(::SP_DEVICE_INTERFACE_DETAIL_DATA_W);
            size = static_cast<::DWORD>(buffer.size()) - sizeof(::SP_DEVICE_INTERFACE_DETAIL_DATA_W) + sizeof(didd->DevicePath);
            
            if (FALSE == ::SetupDiGetDeviceInterfaceDetailW(di, &did, didd, size, nullptr, nullptr)) {
               break;
            }
         } else {
            break;
         }
      }

      std::u16string_view wdiddp(reinterpret_cast<char16_t*>(didd->DevicePath));

      if (std::equal(device_interface_path.begin(), device_interface_path.end(), wdiddp.begin(), wdiddp.end(),
         [](char16_t a, char16_t b) {
            return to_lower(a) == to_lower(b);
         })) {

         ::SP_DEVINFO_DATA dd { sizeof(::SP_DEVINFO_DATA) };
         if (FALSE == ::SetupDiEnumDeviceInfo(di, i, &dd)) {
            break;
         }

         ::HKEY registry_key = ::SetupDiOpenDevRegKey(di, &dd, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
         if (!registry_key || (registry_key == INVALID_HANDLE_VALUE)) {
            break;
         }

         ::DWORD registry_value_size = 1;
         ::RegQueryValueExW(registry_key, L"EDID", nullptr, nullptr, nullptr, &registry_value_size);
         Buf<UC> registry_value = make_buf<UC>(registry_value_size);
         if (ERROR_SUCCESS == ::RegQueryValueExW(registry_key, L"EDID", nullptr, nullptr, registry_value.get(), &registry_value_size)) {
            if (registry_value_size < sizeof(edid)) {
               std::memset(reinterpret_cast< UC* >(&edid) + registry_value_size, 0, sizeof(edid) - registry_value_size);
               std::memcpy(&edid, registry_value.get(), registry_value_size);
            } else {
               std::memcpy(&edid, registry_value.get(), sizeof(edid));
            }

            bo::static_to_host<bo::Big::value>(edid.mfr_id);
            bo::static_to_host<bo::Little::value>(edid.product_id);
            bo::static_to_host<bo::Little::value>(edid.serial_number);
            bo::static_to_host<bo::Little::value>(edid.detailed_timing_descriptor[0].pixel_clock_10khz);
            bo::static_to_host<bo::Little::value>(edid.detailed_timing_descriptor[1].pixel_clock_10khz);
            bo::static_to_host<bo::Little::value>(edid.detailed_timing_descriptor[2].pixel_clock_10khz);
            bo::static_to_host<bo::Little::value>(edid.detailed_timing_descriptor[3].pixel_clock_10khz);

            result = true;
         }
         ::RegCloseKey(registry_key);
      }
   }
   ::SetupDiDestroyDeviceInfoList(di);
   return result;
}

//////////////////////////////////////////////////////////////////////////////
::BOOL CALLBACK native_check_monitors_proc(::HMONITOR monitor, ::HDC dc, ::LPRECT rect, ::LPARAM data) {
   BE_IGNORE3(dc, rect, data);

   ::MONITORINFOEXW mi = { };
   mi.cbSize = sizeof(mi);
   if (FALSE == ::GetMonitorInfoW(monitor, &mi)) {
      return true;
   }

   S device_name = util::narrow(reinterpret_cast<const char16_t*>(mi.szDevice));

   auto& adapters = get_adapters();
   auto ait = adapters.find(device_name);
   if (ait != adapters.end()) {
      auto& adapter = ait->second;
      adapter.mon = monitor;
   }

   return true;
}

} // be::platform::detail::()

//////////////////////////////////////////////////////////////////////////////
void native_check_monitors() {
   BE_ASSERT_MAIN_THREAD();

   auto& adapters = get_adapters();
   auto& displays = get_displays();

   adapters.clear();
   displays.clear();

   for (::DWORD a = 0; a >= 0; ++a) {
      AdapterInfo adapter { a };

      if (!::EnumDisplayDevicesW(nullptr, a, &adapter.dd, 0)) {
         break;
      }
      
      if (!(adapter.dd.StateFlags & DISPLAY_DEVICE_ACTIVE)) {
         continue;
      }

      S adapter_name = util::narrow(reinterpret_cast<const char16_t*>(adapter.dd.DeviceName));
      adapters[adapter_name] = adapter;

      for (::DWORD d = 0; d >= 0; ++d) {
         DisplayInfo display { d };
         
         if (!::EnumDisplayDevicesW(adapter.dd.DeviceName, d, &display.dd, EDD_GET_DEVICE_INTERFACE_NAME)) {
            break;
         }

         display.adapter_name = adapter_name;
         display.device_interface_path = std::u16string(reinterpret_cast<const char16_t*>(display.dd.DeviceID));

         ::EnumDisplayDevicesW(adapter.dd.DeviceName, d, &display.dd, 0);

         S display_name = util::narrow(reinterpret_cast<const char16_t*>(display.dd.DeviceName));
         displays[display_name] = display;
      }
    }

   ::EnumDisplayMonitors(nullptr, nullptr, native_check_monitors_proc, 0);
}

//////////////////////////////////////////////////////////////////////////////
MonitorDetails get_monitor_details(GLFWmonitor* monitor, std::vector<std::pair<Id, S>>& ids) {
   MonitorDetails result = { vec2(), -1, -1 };
   BE_ASSERT_MAIN_THREAD();

   auto& adapters = get_adapters();
   auto ait = adapters.find(glfwGetWin32Adapter(monitor));
   if (ait != adapters.end()) {
      auto& adapter = ait->second;
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_adapter_device_name, util::narrow(reinterpret_cast<char16_t*>(adapter.dd.DeviceName))));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_adapter_device_string, util::narrow(reinterpret_cast<char16_t*>(adapter.dd.DeviceString))));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_adapter_device_id, util::narrow(reinterpret_cast<char16_t*>(adapter.dd.DeviceID))));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_adapter_registry_key, util::narrow(reinterpret_cast<char16_t*>(adapter.dd.DeviceKey))));

      if (adapter.mon) {
         ::MONITORINFO mi = { sizeof(::MONITORINFO) };
         if (FALSE != ::GetMonitorInfoW(adapter.mon, &mi)) {



         }
      }
   }

   auto& displays = get_displays();
   auto dit = displays.find(glfwGetWin32Monitor(monitor));
   if (dit != displays.end()) {
      auto& display = dit->second;
      
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_display_device_name, util::narrow(reinterpret_cast<char16_t*>(display.dd.DeviceName))));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_display_device_string, util::narrow(reinterpret_cast<char16_t*>(display.dd.DeviceString))));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_display_device_id, util::narrow(reinterpret_cast<char16_t*>(display.dd.DeviceID))));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_display_device_interface_id, util::narrow(display.device_interface_path)));
      ids.push_back(std::make_pair(ids::platform_monitor_id_win32_display_registry_key, util::narrow(reinterpret_cast<char16_t*>(display.dd.DeviceKey))));

      if (!display.device_interface_path.empty()) {
         EdidInfo edid = { };
         if (get_edid(display.device_interface_path, edid)) {
            
            U16 mfr_id = edid.mfr_id;
            bo::static_to_big<bo::Host::value>(mfr_id);
            ids.push_back(std::make_pair(ids::platform_monitor_id_edid_raw_mfr_id, util::hex_encode(Buf<U16>(&mfr_id, 1))));
            ids.push_back(std::make_pair(ids::platform_monitor_id_edid_mfr_id, S {
               static_cast<char>('@' + ((edid.mfr_id >> 10) & 0x1F)),
               static_cast<char>('@' + ((edid.mfr_id >> 5) & 0x1F)),
               static_cast<char>('@' + (edid.mfr_id & 0x1F))
            }));

            U16 product_id = edid.product_id;
            bo::static_to_big<bo::Host::value>(product_id);
            ids.push_back(std::make_pair(ids::platform_monitor_id_edid_product_id, util::hex_encode(Buf<U16>(&product_id, 1))));

            U32 serial = edid.serial_number;
            bo::static_to_big<bo::Host::value>(serial);
            ids.push_back(std::make_pair(ids::platform_monitor_id_edid_serial_number, util::hex_encode(Buf<U32>(&serial, 1))));

            if (edid.h_size_cm != 0 && edid.v_size_cm != 0) {
               result.physical_size_mm.x = 10.f * edid.h_size_cm;
               result.physical_size_mm.y = 10.f * edid.h_size_cm;
               result.physical_size_precision = 10.f;

               auto& desc0 = edid.detailed_timing_descriptor[0];

               vec2 desc0_size = vec2(
                  (desc0.h_size_mm_lsb & 0xFF) | ((desc0.size_mm_msb << 4) & 0xF00),
                  (desc0.v_size_mm_lsb & 0xFF) | ((desc0.size_mm_msb << 8) & 0xF00));

               if (glm::all(glm::lessThanEqual(glm::abs(desc0_size - result.physical_size_mm), vec2(10)))) {
                  result.physical_size_mm = desc0_size;
                  result.physical_size_precision = 1;
               }
            }
         }
      }
   }
   return result;
}

//////////////////////////////////////////////////////////////////////////////
MonitorDetails get_monitor_details(GLFWmonitor* monitor, const MonitorIds& ids) {
   BE_ASSERT_MAIN_THREAD();
   return MonitorDetails();
}

//////////////////////////////////////////////////////////////////////////////
MonitorBounds get_monitor_bounds(GLFWmonitor* monitor, const MonitorIds& ids, const MonitorMode& mode) {
   BE_ASSERT_MAIN_THREAD();
   return MonitorBounds();
}

} // be::platform::detail

#endif
