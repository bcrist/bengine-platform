#include "pch.hpp"
#include "monitor_gamma.hpp"
#include <be/core/logging.hpp>
#include <be/gfx/tex/convert_colorspace_srgb.hpp>
#include <glm/common.hpp>
#include <cassert>

namespace be::platform {

//////////////////////////////////////////////////////////////////////////////
MonitorGamma::MonitorGamma()
   : size_(0) { }

//////////////////////////////////////////////////////////////////////////////
MonitorGamma::MonitorGamma(std::size_t size)
   : size_(size) {
   data_.resize(size * 3);
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma::MonitorGamma(const GLFWgammaramp& ramp)
   : size_(ramp.size) {
   
   data_.reserve(size_ * 3);
   
   for (int i = 0; i < size_; ++i) {
      data_.push_back(ramp.red[i]);
   }

   for (int i = 0; i < size_; ++i) {
      data_.push_back(ramp.green[i]);
   }

   for (int i = 0; i < size_; ++i) {
      data_.push_back(ramp.blue[i]);
   }
}

//////////////////////////////////////////////////////////////////////////////
GLFWgammaramp MonitorGamma::glfw() {
   assert(size_ > 0);
   assert(size_ <= std::numeric_limits<int>::max());
   GLFWgammaramp ramp;
   ramp.size = ( int ) size_;
   ramp.red = static_cast<unsigned short*>(data_.data());
   ramp.green = static_cast<unsigned short*>(data_.data() + size_);
   ramp.blue = static_cast<unsigned short*>(data_.data() + size_ * 2);
   return ramp;
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma linear_gamma() {
   MonitorGamma gamma(256);

   constexpr U16 max_response = U16(-1);
   const std::size_t divisor = 255;

   U16* r = gamma.red().get();
   U16* g = gamma.green().get();
   U16* b = gamma.blue().get();

   for (std::size_t i = 0; i < 256; ++i) {
      U16 v = U16(max_response * i / divisor);
      r[i] = v;
      g[i] = v;
      b[i] = v;
   }

   return gamma;
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma srgb_gamma() {
   MonitorGamma gamma(256);

   constexpr F32 scale = F64(U16(-1));

   U16* r = gamma.red().get();
   U16* g = gamma.green().get();
   U16* b = gamma.blue().get();

   for (std::size_t i = 0; i < 256; ++i) {
      F32 input = i / 255.f;
      F32 output = gfx::tex::linear_to_srgb(input) * scale + 0.5f;
      if (output > scale) {
         output = scale;
      }

      U16 v = ( U16 ) output;
      r[i] = v;
      g[i] = v;
      b[i] = v;
   }

   return gamma;
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma standard_gamma(F32 monitor_exponent) {
   MonitorGamma gamma(256);

   if (std::isnan(monitor_exponent) || monitor_exponent <= 0.f || monitor_exponent > std::numeric_limits<F32>::max()) {
      be_warn() << "Invalid gamma exponent!"
         & attr("Monitor Response") << monitor_exponent
         & attr(ids::log_attr_trace) << get_stack_trace()
         | default_log();
   } else {
      const F64 inverse_gamma = 1.0 / monitor_exponent;
      constexpr F64 scale = F64(U16(-1));

      U16* r = gamma.red().get();
      U16* g = gamma.green().get();
      U16* b = gamma.blue().get();

      for (std::size_t i = 0; i < 256; ++i) {
         F64 input = i / 255.0;
         F64 output = std::pow(input, inverse_gamma) * scale + 0.5;
         if (output > scale) {
            output = scale;
         }

         U16 v = ( U16 ) output;
         r[i] = v;
         g[i] = v;
         b[i] = v;
      }
   }

   return gamma;
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma custom_gamma(const std::function<F64(F64)>& response) {
   MonitorGamma gamma(256);

   constexpr F64 scale = F64(U16(-1));

   U16* r = gamma.red().get();
   U16* g = gamma.green().get();
   U16* b = gamma.blue().get();

   for (std::size_t i = 0; i < 256; ++i) {
      F64 input = i / 255.0;
      F64 output = response(input) * scale + 0.5;
      if (output > scale) {
         output = scale;
      }

      U16 v = ( U16 ) output;
      r[i] = v;
      g[i] = v;
      b[i] = v;
   }

   return gamma;
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma custom_gamma(const std::function<F64(F64)>& red_response, const std::function<F64(F64)>& green_response, const std::function<F64(F64)>& blue_response) {
   MonitorGamma gamma(256);

   constexpr F64 scale = F64(U16(-1));

   U16* r = gamma.red().get();
   U16* g = gamma.green().get();
   U16* b = gamma.blue().get();

   for (std::size_t i = 0; i < 256; ++i) {
      F64 input = i / 255.0;

      F64 red = red_response(input) * scale + 0.5;
      F64 green = green_response(input) * scale + 0.5;
      F64 blue = blue_response(input) * scale + 0.5;

      if (red > scale) {
         red = scale;
      }
      if (green > scale) {
         green = scale;
      }
      if (blue > scale) {
         blue = scale;
      }

      r[i] = ( U16 ) red;
      g[i] = ( U16 ) green;
      b[i] = ( U16 ) blue;
   }

   return gamma;
}

//////////////////////////////////////////////////////////////////////////////
MonitorGamma custom_gamma(const std::function<dvec3(F64)>& response) {
   MonitorGamma gamma(256);

   constexpr F64 scale = F64(U16(-1));
   const dvec3 vec_scale = dvec3(scale);

   U16* r = gamma.red().get();
   U16* g = gamma.green().get();
   U16* b = gamma.blue().get();

   for (std::size_t i = 0; i < 256; ++i) {
      F64 input = i / 255.0;
      dvec3 output = response(input) * scale + 0.5;
      output = glm::min(output, dvec3(scale));

      r[i] = ( U16 ) output.r;
      g[i] = ( U16 ) output.g;
      b[i] = ( U16 ) output.b;
   }

   return gamma;
}

} // be::platform
