#pragma once
#ifndef BE_PLATFORM_TEST_ENSURE_INIT_HPP_
#define BE_PLATFORM_TEST_ENSURE_INIT_HPP_

#include <be/core/lifecycle.hpp>
#include <be/platform/lifecycle.hpp>

namespace be {

///////////////////////////////////////////////////////////////////////////////
inline void ensure_init() {
   static CoreInitLifecycle cilc;
   static CoreLifecycle clc;
   static platform::PlatformLifecycle plc;
}

} // be

#endif
