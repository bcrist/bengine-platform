#ifdef BE_TEST

#include "ensure_init.hpp"
#include "service_monitor_manager.hpp"
#include "monitor_manager.hpp"
#include "monitor.hpp"
#include "monitor_ids.hpp"
#include <be/core/service_helpers.hpp>
#include <be/core/logging.hpp>
#include <catch/catch.hpp>

#define BE_CATCH_TAGS "[platform][platform:monitor]"

using namespace be;
using namespace be::platform;

TEST_CASE("MonitorManager", BE_CATCH_TAGS) {
   ensure_init();

   auto& monitors = service<MonitorManager>();

   for (auto& monitor : monitors) {
      for (auto& p : monitor.ids()) {
         be_short_warn() << S(get_id_name(p.first)) << ": " << S(p.second) || default_log();
      }
   }
}

#endif
