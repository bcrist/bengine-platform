#include "pch.hpp"
#include "v_sync_mode.hpp"

/*!! include 'v_sync_mode' !! 47 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(VSyncMode constant) noexcept {
   switch (constant) {
      case VSyncMode::none:
      case VSyncMode::wait_always:
      case VSyncMode::wait_if_early:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* v_sync_mode_name(VSyncMode constant) noexcept {
   switch (constant) {
      case VSyncMode::none:          return "none";
      case VSyncMode::wait_always:   return "wait_always";
      case VSyncMode::wait_if_early: return "wait_if_early";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const VSyncMode, 3> v_sync_mode_values() noexcept {
   return ::be::EnumTraits<VSyncMode>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, VSyncMode constant) {
   if (is_valid(constant)) {
      os << v_sync_mode_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::platform


/* ######################### END OF GENERATED CODE ######################### */
