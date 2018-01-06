#include "pch.hpp"
#include "monitor.hpp"
#include "native/native_monitor.hpp"
#include "service_monitor_manager.hpp"
#include "monitor_id_types.hpp"
#include <be/core/service_helpers.hpp>

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
Monitor::operator bool() const {
   return !!glfw_;
}

//////////////////////////////////////////////////////////////////////////////
GLFWmonitor* Monitor::glfw() {
   return glfw_;
}

//////////////////////////////////////////////////////////////////////////////
const GLFWmonitor* Monitor::glfw() const {
   return glfw_;
}

//////////////////////////////////////////////////////////////////////////////
bool Monitor::primary() const {
   if (mgr_ == nullptr) {
      mgr_ = &service<MonitorManager>();
   }
   return this == &(mgr_->primary());
}

//////////////////////////////////////////////////////////////////////////////
const MonitorIds& Monitor::ids() const {
   return ids_;
}

//////////////////////////////////////////////////////////////////////////////
const MonitorModes& Monitor::modes() const {
   return modes_;
}

//////////////////////////////////////////////////////////////////////////////
const MonitorMode& Monitor::canonical_mode() const {
   return canonical_mode_;
}

//////////////////////////////////////////////////////////////////////////////
const MonitorMode& Monitor::current_mode() const {
   return current_mode_;
}

//////////////////////////////////////////////////////////////////////////////
const MonitorMode& Monitor::current_mode(bool repoll) {
   if (repoll) {
      repoll_mode_();
   }
   return current_mode_;
}

//////////////////////////////////////////////////////////////////////////////
const MonitorGamma& Monitor::gamma() const {
   return gamma_;
}

//////////////////////////////////////////////////////////////////////////////
const MonitorGamma& Monitor::gamma(bool repoll) {
   if (repoll && glfw_) {
      gamma_ = MonitorGamma(*glfwGetGammaRamp(glfw_));
   }
   return gamma_;
}

//////////////////////////////////////////////////////////////////////////////
void Monitor::gamma(const MonitorGamma& gamma) {
   gamma_ = gamma;
   if (glfw_) {
      GLFWgammaramp ramp = gamma_.glfw();
      glfwSetGammaRamp(glfw_, &ramp);
   }
}

//////////////////////////////////////////////////////////////////////////////
const irect& Monitor::virtual_bounds() const {
   return bounds_;
}

//////////////////////////////////////////////////////////////////////////////
const irect& Monitor::virtual_bounds(bool repoll) {
   if (repoll) {
      repoll_mode_();
   }
   return bounds_;
}

//////////////////////////////////////////////////////////////////////////////
const irect& Monitor::virtual_working_bounds() const {
   return working_bounds_;
}

//////////////////////////////////////////////////////////////////////////////
const irect& Monitor::virtual_working_bounds(bool repoll) {
   if (repoll) {
      repoll_mode_();
   }
   return working_bounds_;
}

//////////////////////////////////////////////////////////////////////////////
const F32& Monitor::physical_dim_precision() const {
   return dim_precision_;
}

//////////////////////////////////////////////////////////////////////////////
const vec2& Monitor::physical_dim_mm() const {
   return dim_mm_;
}

//////////////////////////////////////////////////////////////////////////////
void Monitor::physical_dim_mm(vec2 new_dim) {
   dim_mm_ = new_dim;
   dim_precision_ = 0;
}

//////////////////////////////////////////////////////////////////////////////
const F32& Monitor::view_distance_mm() const {
   return view_distance_mm_;
}

//////////////////////////////////////////////////////////////////////////////
void Monitor::view_distance_mm(F32 new_view_dist) {
   view_distance_mm_ = new_view_dist;
}

//////////////////////////////////////////////////////////////////////////////
const S& Monitor::user_monitor_name() const {
   return user_monitor_name_;
}

//////////////////////////////////////////////////////////////////////////////
void Monitor::user_monitor_name(S name) {
   user_monitor_name_ = std::move(name);
}

//////////////////////////////////////////////////////////////////////////////
Monitor::Monitor(GLFWmonitor* glfw)
   : mgr_(nullptr),
     glfw_(glfw),
     dim_precision_(-1.f),
     view_distance_mm_(0) {
   if (glfw_) {
      int count = 0;
      const GLFWvidmode* glfw_modes = glfwGetVideoModes(glfw_, &count);
      std::vector<MonitorMode> modes;
      for (int i = 0; i < count; ++i) {
         const GLFWvidmode& glfw_mode = glfw_modes[i];
         modes.push_back(MonitorMode {
               uvec2(glfw_mode.width, glfw_mode.height),
               uvec3(glfw_mode.redBits, glfw_mode.greenBits, glfw_mode.blueBits),
               U32(glfw_mode.refreshRate)
            });
      }
      modes_ = MonitorModes(modes.begin(), modes.end());

      std::vector<std::pair<Id, S>> ids;
      ids.push_back(std::make_pair(ids::platform_monitor_id_glfw_name, S(glfwGetMonitorName(glfw))));
      
      auto [ dim_mm_, dim_precision_, view_distance_mm_, canonical_mode_ ]
         = detail::get_monitor_details(glfw_, ids);

      ids_ = MonitorIds(ids.begin(), ids.end());

      if (view_distance_mm_ <= 0) {
         view_distance_mm_ = dim_mm_.x * 1.5f;
      }

      repoll_mode_();

      gamma_ = MonitorGamma(*glfwGetGammaRamp(glfw_));
   }
}

//////////////////////////////////////////////////////////////////////////////
void Monitor::disconnected_() {
   glfw_ = nullptr;
}

//////////////////////////////////////////////////////////////////////////////
void Monitor::repoll_mode_() {
   const GLFWvidmode* mode = glfwGetVideoMode(glfw_);
   current_mode_.dim.x = mode->width;
   current_mode_.dim.y = mode->height;
   current_mode_.refresh_rate = mode->refreshRate;
   current_mode_.color_bits.r = mode->redBits;
   current_mode_.color_bits.g = mode->greenBits;
   current_mode_.color_bits.b = mode->blueBits;

   auto [ bounds_, working_bounds_ ] = detail::get_monitor_bounds(glfw_, ids_, current_mode_);
}

} // be::platform
