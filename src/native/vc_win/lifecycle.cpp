#include <be/core/native.hpp>
#ifdef BE_NATIVE_VC_WIN

#include "lifecycle.hpp"
#include "ids.hpp"
#include "service_monitor_manager.hpp"
#include "monitor_manager.hpp"
#include "service_window.hpp"
#include <be/core/logging.hpp>

#include BE_NATIVE_CORE(vc_win_win32.hpp)
#include "native/vc_win/glfw.hpp"

LRESULT CALLBACK window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   return glfwHandleWin32Message(hWnd, uMsg, wParam, lParam);
}

namespace be::platform {

void glfw_error(int error, const char* description) {
   be_error() << "GLFW Error!"
      & attr(ids::log_attr_code) << error
      & attr(ids::log_attr_description) << description
      | default_log();
}

bool platform_setup() {
   glfwSetErrorCallback(glfw_error);
   glfwSetDefaultWin32WindowProc(window_proc);

   if (!glfwInit()) {
      be_short_error() << "Failed to initialize GLFW!" | default_log();
      return false;
   }

   be_short_log(v::verbose) << "GLFW Initialized." | default_log();

   service<MonitorManager>();

   return true;
}

void platform_shutdown() {
   shutdown_service<Window>();
   shutdown_service<MonitorManager>();
   glfwTerminate();
}

} // be::platform

#endif
