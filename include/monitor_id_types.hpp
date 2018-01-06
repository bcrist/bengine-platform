/*!! include('common/ids', { symbol_prefix = 'PLATFORM_MONITOR_ID_', value_prefix = 'be:platform:monitor:id:' }, {

   {'GLFW_NAME', 'glfw-name'},

   {'WIN32_ADAPTER_DEVICE_NAME',   'win32:adapter:device-name'},
   {'WIN32_ADAPTER_DEVICE_STRING', 'win32:adapter:device-string'},
   {'WIN32_ADAPTER_DEVICE_ID',     'win32:adapter:device-id'},
   {'WIN32_ADAPTER_REGISTRY_KEY',  'win32:adapter:registry-key'},

   {'WIN32_DISPLAY_DEVICE_NAME',         'win32:display:device-name'},
   {'WIN32_DISPLAY_DEVICE_STRING',       'win32:display:device-string'},
   {'WIN32_DISPLAY_DEVICE_ID',           'win32:display:device-id'},
   {'WIN32_DISPLAY_DEVICE_INTERFACE_ID', 'win32:display:device-interface-id'},
   {'WIN32_DISPLAY_REGISTRY_KEY',        'win32:display:registry-key'},
   
   {'EDID_RAW_MFR_ID',    'edid:raw-mfr-id'},
   {'EDID_MFR_ID',        'edid:mfr-id'},
   {'EDID_PRODUCT_ID',    'edid:product-id'},
   {'EDID_SERIAL_NUMBER', 'edid:serial-number'},

}) !! 88 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#pragma once
#ifndef BE_PLATFORM_MONITOR_ID_TYPES_HPP_
#define BE_PLATFORM_MONITOR_ID_TYPES_HPP_

#include <be/core/id.hpp>

#define BEIDN_PLATFORM_MONITOR_ID_GLFW_NAME                         "be:platform:monitor:id:glfw-name"
#define  BEID_PLATFORM_MONITOR_ID_GLFW_NAME                         0xC9E16F794C2BBBD2
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_NAME         "be:platform:monitor:id:win32:adapter:device-name"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_NAME         0x211BFC757DA82BD0
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_STRING       "be:platform:monitor:id:win32:adapter:device-string"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_STRING       0xA11F5C14319EA86E
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_ID           "be:platform:monitor:id:win32:adapter:device-id"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_ID           0x2AE0482B7274C666
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_REGISTRY_KEY        "be:platform:monitor:id:win32:adapter:registry-key"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_ADAPTER_REGISTRY_KEY        0x64111C86E5882B0B
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_NAME         "be:platform:monitor:id:win32:display:device-name"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_NAME         0x6B1DCD3C971F5821
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_STRING       "be:platform:monitor:id:win32:display:device-string"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_STRING       0x867F12DBEC991053
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_ID           "be:platform:monitor:id:win32:display:device-id"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_ID           0x2EAF8C13CD6FC3D7
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_INTERFACE_ID "be:platform:monitor:id:win32:display:device-interface-id"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_INTERFACE_ID 0x228ADB832FE9FB69
#define BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_REGISTRY_KEY        "be:platform:monitor:id:win32:display:registry-key"
#define  BEID_PLATFORM_MONITOR_ID_WIN32_DISPLAY_REGISTRY_KEY        0x719B1407E447D850
#define BEIDN_PLATFORM_MONITOR_ID_EDID_RAW_MFR_ID                   "be:platform:monitor:id:edid:raw-mfr-id"
#define  BEID_PLATFORM_MONITOR_ID_EDID_RAW_MFR_ID                   0x8B2300783245F31A
#define BEIDN_PLATFORM_MONITOR_ID_EDID_MFR_ID                       "be:platform:monitor:id:edid:mfr-id"
#define  BEID_PLATFORM_MONITOR_ID_EDID_MFR_ID                       0x73C6522FA30642B3
#define BEIDN_PLATFORM_MONITOR_ID_EDID_PRODUCT_ID                   "be:platform:monitor:id:edid:product-id"
#define  BEID_PLATFORM_MONITOR_ID_EDID_PRODUCT_ID                   0x36CCFBFCA5289397
#define BEIDN_PLATFORM_MONITOR_ID_EDID_SERIAL_NUMBER                "be:platform:monitor:id:edid:serial-number"
#define  BEID_PLATFORM_MONITOR_ID_EDID_SERIAL_NUMBER                0x65C156396FA505F6

#ifdef BE_ID_EXTERNS

namespace be {
namespace ids {

extern const Id platform_monitor_id_glfw_name;
extern const Id platform_monitor_id_win32_adapter_device_name;
extern const Id platform_monitor_id_win32_adapter_device_string;
extern const Id platform_monitor_id_win32_adapter_device_id;
extern const Id platform_monitor_id_win32_adapter_registry_key;
extern const Id platform_monitor_id_win32_display_device_name;
extern const Id platform_monitor_id_win32_display_device_string;
extern const Id platform_monitor_id_win32_display_device_id;
extern const Id platform_monitor_id_win32_display_device_interface_id;
extern const Id platform_monitor_id_win32_display_registry_key;
extern const Id platform_monitor_id_edid_raw_mfr_id;
extern const Id platform_monitor_id_edid_mfr_id;
extern const Id platform_monitor_id_edid_product_id;
extern const Id platform_monitor_id_edid_serial_number;

} // be::ids
} // be

#endif
#endif
#ifdef BE_ID_STATICS

namespace be {
namespace ids {

const Id platform_monitor_id_glfw_name = Id(BEIDN_PLATFORM_MONITOR_ID_GLFW_NAME);
const Id platform_monitor_id_win32_adapter_device_name = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_NAME);
const Id platform_monitor_id_win32_adapter_device_string = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_STRING);
const Id platform_monitor_id_win32_adapter_device_id = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_DEVICE_ID);
const Id platform_monitor_id_win32_adapter_registry_key = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_ADAPTER_REGISTRY_KEY);
const Id platform_monitor_id_win32_display_device_name = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_NAME);
const Id platform_monitor_id_win32_display_device_string = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_STRING);
const Id platform_monitor_id_win32_display_device_id = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_ID);
const Id platform_monitor_id_win32_display_device_interface_id = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_DEVICE_INTERFACE_ID);
const Id platform_monitor_id_win32_display_registry_key = Id(BEIDN_PLATFORM_MONITOR_ID_WIN32_DISPLAY_REGISTRY_KEY);
const Id platform_monitor_id_edid_raw_mfr_id = Id(BEIDN_PLATFORM_MONITOR_ID_EDID_RAW_MFR_ID);
const Id platform_monitor_id_edid_mfr_id = Id(BEIDN_PLATFORM_MONITOR_ID_EDID_MFR_ID);
const Id platform_monitor_id_edid_product_id = Id(BEIDN_PLATFORM_MONITOR_ID_EDID_PRODUCT_ID);
const Id platform_monitor_id_edid_serial_number = Id(BEIDN_PLATFORM_MONITOR_ID_EDID_SERIAL_NUMBER);

} // be::ids
} // be

#endif

/* ######################### END OF GENERATED CODE ######################### */
