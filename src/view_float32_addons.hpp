#pragma once

#include <pybind11/pybind11.h>

template <typename type_, typename... options>
void view_float32_addons(pybind11::class_<type_, options...> &cl) {
    cl.def("__setitem__", [](ecvl::View<ecvl::DataType::float32> &v,
			     const std::vector<int>& coords, float value) {
	       v(coords) = value;
	   });
    cl.def("__getitem__", [](ecvl::View<ecvl::DataType::float32> &v,
			     const std::vector<int>& coords) -> float {
	       return v(coords);
	   });
}
