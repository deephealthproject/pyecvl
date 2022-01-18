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
#include <ecvl/dataset_parser.h>

ecvl::any toSplit(pybind11::object o) {
    ecvl::any split;
    try {
	split = o.cast<ecvl::SplitType>();
    } catch (const pybind11::cast_error&) {
	try {
	    split = o.cast<std::string>();
	} catch (const pybind11::cast_error&) {
	    try {
		split = o.cast<int>();
	    } catch (const pybind11::cast_error&) {
		split = -1;
	    }
	}
    }
    return split;
}


template <typename type_, typename... options>
void dataset_addons(pybind11::class_<type_, options...> &cl) {
    cl.def(pybind11::init([](const std::string& filename) {
      return new ecvl::Dataset(filename);
    }));
    cl.def("GetSplit", [](ecvl::Dataset& d) {
      return d.GetSplit();
    });
    cl.def("GetSplit", [](ecvl::Dataset& d, pybind11::object o) {
      return d.GetSplit(toSplit(o));
    });
    cl.def("SetSplit", [](ecvl::Dataset& d, pybind11::object o) {
      d.SetSplit(toSplit(o));
    });
    cl.def("Dump", [](ecvl::Dataset& d, const std::string& file_path) {
      d.Dump(file_path);
    });
    cl.def("GetLocations", &ecvl::Dataset::GetLocations);
}
