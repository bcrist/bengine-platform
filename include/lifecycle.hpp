#pragma once
#ifndef BE_PLATFORM_LIFECYCLE_HPP_
#define BE_PLATFORM_LIFECYCLE_HPP_

namespace be {

bool platform_setup();
void platform_shutdown();

struct PlatformLifecycle {
   PlatformLifecycle() { platform_setup(); }
   ~PlatformLifecycle() { platform_shutdown(); }
};

} // be

#endif

