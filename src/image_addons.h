#define image_addons(cl) \
cl.def(pybind11::init<const std::vector<int>&, ecvl::DataType, std::string, \
       ecvl::ColorType, const std::vector<float>&>(), \
       pybind11::arg("dims"), pybind11::arg("elemtype"), \
       pybind11::arg("channels"), pybind11::arg("colortype"), \
       pybind11::arg("spacings") = std::vector<float>(), \
       pybind11::keep_alive<1, 2>(), pybind11::keep_alive<1, 6>());
