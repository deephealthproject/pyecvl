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

#pragma once
#include <pybind11/pybind11.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgcodecs.h>
#include <ecvl/core/imgproc.h>
#ifdef ECVL_EDDL
#include <ecvl/augmentations.h>
#include <ecvl/support_eddl.h>
#endif
#ifdef ECVL_WITH_OPENSLIDE
#include <ecvl/core/support_openslide.h>
#endif
#include <ecvl/core/support_nifti.h>
#ifdef ECVL_WITH_DICOM
#include <ecvl/core/support_dcmtk.h>
#endif

void bind_ecvl_functions(pybind11::module &m) {
  m.def("RearrangeChannels", [](const ecvl::Image& src, ecvl::Image& dst, const std::string& channels) {
    ecvl::RearrangeChannels(src, dst, channels);
  });
  m.def("RearrangeChannels", (void (*)(const ecvl::Image&, ecvl::Image&, const std::string&, ecvl::DataType)) &ecvl::RearrangeChannels, "C++: ecvl::RearrangeChannels(const ecvl::Image&, ecvl::Image&, const std::string&, ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("channels"), pybind11::arg("new_type"));
  m.def("ImRead", [](const std::string& filename) -> ecvl::Image {
	  ecvl::Image dst;
	  if (!ecvl::ImRead(filename, dst)) {
	      throw std::runtime_error("Can't read " + filename);
	  }
	  return dst;
      });
  m.def("ImRead", [](const std::string& filename, ecvl::ImReadMode flags) -> ecvl::Image {
	  ecvl::Image dst;
	  if (!ecvl::ImRead(filename, dst, flags)) {
	      throw std::runtime_error("Can't read " + filename);
	  }
	  return dst;
      });
  m.def("ImWrite", [](const std::string& filename, ecvl::Image& src) -> void {
	  if (!ecvl::ImWrite(filename, src)) {
	      throw std::runtime_error("Can't write " + filename);
	  }
      });
  // imgproc: ResizeDim
  m.def("ResizeDim", [](const class ecvl::Image& src, class ecvl::Image& dst, const std::vector<int>& newdims) -> void { return ecvl::ResizeDim(src, dst, newdims); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("newdims"));
  m.def("ResizeDim", (void (*)(const class ecvl::Image&, class ecvl::Image&, const std::vector<int>&, enum ecvl::InterpolationType)) &ecvl::ResizeDim, "Resizes an Image to the specified dimensions.\n\nC++: ecvl::ResizeDim(const class ecvl::Image&, class ecvl::Image&, const std::vector<int>&, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("newdims"), pybind11::arg("interp"));
  // imgproc: ResizeScale
  m.def("ResizeScale", [](const class ecvl::Image& src, class ecvl::Image& dst, const std::vector<double>& scales) -> void { return ecvl::ResizeScale(src, dst, scales); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("scales"));
  m.def("ResizeScale", (void (*)(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, enum ecvl::InterpolationType)) &ecvl::ResizeScale, "Resizes an Image by scaling the dimensions to a given scale factor.\n\nC++: ecvl::ResizeScale(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("scales"), pybind11::arg("interp"));
  // imgproc: Rotate2D
  m.def("Rotate2D", [](const class ecvl::Image& src, class ecvl::Image& dst, double angle) -> void { return ecvl::Rotate2D(src, dst, angle); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"));
  m.def("Rotate2D", [](const class ecvl::Image& src, class ecvl::Image& dst, double angle, const std::vector<double>& center) -> void { return ecvl::Rotate2D(src, dst, angle, center); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("center"));
  m.def("Rotate2D", [](const class ecvl::Image& src, class ecvl::Image& dst, double angle, const std::vector<double>& center, double scale) -> void { return ecvl::Rotate2D(src, dst, angle, center, scale); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("center"), pybind11::arg("scale"));
  m.def("Rotate2D", (void (*)(const class ecvl::Image&, class ecvl::Image&, double, const std::vector<double>&, double, enum ecvl::InterpolationType)) &ecvl::Rotate2D, "Rotates an Image.\n\nC++: ecvl::Rotate2D(const class ecvl::Image&, class ecvl::Image&, double, const std::vector<double>&, double, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("center"), pybind11::arg("scale"), pybind11::arg("interp"));
  // imgproc: SeparableFilter2D
  m.def("SeparableFilter2D", [](const class ecvl::Image& src, class ecvl::Image& dst, const std::vector<double>& kerX, const std::vector<double>& kerY) -> void { return ecvl::SeparableFilter2D(src, dst, kerX, kerY); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("kerX"), pybind11::arg("kerY"));
  m.def("SeparableFilter2D", (void (*)(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, const std::vector<double>&, enum ecvl::DataType)) &ecvl::SeparableFilter2D, "Convolves an Image with a couple of 1-dimensional kernels.\n\nC++: ecvl::SeparableFilter2D(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, const std::vector<double>&, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("kerX"), pybind11::arg("kerY"), pybind11::arg("type"));
  // imgproc: GetMaxN
  m.def("GetMaxN", (std::vector<std::array<int, 2>> (*)(const class ecvl::Image&, size_t)) &ecvl::GetMaxN, "Get the n maximum values that are in the source Image.\n\nC++: ecvl::GetMaxN(const class ecvl::Image&, size_t) --> std::vector<std::array<int, 2>>", pybind11::arg("src"), pybind11::arg("n"));
  // imgproc: FindContours
  m.def("FindContours", [](const class ecvl::Image& src) -> std::vector<std::vector<std::array<int, 2>>> {
	  std::vector<std::vector<ecvl::Point2i>> contours;
	  ecvl::FindContours(src, contours);
	  return contours;
      }, "Find contours in a binary image");
#ifdef ECVL_EDDL

  // augmentations: AugmentationParam
  {
  pybind11::class_<ecvl::AugmentationParam, std::shared_ptr<ecvl::AugmentationParam>> cl(m, "AugmentationParam", "Augmentations parameters. This class represent the augmentations parameters which must be randomly generated in a specific range.");
  cl.def(pybind11::init([](){ return new ecvl::AugmentationParam(); }));
  cl.def( pybind11::init<const double, const double>(), pybind11::arg("min"), pybind11::arg("max"));
  cl.def_readwrite("min_", &ecvl::AugmentationParam::min_);
  cl.def_readwrite("max_", &ecvl::AugmentationParam::max_);
  cl.def_readwrite("value_", &ecvl::AugmentationParam::value_);
  cl.def("GenerateValue", (void (ecvl::AugmentationParam::*)()) &ecvl::AugmentationParam::GenerateValue, "Generate the random value between min_ and max_.");
  cl.def_static("SetSeed", (void (*)(unsigned int)) &ecvl::AugmentationParam::SetSeed, "Set a fixed seed for the random generated values. Useful to reproduce experiments with same augmentations.", pybind11::arg("seed"));
  }

  // eddl: ImageToTensor
  m.def("ImageToTensor", [](const ecvl::Image& img) {
    Tensor* t;
    ecvl::ImageToTensor(img, t);
    return t;
  });
  m.def("ImageToTensor", [](const ecvl::Image& img, int offset) {
    Tensor* t;
    ecvl::ImageToTensor(img, t, offset);
    return t;
  });
  // support_eddl: TensorToImage
  m.def("TensorToImage", [](Tensor* t) {
    ecvl::Image img;
    ecvl::TensorToImage(t, img);
    return img;
  });
  // support_eddl: TensorToView
  m.def("TensorToView", [](Tensor* t) {
    ecvl::View<ecvl::DataType::float32> view;
    ecvl::TensorToView(t, view);
    return view;
  });
  // support_eddl: DLDataset
  // pybind11::class_<ecvl::DLDataset, std::shared_ptr<ecvl::DLDataset>, ecvl::Dataset> cl(m, "DLDataset", "");
  // cl.def(pybind11::init([](const std::string& filename, const int batch_size, const std::vector<int>& resize_dims) { return new ecvl::DLDataset(filename, batch_size, resize_dims); }));
  // cl.def(pybind11::init([](const std::string& filename, const int batch_size, const std::vector<int>& resize_dims, ecvl::ColorType ctype) { return new ecvl::DLDataset(filename, batch_size, resize_dims, ctype); }));
  // cl.def(pybind11::init([](const std::string& filename, const int batch_size, const std::vector<int>& resize_dims, ecvl::ColorType ctype, ecvl::ColorType ctype_gt) { return new ecvl::DLDataset(filename, batch_size, resize_dims, ctype, ctype_gt); }));
  // cl.def_readwrite("batch_size_", &ecvl::DLDataset::batch_size_);
  // cl.def_readwrite("n_channels_", &ecvl::DLDataset::n_channels_);
  // cl.def_readwrite("current_split_", &ecvl::DLDataset::current_split_);
  // cl.def_readwrite("resize_dims_", &ecvl::DLDataset::resize_dims_);
  // cl.def_readwrite("current_batch_", &ecvl::DLDataset::current_batch_);
  // cl.def_readwrite("ctype_", &ecvl::DLDataset::ctype_);
  // cl.def_readwrite("ctype_gt_", &ecvl::DLDataset::ctype_gt_);
  // cl.def("GetSplit", &ecvl::DLDataset::GetSplit);
  // cl.def("ResetCurrentBatch", &ecvl::DLDataset::ResetCurrentBatch);
  // cl.def("ResetAllBatches", &ecvl::DLDataset::ResetAllBatches);
  // cl.def("SetSplit", &ecvl::DLDataset::SetSplit);
  // cl.def("LoadBatch", [](ecvl::DLDataset& d, Tensor* images, Tensor* labels) {
  //   d.LoadBatch(images, labels);
  // });
#endif
#ifdef ECVL_WITH_OPENSLIDE
  // support_openslide: OpenSlideRead
  m.def("OpenSlideRead", [](std::string& filename, const int level, const std::vector<int>& dims) -> ecvl::Image {
    ecvl::Image dst;
    if (!ecvl::OpenSlideRead(filename, dst, level, dims)) {
	throw std::runtime_error("Can't read " + filename);
    }
    return dst;
  });
  // support_openslide: OpenSlideGetLevels
  m.def("OpenSlideGetLevels", [](std::string& filename) -> std::vector<std::array<int, 2>> {
    std::vector<std::array<int, 2>> levels;
    ecvl::OpenSlideGetLevels(filename, levels);
    return levels;
  });
#endif
  // support_nifti: NiftiRead
  m.def("NiftiRead", [](const std::string& filename) -> ecvl::Image {
    ecvl::Image dst;
    if (!ecvl::NiftiRead(filename, dst)) {
      throw std::runtime_error("Can't read " + filename);
    }
    return dst;
  });
  // support_nifti: NiftiWrite
  m.def("NiftiWrite", [](const std::string& filename, ecvl::Image& src) {
    if (!ecvl::NiftiWrite(filename, src)) {
      throw std::runtime_error("Can't write " + filename);
    }
  });
#ifdef ECVL_WITH_DICOM
  // support_dcmtk: DicomRead
  m.def("DicomRead", [](const std::string& filename) -> ecvl::Image {
    ecvl::Image dst;
    if (!ecvl::DicomRead(filename, dst)) {
      throw std::runtime_error("Can't read " + filename);
    }
    return dst;
  });
  // support_dcmtk: DicomWrite
  m.def("DicomWrite", [](const std::string& filename, ecvl::Image& src) {
    if (!ecvl::DicomWrite(filename, src)) {
      throw std::runtime_error("Can't write " + filename);
    }
  });
#endif
}
