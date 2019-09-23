#pragma once

#include <pybind11/pybind11.h>

template <typename type_, typename... options>
void path_addons(pybind11::class_<type_, options...> &cl) {
    cl.def(pybind11::init<const std::string&>(), pybind11::arg("p"),
	   pybind11::keep_alive<1, 2>());
}
