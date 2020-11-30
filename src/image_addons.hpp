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
#include <pybind11/numpy.h>


ecvl::Image* bufToImg(const pybind11::buffer_info& b,
                      const ecvl::DataType& elemtype,
                      const std::string& channels,
                      const ecvl::ColorType& colortype,
                      const std::vector<float>& spacings) {
    std::vector<int> shape(b.shape.begin(), b.shape.end());
    auto img = new ecvl::Image(shape, elemtype, channels, colortype, spacings);
    std::copy((uint8_t*)b.ptr, ((uint8_t*)b.ptr) + img->datasize_, img->data_);
    return img;
}


template <typename type_, typename... options>
void image_addons(pybind11::class_<type_, options...> &cl) {
    cl.def(pybind11::init<const std::vector<int>&, ecvl::DataType, std::string,
           ecvl::ColorType, const std::vector<float>&, ecvl::Device>(),
           pybind11::arg("dims"), pybind11::arg("elemtype"),
           pybind11::arg("channels"), pybind11::arg("colortype"),
           pybind11::arg("spacings") = std::vector<float>(),
           pybind11::arg("dev") = ecvl::Device::CPU,
           pybind11::keep_alive<1, 2>(), pybind11::keep_alive<1, 6>());
    // def_buffer will be run by numpy, so exceptions will crash the program
    cl.def_buffer([](ecvl::Image &img) -> pybind11::buffer_info {
        if (img.IsEmpty()) {
            throw std::invalid_argument("image is empty");
        }
        std::string fmt;
        switch (img.elemtype_) {
        case ecvl::DataType::int8:
            fmt = "b";
            break;
        case ecvl::DataType::int16:
            fmt = "h";
            break;
        case ecvl::DataType::int32:
            fmt = "i";
            break;
        case ecvl::DataType::int64:
            fmt = "q";
            break;
        case ecvl::DataType::float32:
            fmt = "f";
            break;
        case ecvl::DataType::float64:
            fmt = "d";
            break;
        case ecvl::DataType::uint8:
            fmt = "B";
            break;
        case ecvl::DataType::uint16:
            fmt = "H";
            break;
        default:
            throw std::invalid_argument("unknown data type");
        }
        return pybind11::buffer_info(
            img.data_,
            img.elemsize_,
            fmt,
            img.dims_.size(),
            img.dims_,
            img.strides_
        );
    });
    cl.def(pybind11::init([](pybind11::array_t<std::int8_t, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::int8, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<std::int16_t, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::int16, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<std::int32_t, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::int32, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<std::int64_t, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::int64, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<std::uint8_t, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::uint8, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<std::uint16_t, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::uint16, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<float, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::float32, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def(pybind11::init([](pybind11::array_t<double, pybind11::array::f_style> array, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings) {
        return bufToImg(array.request(), ecvl::DataType::float64, channels, colortype, spacings);
    }), pybind11::arg("buf"), pybind11::arg("channels"), pybind11::arg("colortype"), pybind11::arg("spacings") = std::vector<float>());
    cl.def("Add", &ecvl::Image::Add<ecvl::Image>, "In-place addition", pybind11::arg("rhs"), pybind11::arg("saturate") = true);
    cl.def("Sub", &ecvl::Image::Sub<ecvl::Image>, "In-place subtraction", pybind11::arg("rhs"), pybind11::arg("saturate") = true);
    cl.def("Mul", &ecvl::Image::Mul<ecvl::Image>, "In-place multiplication", pybind11::arg("rhs"), pybind11::arg("saturate") = true);
    cl.def("Div", &ecvl::Image::Div<ecvl::Image>, "In-place division", pybind11::arg("rhs"), pybind11::arg("saturate") = true);
    cl.def("copy", [](ecvl::Image& img) -> ecvl::Image {
      return ecvl::Image(img);  // copy constructor
    });
}
