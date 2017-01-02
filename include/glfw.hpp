#pragma once
#ifndef BE_PLATFORM_GLFW_HPP_
#define BE_PLATFORM_GLFW_HPP_

#define BE_AUTOLINK_LIB "glfw"
#include <be/core/autolink.hpp>

#include "platform_autolink.hpp"

#include <GLFW/glfw3.h>
#if defined(APIENTRY) && !defined(_MINWINDEF_)
#  undef APIENTRY
#endif

#endif
