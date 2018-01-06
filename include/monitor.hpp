#pragma once
#ifndef BE_PLATFORM_MONITOR_HPP_
#define BE_PLATFORM_MONITOR_HPP_

#include "monitor_ids.hpp"
#include "monitor_modes.hpp"
#include "monitor_gamma.hpp"
#include <be/core/extents.hpp>
#include <glfw/glfw3.h>

namespace be::platform {

class MonitorManager;

//////////////////////////////////////////////////////////////////////////////
class Monitor final : Immovable {
   friend class MonitorManager;
public:
   explicit operator bool() const;
   GLFWmonitor* glfw();
   const GLFWmonitor* glfw() const;

   bool primary() const;

   const MonitorIds& ids() const;

   const MonitorModes& modes() const;
   const MonitorMode& canonical_mode() const;

   const MonitorMode& current_mode() const;
   const MonitorMode& current_mode(bool repoll);

   const MonitorGamma& gamma() const;
   const MonitorGamma& gamma(bool repoll);
   void gamma(const MonitorGamma& gamma);

   const irect& virtual_bounds() const;
   const irect& virtual_bounds(bool repoll);

   const irect& virtual_working_bounds() const;
   const irect& virtual_working_bounds(bool repoll);
   
   const F32& physical_dim_precision() const;
   const vec2& physical_dim_mm() const;
   void physical_dim_mm(vec2 new_dim);

   const F32& view_distance_mm() const;
   void view_distance_mm(F32 new_view_dist);

   const S& user_monitor_name() const;
   void user_monitor_name(S name);

private:
   Monitor(GLFWmonitor* glfw);
   void disconnected_();
   void repoll_mode_();

   mutable MonitorManager* mgr_;
   GLFWmonitor* glfw_;
   MonitorIds ids_;
   MonitorModes modes_;
   MonitorMode canonical_mode_;
   MonitorMode current_mode_;
   irect bounds_;
   irect working_bounds_;
   MonitorGamma gamma_;
   S user_monitor_name_;
   vec2 dim_mm_;
   F32 dim_precision_;
   F32 view_distance_mm_;
};

} // be::platform

#endif
