#pragma once

namespace ecvl {
  template<typename Module> void bind_ecvl_functions(Module &m) {
    m.def("RearrangeChannels", &RearrangeChannels);
  }
}
