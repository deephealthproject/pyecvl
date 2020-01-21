#pragma once

#include <pybind11/pybind11.h>
#include <ecvl/dataset_parser.h>

template <typename type_, typename... options>
void dataset_addons(pybind11::class_<type_, options...> &cl) {
    cl.def(pybind11::init([](const std::string& filename) {
      return new ecvl::Dataset(filename);
    }));
}
