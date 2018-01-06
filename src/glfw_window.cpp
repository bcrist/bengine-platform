#include "pch.hpp"
#include "glfw_window.hpp"

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
GlfwWindow::GlfwWindow()
   : wnd_(nullptr) { }

//////////////////////////////////////////////////////////////////////////////
GlfwWindow::GlfwWindow(const WindowParams& params) {
   BE_ASSERT_MAIN_THREAD();
   uvec2 size = params.size();
   ivec2 position = params.position();
   U32 refresh_rate = params.refresh_rate();

   if (params.flag(WindowFlag::monitor_exclusive)) {

   } else {
      refresh_rate = 0;
   }



   //GLFWmonitor* monitor = nullptr;
   //if (params.flag(WindowFlag::fullscreen)) {
   //   if (params.monitor_index() > 0) {
   //      int monitor_count;
   //      GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
   //      if (params.monitor_index() <= monitor_count) {
   //         monitor = monitors[params.monitor_index() - 1];
   //      }
   //   } else {
   //      monitor = glfwGetPrimaryMonitor();
   //   }

   //   if (!params.flag(WindowFlag::monitor_exclusive)) {
   //      if (monitor) {
   //         size = monitor
   //   }

   //} else if (params.flag(WindowFlag::centered)) {
   //   if (params.monitor_index() > 0) {
   //      int monitor_count;
   //      GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
   //      if (params.monitor_index() <= monitor_count) {
   //         monitor = monitors[params.monitor_index() - 1];
   //      }
   //   } else if (position != ivec2()) {


   //   } else {
   //      monitor = glfwGetPrimaryMonitor();
   //   }

   //   if (monitor) {

   //   }

   //   monitor = nullptr;
   //} else if (params.flag(WindowFlag::system_positioned)) {

   //} else {
   //}
   //   

   //   ivec2 center = window_params.position + window_params.size / 2;

   //   int monitor_count;
   //   GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
   //   
   //   for (int i = 0; i < monitor_count; ++i)
   //   {
   //      GLFWmonitor* mon = monitors[i];
   //      ivec2 offset;
   //      glfwGetMonitorPos(mon, &offset.x, &offset.y);
   //      const GLFWvidmode* mode = glfwGetVideoMode(mon);

   //      if (center.x >= offset.x && center.x < offset.x + mode->width &&
   //          center.y >= offset.y && center.y < offset.y + mode->height)
   //      {
   //         monitor = mon;
   //         break;
   //      }
   //   }
   //}

   //if (!monitor)
   //   monitor = glfwGetPrimaryMonitor();

   //const GLFWvidmode* monitor_mode = glfwGetVideoMode(monitor);

   //if (fullscreen_windowed)
   //{
   //   width = monitor_mode->width;
   //   height = monitor_mode->height;

   //   glfwGetMonitorPos(monitor, &position.x, &position.y);

   //   color_bits.r = monitor_mode->redBits;
   //   color_bits.g = monitor_mode->greenBits;
   //   color_bits.b = monitor_mode->blueBits;
   //}

   //// if not fullscreen exclusive, we don't provide monitor
   //if (!fullscreen_exclusive)
   //{
   //   monitor = nullptr;
   //   refresh_rate = 0;
   //}

   //glfwDefaultWindowHints();
   //glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

   //glfwWindowHint(GLFW_DECORATED, undecorated ? GL_FALSE : GL_TRUE);
   //glfwWindowHint(GLFW_RESIZABLE, fixed_size ? GL_FALSE : GL_TRUE);

   //glfwWindowHint(GLFW_REFRESH_RATE, refresh_rate);
   //glfwWindowHint(GLFW_SRGB_CAPABLE, window_params.srgb_capable ? GL_TRUE : GL_FALSE);
   //glfwWindowHint(GLFW_RED_BITS, color_bits.r);
   //glfwWindowHint(GLFW_GREEN_BITS, color_bits.g);
   //glfwWindowHint(GLFW_BLUE_BITS, color_bits.b);
   //glfwWindowHint(GLFW_ALPHA_BITS, window_params.alpha_bits);
   //glfwWindowHint(GLFW_DEPTH_BITS, window_params.depth_bits);
   //glfwWindowHint(GLFW_STENCIL_BITS, window_params.stencil_bits);
   //glfwWindowHint(GLFW_SAMPLES, window_params.msaa_level);

   //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window_params.context_version_major);
   //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window_params.context_version_minor);
   //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, window_params.forward_compatible_context ? GL_TRUE : GL_FALSE);
   //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, window_params.debug_context ? GL_TRUE : GL_FALSE);

   //switch (window_params.context_profile_type)
   //{
   //   case WindowParams::ContextProfileType::core:
   //      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   //      break;

   //   case WindowParams::ContextProfileType::compatability:
   //      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
   //      break;

   //   default:
   //      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
   //      break;
   //}

   //glfw_window_ = glfwCreateWindow(width, height, "bengine", monitor, nullptr);

   //if (!glfw_window_)
   //   throw std::runtime_error("Failed to create window!");

   //if (fullscreen_exclusive)
   //{
   //   if (window_params.use_custom_gamma)
   //      glfwSetGamma(monitor, window_params.custom_gamma);
   //}
   //else if (fullscreen_windowed || !window_params.system_positioned)
   //{
   //   glfwSetWindowPos(glfw_window_, position.x, position.y);
   //}
}

//////////////////////////////////////////////////////////////////////////////
GlfwWindow::GlfwWindow(GlfwWindow&& other)
   : wnd_(nullptr) {
   using std::swap;
   swap(wnd_, other.wnd_);
}

//////////////////////////////////////////////////////////////////////////////
GlfwWindow& GlfwWindow::operator=(GlfwWindow&& other) {
   using std::swap;
   swap(wnd_, other.wnd_);
   return *this;
}

//////////////////////////////////////////////////////////////////////////////
GlfwWindow::~GlfwWindow() {
   if (wnd_) {
      BE_ASSERT_MAIN_THREAD();
      glfwDestroyWindow(wnd_);
      wnd_ = nullptr;
   }
}

//////////////////////////////////////////////////////////////////////////////
const GLFWwindow* GlfwWindow::wnd() const {
   return wnd_;
}

//////////////////////////////////////////////////////////////////////////////
GLFWwindow* GlfwWindow::wnd() {
   return wnd_;
}

} // be::platform
