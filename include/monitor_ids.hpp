#pragma once
#ifndef BE_PLATFORM_MONITOR_IDS_HPP_
#define BE_PLATFORM_MONITOR_IDS_HPP_

#include <be/core/id.hpp>
#include <unordered_map>

namespace be::platform {

class Monitor;

class MonitorIds final {
public:
   using iterator = std::unordered_map<Id, S>::const_iterator;

   MonitorIds() = default;
   template <typename I>
   MonitorIds(I begin, I end)
      : ids_(begin, end) { }

   bool empty() const {
      return ids_.empty();
   }

   std::size_t size() const {
      return ids_.size();
   }

   iterator begin() const {
      return ids_.begin();
   }

   iterator end() const {
      return ids_.end();
   }

   SV operator[](Id type) const {
      auto it = ids_.find(type);
      if (it != ids_.end()) {
         return it->second;
      } else {
         return SV();
      }
   }

private:
   std::unordered_map<Id, S> ids_;
};

} // be::platform

#endif
