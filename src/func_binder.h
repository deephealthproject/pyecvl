#pragma once
#include <pybind11/pybind11.h>
#include <ecvl/core/image.h>

void bind_ecvl_functions(pybind11::module &m) {
  m.def("RearrangeChannels", &ecvl::RearrangeChannels);
}
