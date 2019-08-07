#include <ecvl/core/image.h>

namespace ecvl {
  class View_int8 : public View<DataType::int8> {
  public:
  View_int8(Image& img) : View<DataType::int8>(img) {}
  };
}
