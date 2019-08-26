#define image_addons(cl) \
cl.def(pybind11::init<const std::vector<int>&, ecvl::DataType, std::string, \
       ecvl::ColorType, const std::vector<float>&>(), \
       pybind11::arg("dims"), pybind11::arg("elemtype"), \
       pybind11::arg("channels"), pybind11::arg("colortype"), \
       pybind11::arg("spacings") = std::vector<float>(), \
       pybind11::keep_alive<1, 2>(), pybind11::keep_alive<1, 6>()); \
cl.def_buffer([](ecvl::Image &img) -> pybind11::buffer_info { \
  std::string fmt; \
  switch (img.elemtype_) { \
  case ecvl::DataType::int8: \
    fmt = "b"; \
    break; \
  case ecvl::DataType::int16: \
    fmt = "h"; \
    break; \
  case ecvl::DataType::int32: \
    fmt = "i"; \
    break; \
  case ecvl::DataType::int64: \
    fmt = "q"; \
    break; \
  case ecvl::DataType::float32: \
    fmt = "f"; \
    break; \
  case ecvl::DataType::float64: \
    fmt = "d"; \
    break; \
  case ecvl::DataType::uint8: \
    fmt = "B"; \
    break; \
  case ecvl::DataType::uint16: \
    fmt = "H"; \
    break; \
  default: \
    throw std::invalid_argument("unknown data type"); \
  } \
  return pybind11::buffer_info( \
    img.data_,	\
    img.elemsize_, \
    fmt, \
    img.dims_.size(), \
    img.dims_, \
    img.strides_ \
  ); \
});
