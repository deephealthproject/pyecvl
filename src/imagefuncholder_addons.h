#define imagefuncholder_addons(cl) \
  cl.def_static("RearrangeChannels", [](const ecvl::Image& src, ecvl::Image& dst, const std::string& channels) { return ecvl::RearrangeChannels(src, dst, channels); });
