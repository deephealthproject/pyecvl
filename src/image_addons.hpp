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
           ecvl::ColorType, const std::vector<float>&>(),
           pybind11::arg("dims"), pybind11::arg("elemtype"),
           pybind11::arg("channels"), pybind11::arg("colortype"),
           pybind11::arg("spacings") = std::vector<float>(),
           pybind11::keep_alive<1, 2>(), pybind11::keep_alive<1, 6>());
    cl.def_buffer([](ecvl::Image &img) -> pybind11::buffer_info {
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
}
