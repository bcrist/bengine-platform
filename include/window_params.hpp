#pragma once
#ifndef BE_PLATFORM_WINDOW_PARAMS_HPP_
#define BE_PLATFORM_WINDOW_PARAMS_HPP_

#include "window_flags.hpp"
#include "v_sync_mode.hpp"
#include "context_profile_type.hpp"
#include <be/core/glm.hpp>
#include <be/core/extents.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <bitset>

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
class WindowParams final {
public:
   WindowParams();

   bool flag(WindowFlag f) const;
   void flag(WindowFlag f, bool v);

   uvec2 size() const;
   void size(uvec2 v);

   ibox size_bounds() const;
   void size_bounds(ibox v);

   range aspect_bounds() const;
   void aspect_bounds(range v);

   ivec2 position() const;
   void position(ivec2 v);

   U32 monitor_index() const;
   void monitor_index(U32 v);

   VSyncMode v_sync() const;
   void v_sync(VSyncMode v);

   U8 refresh_rate() const;
   void refresh_rate(U8 v);

   glm::u8vec4 color_bits() const;
   void color_bits(glm::u8vec4 v);

   glm::u8vec2 depth_stencil_bits() const;
   void depth_stencil_bits(glm::u8vec2 v);

   U8 msaa() const;
   void msaa(U8 v);

   F32 gamma_exponent() const;
   void gamma_exponent(F32 v);

   U8 context_version_major() const;
   U8 context_version_minor() const;
   void context_version_major(U8 v);
   void context_version_minor(U8 v);
   void context_version(U8 major, U8 minor);

   ContextProfileType profile() const;
   void profile(ContextProfileType v);

private:
   void clear_flag_(WindowFlag f);
   void set_flag_(WindowFlag f);

   std::bitset<EnumTraits<WindowFlag>::count> flags_;
   uvec2 size_;
   ibox size_bounds_;
   range aspect_bounds_;
   ivec2 position_;
   U32 monitor_index_;
   F32 gamma_exponent_;
   VSyncMode v_sync_;
   U8 refresh_rate_;
   glm::u8vec4 color_bits_;
   glm::u8vec2 depth_stencil_bits_;
   U8 msaa_;
   U8 context_version_major_;
   U8 context_version_minor_;
   ContextProfileType profile_;
};

} // be::platform

#endif
