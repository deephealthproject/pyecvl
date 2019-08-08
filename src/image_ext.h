#include <ecvl/core/image.h>

namespace ecvl {
  class View_int8 : public View<DataType::int8> {
  public:
  View_int8(Image& img) : View<DataType::int8>(img) {}
  };

  class View_int16 : public View<DataType::int16> {
  public:
  View_int16(Image& img) : View<DataType::int16>(img) {}
  };

  class ImageFuncHolder {};
}
