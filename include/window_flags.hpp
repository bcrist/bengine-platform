#pragma once
#ifndef BE_PLATFORM_WINDOW_FLAGS_HPP_
#define BE_PLATFORM_WINDOW_FLAGS_HPP_

#include <be/core/enum_traits.hpp>

/*!! include 'window_flags' !! 66 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
enum class WindowFlag : U8 {
   resizable = 0,
   undecorated,
   transparent,
   fullscreen,
   monitor_exclusive,
   system_positioned,
   centered,
   srgb_capable,
   custom_gamma,
   debug_context,
   forward_compatible_context
};

bool is_valid(WindowFlag constant) noexcept;
const char* window_flag_name(WindowFlag constant) noexcept;
std::array<const WindowFlag, 11> window_flag_values() noexcept;
std::ostream& operator<<(std::ostream& os, WindowFlag constant);

} // be::platform

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::platform::WindowFlag> {
   using type = ::be::platform::WindowFlag;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 11;

   static bool is_valid(type value) {
      return ::be::platform::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::platform::window_flag_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::platform::WindowFlag::resizable,
         ::be::platform::WindowFlag::undecorated,
         ::be::platform::WindowFlag::transparent,
         ::be::platform::WindowFlag::fullscreen,
         ::be::platform::WindowFlag::monitor_exclusive,
         ::be::platform::WindowFlag::system_positioned,
         ::be::platform::WindowFlag::centered,
         ::be::platform::WindowFlag::srgb_capable,
         ::be::platform::WindowFlag::custom_gamma,
         ::be::platform::WindowFlag::debug_context,
         ::be::platform::WindowFlag::forward_compatible_context,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
