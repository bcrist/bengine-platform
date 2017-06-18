#pragma once
#ifndef BE_PLATFORM_VERSION_HPP_
#define BE_PLATFORM_VERSION_HPP_

#include <be/core/macros.hpp>

#define BE_PLATFORM_VERSION_MAJOR 0
#define BE_PLATFORM_VERSION_MINOR 1
#define BE_PLATFORM_VERSION_REV 3

/*!! include('common/version', 'be::platform') !! 6 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#define BE_PLATFORM_VERSION (BE_PLATFORM_VERSION_MAJOR * 100000 + BE_PLATFORM_VERSION_MINOR * 1000 + BE_PLATFORM_VERSION_REV)
#define BE_PLATFORM_VERSION_STRING "be::platform " BE_STRINGIFY(BE_PLATFORM_VERSION_MAJOR) "." BE_STRINGIFY(BE_PLATFORM_VERSION_MINOR) "." BE_STRINGIFY(BE_PLATFORM_VERSION_REV)

/* ######################### END OF GENERATED CODE ######################### */

#endif
