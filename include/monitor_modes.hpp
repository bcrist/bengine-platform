#pragma once
#ifndef BE_PLATFORM_MONITOR_MODES_HPP_
#define BE_PLATFORM_MONITOR_MODES_HPP_

#include "monitor_mode.hpp"
#include <vector>

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
class MonitorModes final {
public:
   using iterator = std::vector<MonitorMode>::const_iterator;

   MonitorModes() = default;

   template <typename I>
   MonitorModes(I begin, I end)
      : modes_(begin, end) { }
   
   bool empty() const {
      return modes_.empty();
   }

   std::size_t size() const {
      return modes_.size();
   }

   iterator begin() const {
      return modes_.begin();
   }

   iterator end() const {
      return modes_.end();
   }

   const MonitorMode& operator[](std::size_t index) const {
      return modes_[index];
   }

private:
   std::vector<MonitorMode> modes_;
};

} // be::platform

#endif
