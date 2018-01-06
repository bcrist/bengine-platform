#include "pch.hpp"
#include "window_params.hpp"

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
WindowParams::WindowParams()
   : size_(640, 480),
     aspect_bounds_(make_extents_from_min_max(9.f / 16.f, 25.f / 9.f)),
     monitor_index_(0),
     gamma_exponent_(0),
     v_sync_(VSyncMode::none),
     refresh_rate_(0),
     color_bits_(8, 8, 8, 0),
     depth_stencil_bits_(24, 0),
     msaa_(0),
     context_version_major_(1),
     context_version_minor_(0),
     profile_(ContextProfileType::any) { }

//////////////////////////////////////////////////////////////////////////////
bool WindowParams::flag(WindowFlag f) const {
   return flags_[static_cast<std::size_t>(f)];
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::flag(WindowFlag f, bool v) {
   flags_[static_cast<std::size_t>(f)] = v;

   if (v) {
      switch (f) {
         case WindowFlag::resizable:
            clear_flag_(WindowFlag::fullscreen);
            clear_flag_(WindowFlag::monitor_exclusive);
            clear_flag_(WindowFlag::custom_gamma);
            monitor_index_ = 0;
            break;

         case WindowFlag::transparent:
            clear_flag_(WindowFlag::fullscreen);
            clear_flag_(WindowFlag::monitor_exclusive);
            clear_flag_(WindowFlag::custom_gamma);
            monitor_index_ = 0;
            break;

         case WindowFlag::fullscreen:
            clear_flag_(WindowFlag::resizable);
            clear_flag_(WindowFlag::transparent);
            set_flag_(WindowFlag::undecorated);
            clear_flag_(WindowFlag::system_positioned);
            clear_flag_(WindowFlag::centered);
            break;

         case WindowFlag::custom_gamma:
         case WindowFlag::monitor_exclusive:
            clear_flag_(WindowFlag::resizable);
            clear_flag_(WindowFlag::transparent);
            set_flag_(WindowFlag::undecorated);
            set_flag_(WindowFlag::fullscreen);
            clear_flag_(WindowFlag::system_positioned);
            clear_flag_(WindowFlag::centered);
            break;

         case WindowFlag::system_positioned:
            clear_flag_(WindowFlag::fullscreen);
            clear_flag_(WindowFlag::monitor_exclusive);
            clear_flag_(WindowFlag::custom_gamma);
            clear_flag_(WindowFlag::centered);
            break;

         case WindowFlag::centered:
            clear_flag_(WindowFlag::fullscreen);
            clear_flag_(WindowFlag::monitor_exclusive);
            clear_flag_(WindowFlag::custom_gamma);
            clear_flag_(WindowFlag::system_positioned);
            break;

         default:
            break;
      }
   } else {
      switch (f) {
         case WindowFlag::undecorated:
            clear_flag_(WindowFlag::fullscreen);
            clear_flag_(WindowFlag::monitor_exclusive);
            clear_flag_(WindowFlag::custom_gamma);
            break;

         case WindowFlag::fullscreen:
            clear_flag_(WindowFlag::monitor_exclusive);
            clear_flag_(WindowFlag::custom_gamma);
            break;

         default:
            break;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
uvec2 WindowParams::size() const {
   return size_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::size(uvec2 v) {
   size_ = v;
}

//////////////////////////////////////////////////////////////////////////////
ibox WindowParams::size_bounds() const {
   return size_bounds_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::size_bounds(ibox v) {
   size_bounds_ = v;
}

//////////////////////////////////////////////////////////////////////////////
range WindowParams::aspect_bounds() const {
   return aspect_bounds_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::aspect_bounds(range v) {
   aspect_bounds_ = v;
}

//////////////////////////////////////////////////////////////////////////////
ivec2 WindowParams::position() const {
   return position_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::position(ivec2 v) {
   position_ = v;
}

//////////////////////////////////////////////////////////////////////////////
U32 WindowParams::monitor_index() const {
   return monitor_index_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::monitor_index(U32 v) {
   monitor_index_ = v;
}

//////////////////////////////////////////////////////////////////////////////
VSyncMode WindowParams::v_sync() const {
   return v_sync_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::v_sync(VSyncMode v) {
   v_sync_ = v;
}

//////////////////////////////////////////////////////////////////////////////
U8 WindowParams::refresh_rate() const {
   return refresh_rate_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::refresh_rate(U8 v) {
   refresh_rate_ = v;
}

//////////////////////////////////////////////////////////////////////////////
glm::u8vec4 WindowParams::color_bits() const {
   return color_bits_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::color_bits(glm::u8vec4 v) {
   color_bits_ = v;
}

//////////////////////////////////////////////////////////////////////////////
glm::u8vec2 WindowParams::depth_stencil_bits() const {
   return depth_stencil_bits_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::depth_stencil_bits(glm::u8vec2 v) {
   depth_stencil_bits_ = v;
}

//////////////////////////////////////////////////////////////////////////////
U8 WindowParams::msaa() const {
   return msaa_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::msaa(U8 v) {
   msaa_ = v;
}

//////////////////////////////////////////////////////////////////////////////
F32 WindowParams::gamma_exponent() const {
   return gamma_exponent_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::gamma_exponent(F32 v) {
   gamma_exponent_ = v;
}

//////////////////////////////////////////////////////////////////////////////
U8 WindowParams::context_version_major() const {
   return context_version_major_;
}

//////////////////////////////////////////////////////////////////////////////
U8 WindowParams::context_version_minor() const {
   return context_version_minor_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::context_version_major(U8 v) {
   if (v != context_version_major_) {
      context_version_major_ = v;

      if (context_version_major_ < 3 ||
         context_version_major_ == 3 && context_version_minor_ < 2) {
         profile(ContextProfileType::any);
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::context_version_minor(U8 v) {
   if (v != context_version_minor_) {
      context_version_minor_ = v;

      if (context_version_major_ < 3 ||
         context_version_major_ == 3 && context_version_minor_ < 2) {
         profile(ContextProfileType::any);
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::context_version(U8 major, U8 minor) {
   if (major != context_version_major_ || minor != context_version_minor_) {
      context_version_major_ = major;
      context_version_minor_ = minor;

      if (context_version_major_ < 3 ||
         context_version_major_ == 3 && context_version_minor_ < 2) {
         profile(ContextProfileType::any);
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
ContextProfileType WindowParams::profile() const {
   return profile_;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::profile(ContextProfileType v) {
   if (v != profile_) {
      profile_ = v;

      if (profile_ != ContextProfileType::any) {
         if (context_version_major_ < 3 ||
            context_version_major_ == 3 && context_version_minor_ < 2) {
            context_version(3, 2);
         }
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::clear_flag_(WindowFlag f) {
   flags_[static_cast<std::size_t>(f)] = false;
}

//////////////////////////////////////////////////////////////////////////////
void WindowParams::set_flag_(WindowFlag f) {
   flags_[static_cast<std::size_t>(f)] = true;
}

} // be::platform
