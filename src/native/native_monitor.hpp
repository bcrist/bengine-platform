#pragma once
#ifndef BE_PLATFORM_NATIVE_MONITOR_HPP_
#define BE_PLATFORM_NATIVE_MONITOR_HPP_

#include "monitor_ids.hpp"
#include "monitor_mode.hpp"
#include <be/core/id.hpp>
#include <be/core/extents.hpp>
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
#include <vector>

namespace be::platform::detail {

struct MonitorDetails {
   vec2 physical_size_mm;
   F32 physical_size_precision;
   F32 viewing_distance_mm;
   MonitorMode canonical_mode;
};

struct MonitorBounds {
   irect full; ///< The full footprint of the screen
   irect work; ///< The area of the screen that a maximized window covers
};

void native_check_monitors();
MonitorDetails get_monitor_details(GLFWmonitor* monitor, std::vector<std::pair<Id, S>>& ids);
MonitorBounds get_monitor_bounds(GLFWmonitor* monitor, const MonitorIds& ids, const MonitorMode& current_mode);

} // be::platform::detail

#endif
