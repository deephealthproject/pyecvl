#define view_int16_addons(cl) \
cl.def("__setitem__", [](ecvl::View<ecvl::DataType::int16> &v, const std::vector<int>& coords, int16_t value) { v(coords) = value; }); \
cl.def("__getitem__", [](ecvl::View<ecvl::DataType::int16> &v, const std::vector<int>& coords) -> int16_t { return v(coords); });
