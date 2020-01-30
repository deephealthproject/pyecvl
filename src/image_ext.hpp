// Copyright (c) 2020 CRS4
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
  class View_float32 : public View<DataType::float32> {
  public:
    View_float32(Image& img) : View<DataType::float32>(img) {}
  };
  class View_uint8 : public View<DataType::uint8> {
  public:
    View_uint8(Image& img) : View<DataType::uint8>(img) {}
  };
}
