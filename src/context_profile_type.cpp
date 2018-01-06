#include "pch.hpp"
#include "context_profile_type.hpp"

/*!! include 'context_profile_type' !! 47 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(ContextProfileType constant) noexcept {
   switch (constant) {
      case ContextProfileType::any:
      case ContextProfileType::core:
      case ContextProfileType::compatibility:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* context_profile_type_name(ContextProfileType constant) noexcept {
   switch (constant) {
      case ContextProfileType::any:           return "any";
      case ContextProfileType::core:          return "core";
      case ContextProfileType::compatibility: return "compatibility";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const ContextProfileType, 3> context_profile_type_values() noexcept {
   return ::be::EnumTraits<ContextProfileType>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, ContextProfileType constant) {
   if (is_valid(constant)) {
      os << context_profile_type_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::platform


/* ######################### END OF GENERATED CODE ######################### */
