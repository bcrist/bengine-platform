#pragma once
#ifndef BE_PLATFORM_MONITOR_MODE_HPP_
#define BE_PLATFORM_MONITOR_MODE_HPP_

#include <be/core/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace be::platform {

struct MonitorMode {
   uvec2 dim;
   uvec3 color_bits;
   U32 refresh_rate;
};

} // be::platform

#endif
