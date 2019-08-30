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
}); \
 cl.def("__init__", [](ecvl::Image &img, pybind11::buffer b, std::string channels, ecvl::ColorType colortype, const std::vector<float>& spacings = std::vector<float>()) { \
  pybind11::buffer_info info = b.request(); \
  ecvl::DataType elemtype; \
  if (info.format == "b") \
    elemtype = ecvl::DataType::int8; \
  else if (info.format == "h") \
    elemtype = ecvl::DataType::int16; \
  else if (info.format == "i") \
    elemtype = ecvl::DataType::int32; \
  else if (info.format == "q" || (info.format == "l" && info.itemsize == 8)) \
    elemtype = ecvl::DataType::int64 ; \
  else if (info.format == "f") \
    elemtype = ecvl::DataType::float32; \
  else if (info.format == "d") \
    elemtype = ecvl::DataType::float64; \
  else if (info.format == "B") \
    elemtype = ecvl::DataType::uint8; \
  else if (info.format == "H") \
    elemtype = ecvl::DataType::uint16; \
  else \
    throw std::invalid_argument("unknown data type"); \
  bool f_contiguous = true; \
  std::vector<ssize_t> f_contiguous_strides(info.ndim); \
  ssize_t S = info.itemsize; \
  for (int i = 0; i < info.ndim; ++i) { \
    f_contiguous_strides[i] = S; \
    S *= info.shape[i]; \
  } \
  for (int i = 0; i < info.ndim; ++i) { \
    if (info.strides[i] != f_contiguous_strides[i]) { \
	f_contiguous = false; \
	break; \
    } \
  } \
  std::vector<int> shape(info.ndim); \
  for (int i = 0; i < info.ndim; ++i) { \
    shape[i] = info.shape[i]; \
  } \
  new(&img) ecvl::Image(shape, elemtype, channels, colortype, spacings); \
  if (f_contiguous) { \
    std::copy((uint8_t*)info.ptr, ((uint8_t*)info.ptr) + img.datasize_, img.data_); \
  } else { \
    throw std::runtime_error("data is not fortran-contiguous"); \
  } \
});
