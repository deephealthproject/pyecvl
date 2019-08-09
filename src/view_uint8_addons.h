#define view_uint8_addons(cl) \
cl.def("__setitem__", [](ecvl::View<ecvl::DataType::uint8> &v, const std::vector<int>& coords, uint8_t value) { v(coords) = value; }); \
cl.def("__getitem__", [](ecvl::View<ecvl::DataType::uint8> &v, const std::vector<int>& coords) -> uint8_t { return v(coords); });
