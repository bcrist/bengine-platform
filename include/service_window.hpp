#pragma once
#ifndef BE_PLATFORM_SERVICE_WINDOW_HPP_
#define BE_PLATFORM_SERVICE_WINDOW_HPP_

#include "window.hpp"
#include <be/core/service.hpp>

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct SuppressUndefinedService<platform::Window> : True { };

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceTraits<platform::Window> : ServiceTraits<> {
   using preemptive_default = no;
   using lazy_default = yes;
   using lazy_ids = yes;
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceName<platform::Window> {
   SV operator()() {
      using namespace std::string_view_literals;
      return "Window"sv;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceShutdown<platform::Window> {
   void operator()(std::unique_ptr<platform::Window>& service) {
      service.reset();
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceCleanup<platform::Window> {
   void operator()(std::unique_ptr<platform::Window>&) { }
};

} // be

#endif
