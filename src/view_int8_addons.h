#pragma once

#include <pybind11/pybind11.h>

template <typename type_, typename... options>
void view_int8_addons(pybind11::class_<type_, options...> &cl) {
    cl.def("__setitem__", [](ecvl::View<ecvl::DataType::int8> &v,
			     const std::vector<int>& coords, int8_t value) {
	       v(coords) = value;
	   });
    cl.def("__getitem__", [](ecvl::View<ecvl::DataType::int8> &v,
			     const std::vector<int>& coords) -> int8_t {
	       return v(coords);
	   });
}
