#pragma once
#ifndef BE_PLATFORM_GLFW_WINDOW_HPP_
#define BE_PLATFORM_GLFW_WINDOW_HPP_

#include "window_params.hpp"
#include <glfw/glfw3.h>

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
class GlfwWindow final : Movable {
   GlfwWindow();
   GlfwWindow(const WindowParams& params);
   GlfwWindow(GlfwWindow&& other);
   GlfwWindow& operator=(GlfwWindow&& other);
   ~GlfwWindow();

   const GLFWwindow* wnd() const;
   GLFWwindow* wnd();

private:
   GLFWwindow* wnd_;
};

} // be::platform

#endif
