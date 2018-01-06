#pragma once
#ifndef BE_PLATFORM_CONTEXT_PROFILE_TYPE_HPP_
#define BE_PLATFORM_CONTEXT_PROFILE_TYPE_HPP_

#include <be/core/enum_traits.hpp>

/*!! include 'context_profile_type' !! 50 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
enum class ContextProfileType : U8 {
   any = 0,
   core,
   compatibility
};

bool is_valid(ContextProfileType constant) noexcept;
const char* context_profile_type_name(ContextProfileType constant) noexcept;
std::array<const ContextProfileType, 3> context_profile_type_values() noexcept;
std::ostream& operator<<(std::ostream& os, ContextProfileType constant);

} // be::platform

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct EnumTraits<::be::platform::ContextProfileType> {
   using type = ::be::platform::ContextProfileType;
   using underlying_type = typename std::underlying_type<type>::type;

   static constexpr std::size_t count = 3;

   static bool is_valid(type value) {
      return ::be::platform::is_valid(value);
   }

   static const char* name(type value) {
      return ::be::platform::context_profile_type_name(value);
   }

   template <typename C = std::array<const type, count>>
   static C values() {
      return {
         ::be::platform::ContextProfileType::any,
         ::be::platform::ContextProfileType::core,
         ::be::platform::ContextProfileType::compatibility,
      };
   }
};

} // be

/* ######################### END OF GENERATED CODE ######################### */

#endif
