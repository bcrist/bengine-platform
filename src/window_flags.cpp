#include "pch.hpp"
#include "window_flags.hpp"

/*!! include 'window_flags' !! 63 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */

namespace be::platform {

///////////////////////////////////////////////////////////////////////////////
bool is_valid(WindowFlag constant) noexcept {
   switch (constant) {
      case WindowFlag::resizable:
      case WindowFlag::undecorated:
      case WindowFlag::transparent:
      case WindowFlag::fullscreen:
      case WindowFlag::monitor_exclusive:
      case WindowFlag::system_positioned:
      case WindowFlag::centered:
      case WindowFlag::srgb_capable:
      case WindowFlag::custom_gamma:
      case WindowFlag::debug_context:
      case WindowFlag::forward_compatible_context:
         return true;
      default:
         return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* window_flag_name(WindowFlag constant) noexcept {
   switch (constant) {
      case WindowFlag::resizable:                  return "resizable";
      case WindowFlag::undecorated:                return "undecorated";
      case WindowFlag::transparent:                return "transparent";
      case WindowFlag::fullscreen:                 return "fullscreen";
      case WindowFlag::monitor_exclusive:          return "monitor_exclusive";
      case WindowFlag::system_positioned:          return "system_positioned";
      case WindowFlag::centered:                   return "centered";
      case WindowFlag::srgb_capable:               return "srgb_capable";
      case WindowFlag::custom_gamma:               return "custom_gamma";
      case WindowFlag::debug_context:              return "debug_context";
      case WindowFlag::forward_compatible_context: return "forward_compatible_context";
      default:
         return "?";
   }
}

///////////////////////////////////////////////////////////////////////////////
std::array<const WindowFlag, 11> window_flag_values() noexcept {
   return ::be::EnumTraits<WindowFlag>::values<>();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, WindowFlag constant) {
   if (is_valid(constant)) {
      os << window_flag_name(constant);
   } else {
      os << static_cast<I64>(static_cast<U8>(constant));
   }
   return os;
}

} // be::platform


/* ######################### END OF GENERATED CODE ######################### */
