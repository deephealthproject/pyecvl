// Copyright (c) 2020 CRS4
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


std::vector<std::string> getSampleLocation(ecvl::Sample &s) {
    std::vector<std::string> loc;
    for (const auto &path: s.location_) {
	loc.push_back(std::string(path));
    }
    return loc;
}

void setSampleLocation(ecvl::Sample &s, std::vector<std::string> loc) {
    std::vector<ecvl::filesystem::path> location_;
    for (const auto &str: loc) {
	location_.push_back(ecvl::filesystem::path(str));
    }
    s.location_ = location_;
}


ecvl::optional<std::string> getSampleLabelPath(ecvl::Sample &s) {
    if (s.label_path_) {
	std::string rval = *(s.label_path_);
	return rval;
    }
    return std::nullopt;
}


void setSampleLabelPath(ecvl::Sample &s, std::string lp) {
    s.label_path_ = ecvl::filesystem::path(lp);
}


template <typename type_, typename... options>
void sample_addons(pybind11::class_<type_, options...> &cl) {
    cl.def_property("location_", getSampleLocation, setSampleLocation);
    cl.def_property("label_path_", getSampleLabelPath, setSampleLabelPath);
}
