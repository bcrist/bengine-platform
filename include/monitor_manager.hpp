#pragma once
#ifndef BE_PLATFORM_MONITOR_MANAGER_HPP_
#define BE_PLATFORM_MONITOR_MANAGER_HPP_

#include <be/core/glm.hpp>
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <vector>
#include <unordered_map>

namespace be {

template <typename>
struct ServiceFactory;

namespace platform {

class Monitor;

//////////////////////////////////////////////////////////////////////////////
class MonitorManager final : Immovable {
   friend struct ServiceFactory<MonitorManager>;
public:
   using iterator = boost::indirect_iterator<std::vector<Monitor*>::iterator>;
   using const_iterator = boost::indirect_iterator<std::vector<Monitor*>::const_iterator>;

   ~MonitorManager();

   Monitor& from_glfw(GLFWmonitor* glfw);
   const Monitor& from_glfw(GLFWmonitor* glfw) const;

   Monitor& from_virtual_position(ivec2 virtual_position);
   const Monitor& from_virtual_position(ivec2 virtual_position) const;

   Monitor& primary();
   const Monitor& primary() const;

   bool empty() const;
   std::size_t size() const;

   iterator begin();
   const_iterator begin() const;
   const_iterator cbegin() const;

   iterator end();
   const_iterator end() const;
   const_iterator cend() const;

   Monitor& operator[](std::size_t index);
   const Monitor& operator[](std::size_t index) const;

private:
   MonitorManager();
   void configure_();

   std::vector<std::unique_ptr<Monitor>> monitors_;
   std::unordered_map<GLFWmonitor*, Monitor*> glfw_map_;
   std::vector<Monitor*> active_monitors_;
   Monitor* primary_monitor_;
};

} // be::platform
} // be

#endif
