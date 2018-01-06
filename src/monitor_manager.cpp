#include "pch.hpp"
#include "monitor_manager.hpp"
#include "monitor.hpp"
#include "service_monitor_manager.hpp"
#include "native/native_monitor.hpp"
#include <be/core/service_helpers.hpp>

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
MonitorManager::~MonitorManager() {
   glfwSetMonitorCallback(nullptr);
}

//////////////////////////////////////////////////////////////////////////////
Monitor& MonitorManager::from_glfw(GLFWmonitor* glfw) {
   auto it = glfw_map_.find(glfw);
   if (it != glfw_map_.end()) {
      return *(it->second);
   } else {
      return *(monitors_.front());
   }
}

//////////////////////////////////////////////////////////////////////////////
const Monitor& MonitorManager::from_glfw(GLFWmonitor* glfw) const {
   auto it = glfw_map_.find(glfw);
   if (it != glfw_map_.end()) {
      return *(it->second);
   } else {
      return *(monitors_.front());
   }
}

//////////////////////////////////////////////////////////////////////////////
Monitor& MonitorManager::from_virtual_position(ivec2 virtual_position) {
   for (auto monitor : active_monitors_) {
      if (monitor->virtual_bounds().contains(virtual_position)) {
         return *monitor;
      }
   }

   return *(monitors_.front());
}

//////////////////////////////////////////////////////////////////////////////
const Monitor& MonitorManager::from_virtual_position(ivec2 virtual_position) const {
   for (auto monitor : active_monitors_) {
      if (monitor->virtual_bounds().contains(virtual_position)) {
         return *monitor;
      }
   }

   return *(monitors_.front());
}

//////////////////////////////////////////////////////////////////////////////
Monitor& MonitorManager::primary() {
   return *primary_monitor_;
}

//////////////////////////////////////////////////////////////////////////////
const Monitor& MonitorManager::primary() const {
   return *primary_monitor_;
}

//////////////////////////////////////////////////////////////////////////////
bool MonitorManager::empty() const {
   return active_monitors_.empty();
}

//////////////////////////////////////////////////////////////////////////////
std::size_t MonitorManager::size() const {
   return active_monitors_.size();
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::iterator MonitorManager::begin() {
   return boost::make_indirect_iterator(active_monitors_.begin());
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::const_iterator MonitorManager::begin() const {
   return boost::make_indirect_iterator(active_monitors_.cbegin());
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::const_iterator MonitorManager::cbegin() const {
   return boost::make_indirect_iterator(active_monitors_.cbegin());
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::iterator MonitorManager::end() {
   return boost::make_indirect_iterator(active_monitors_.end());
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::const_iterator MonitorManager::end() const {
   return boost::make_indirect_iterator(active_monitors_.cend());
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::const_iterator MonitorManager::cend() const {
   return boost::make_indirect_iterator(active_monitors_.cend());
}

//////////////////////////////////////////////////////////////////////////////
Monitor& MonitorManager::operator[](std::size_t index) {
   return *(active_monitors_[index]);
}

//////////////////////////////////////////////////////////////////////////////
const Monitor& MonitorManager::operator[](std::size_t index) const {
   return *(active_monitors_[index]);
}

//////////////////////////////////////////////////////////////////////////////
MonitorManager::MonitorManager()
   : primary_monitor_(nullptr) {
   BE_ASSERT_MAIN_THREAD();

   detail::native_check_monitors();

   monitors_.push_back(std::unique_ptr<Monitor>(new Monitor(nullptr)));

   glfwSetMonitorCallback([](GLFWmonitor* monitor, int op) {
         BE_ASSERT_MAIN_THREAD();
         MonitorManager& mgr = service<MonitorManager>();

         detail::native_check_monitors();

         if (op == GLFW_CONNECTED) {
            auto it = mgr.glfw_map_.find(monitor);
            if (it != mgr.glfw_map_.end()) {
               it->second->disconnected_();
            }
            
            auto ptr = std::unique_ptr<Monitor>(new Monitor(monitor));
            Monitor* mon = ptr.get();
            mgr.monitors_.push_back(std::move(ptr));
            mgr.glfw_map_[monitor] = mon;
            mgr.configure_();

            // TODO EventDispatcher event
         } else if (op == GLFW_DISCONNECTED) {
            mgr.from_glfw(monitor).disconnected_();
            mgr.configure_();

            // TODO EventDispatcher event
         }
      });

   int count = 0;
   GLFWmonitor** monitors = glfwGetMonitors(&count);
   for (int i = 0; i < count; ++i) {
      GLFWmonitor* monitor = monitors[i];
      auto ptr = std::unique_ptr<Monitor>(new Monitor(monitor));
      Monitor* mon = ptr.get();
      monitors_.push_back(std::move(ptr));
      glfw_map_[monitor] = mon;
   }

   configure_();
}

//////////////////////////////////////////////////////////////////////////////
void MonitorManager::configure_() {
   GLFWmonitor* primary = glfwGetPrimaryMonitor();
   primary_monitor_ = &from_glfw(primary);

   active_monitors_.clear();
   int count = 0;
   GLFWmonitor** monitors = glfwGetMonitors(&count);
   for (int i = 0; i < count; ++i) {
      GLFWmonitor* monitor = monitors[i];
      active_monitors_.push_back(&from_glfw(monitor));
   }
   
   for (Monitor* monitor : active_monitors_) {
      monitor->current_mode(true);
   }
}

} // be::platform
