#define path_addons(cl) \
cl.def(pybind11::init<const std::string&>(), pybind11::arg("p"), pybind11::keep_alive<1, 2>());
