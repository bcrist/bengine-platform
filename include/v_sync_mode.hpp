#pragma once
#ifndef BE_PLATFORM_V_SYNC_MODE_HPP_
#define BE_PLATFORM_V_SYNC_MODE_HPP_

#include <be/core/enum_traits.hpp>

/*!! include 'v_sync_mode' !! 50 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
enum class VSyncMode : U8 {
   none = 0,
   wait_always,
   wait_if_early
};

bool is_valid(VSyncMode constant) noexcept;
const char* v_sync_mode_name(VSyncMode constant) noexcept;
std::array<const VSyncMode, 3> v_sync_mode_values() noexcept;
std::ostream& operator<<(std::ostream& os, VSyncMode constant);

} // be::platform

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::platform::VSyncMode> {
   using type = ::be::platform::VSyncMode;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 3;

   static bool is_valid(type value) {
      return ::be::platform::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::platform::v_sync_mode_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::platform::VSyncMode::none,
         ::be::platform::VSyncMode::wait_always,
         ::be::platform::VSyncMode::wait_if_early,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
