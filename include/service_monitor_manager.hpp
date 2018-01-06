#pragma once
#ifndef BE_PLATFORM_SERVICE_MONITOR_MANAGER_HPP_
#define BE_PLATFORM_SERVICE_MONITOR_MANAGER_HPP_

#include "monitor_manager.hpp"
#include <be/core/service.hpp>

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct SuppressUndefinedService<platform::MonitorManager> : True { };

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceName<platform::MonitorManager> {
   SV operator()() {
      using namespace std::string_view_literals;
      return "MonitorManager"sv;
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceFactory<platform::MonitorManager> {
   std::unique_ptr<platform::MonitorManager> operator()(Id) {
      return std::unique_ptr<platform::MonitorManager>(new platform::MonitorManager());
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceShutdown<platform::MonitorManager> {
   void operator()(std::unique_ptr<platform::MonitorManager>& service) {
      service.reset();
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceCleanup<platform::MonitorManager> {
   void operator()(std::unique_ptr<platform::MonitorManager>&) { }
};

} // be

#endif
