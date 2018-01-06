#pragma once
#ifndef BE_PLATFORM_MONITOR_GAMMA_HPP_
#define BE_PLATFORM_MONITOR_GAMMA_HPP_

#include <be/core/buf.hpp>
#include <be/core/glm.hpp>
#include <glfw/glfw3.h>
#include <glm/vec3.hpp>
#include <functional>

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
class MonitorGamma final {
public:
   MonitorGamma();
   explicit MonitorGamma(std::size_t size);
   explicit MonitorGamma(const GLFWgammaramp& ramp);

   explicit operator bool() const {
      return size_ > 0;
   }

   std::size_t size() const {
      return size_;
   }

   GLFWgammaramp glfw();

   Buf<U16> red() {
      return Buf<U16>(data_.data(), size_);
   }

   Buf<const U16> red() const {
      return Buf<const U16>(data_.data(), size_);
   }

   Buf<U16> green() {
      return Buf<U16>(data_.data() + size_, size_);
   }

   Buf<const U16> green() const {
      return Buf<const U16>(data_.data() + size_, size_);
   }

   Buf<U16> blue() {
      return Buf<U16>(data_.data() + size_ * 2, size_);
   }

   Buf<const U16> blue() const {
      return Buf<const U16>(data_.data() + size_ * 2, size_);
   }

private:
   std::vector<U16> data_;
   std::size_t size_;
};

MonitorGamma linear_gamma();
MonitorGamma srgb_gamma();
MonitorGamma standard_gamma(F32 monitor_exponent = 2.2f);
MonitorGamma custom_gamma(const std::function<F64(F64)>& response);
MonitorGamma custom_gamma(const std::function<F64(F64)>& red_response, const std::function<F64(F64)>& green_response, const std::function<F64(F64)>& blue_response);
MonitorGamma custom_gamma(const std::function<dvec3(F64)>& response);

} // be::platform

#endif
