// Copyright (c) 2019-2022 CRS4
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <pybind11/pybind11.h>
#include <ecvl/core/metadata.h>


template <typename type_, typename... options>
void metadata_addons(pybind11::class_<type_, options...> &cl) {
    cl.def(pybind11::init([](const unsigned short& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def(pybind11::init([](const short& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def(pybind11::init([](const unsigned int& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def(pybind11::init([](const int& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def(pybind11::init([](const long& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def(pybind11::init([](const long long& value) {
      return new ecvl::MetaData(value, 0);
    }));
    // No overload for float (in case of overflow, conversion succeeds and creates an inf)
    cl.def(pybind11::init([](const double& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def(pybind11::init([](const std::string& value) {
      return new ecvl::MetaData(value, 0);
    }));
    cl.def("Get", [](ecvl::MetaData& m) -> pybind11::object {
      std::any value = m.Get();
      if (const auto it = metadata_conv.find(std::type_index(value.type())); it != metadata_conv.cend()) {
        return it->second(value);
      }
      throw std::runtime_error("Unsupported type");
    });
    cl.def("GetStr", &ecvl::MetaData::GetStr);
}
