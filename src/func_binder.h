#pragma once
#include <pybind11/pybind11.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgcodecs.h>

void bind_ecvl_functions(pybind11::module &m) {
  m.def("RearrangeChannels", &ecvl::RearrangeChannels);
  m.def("ImRead", [](const std::string& filename, ecvl::Image& dst) -> bool {
	  return ecvl::ImRead(filename, dst);
      });
  m.def("ImWrite", [](const std::string& filename, ecvl::Image& src) -> bool {
	  return ecvl::ImWrite(filename, src);
      });
}
