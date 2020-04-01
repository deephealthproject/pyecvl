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


class PyAugmentation : public ecvl::Augmentation {
public:
    using ecvl::Augmentation::Augmentation;

    void RealApply(ecvl::Image& img, const ecvl::Image& gt = ecvl::Image()) override {
	PYBIND11_OVERLOAD_PURE(void, ecvl::Augmentation, RealApply, img, gt);
    }
};


std::vector<ecvl::Augmentation*> getAugs(ecvl::SequentialAugmentationContainer &c) {
    std::vector<ecvl::Augmentation*> rval;
    for (const auto &aug: c.augs_) {
	rval.push_back(aug.get());
    }
    return rval;
}


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
  // augmentations: Augmentation
  {
  pybind11::class_<ecvl::Augmentation, std::unique_ptr<ecvl::Augmentation, pybind11::nodelete>, PyAugmentation> cl(m, "Augmentation", "Abstract class which represent a generic Augmentation function.");
  cl.def(pybind11::init<>());
  cl.def_readwrite("params_", &ecvl::Augmentation::params_);
  cl.def("Apply", [](ecvl::Augmentation &o, class ecvl::Image & a0) -> void { return o.Apply(a0); }, "", pybind11::arg("img"));
  cl.def("Apply", (void (ecvl::Augmentation::*)(class ecvl::Image &, const class ecvl::Image &)) &ecvl::Augmentation::Apply, "Generate the random value for each parameter and call the specialized augmentation functions.", pybind11::arg("img"), pybind11::arg("gt"));
  }
  // augmentations::SequentialAugmentationContainer
  {
  pybind11::class_<ecvl::SequentialAugmentationContainer, std::unique_ptr<ecvl::SequentialAugmentationContainer, pybind11::nodelete>, ecvl::Augmentation> cl(m, "SequentialAugmentationContainer", "Represents a container for multiple augmentations which will be sequentially applied to the Dataset images.");
  cl.def_property_readonly("augs_", getAugs, pybind11::return_value_policy::reference);
  cl.def(pybind11::init<>());
  cl.def(pybind11::init<const std::vector<ecvl::Augmentation*>&>());
  cl.def("Add", (void (ecvl::SequentialAugmentationContainer::*)(ecvl::Augmentation*)) &ecvl::SequentialAugmentationContainer::Add, "ecvl::Add(ecvl::Augmentation*) --> void", pybind11::arg("aug"));
  }
  // augmentations: AugRotate
  {
  pybind11::class_<ecvl::AugRotate, std::unique_ptr<ecvl::AugRotate, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugRotate", "Augmentation wrapper for ecvl::Rotate2D.");
  cl.def(pybind11::init<const std::array<double, 2>&, const std::vector<double>&, const double&, const ecvl::InterpolationType&>(), pybind11::arg("angle"), pybind11::arg("center") = std::vector<double>(), pybind11::arg("scale") = 1., pybind11::arg("interp") = ecvl::InterpolationType::linear);
  }
  // augmentations: AugResizeDim
  {
  pybind11::class_<ecvl::AugResizeDim, std::unique_ptr<ecvl::AugResizeDim, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugResizeDim", "Augmentation wrapper for ecvl::ResizeDim.");
  cl.def(pybind11::init<const std::vector<int>&, const ecvl::InterpolationType&>(), pybind11::arg("dims"), pybind11::arg("interp") = ecvl::InterpolationType::linear);
  }
  // augmentations: AugResizeScale
  {
  pybind11::class_<ecvl::AugResizeScale, std::unique_ptr<ecvl::AugResizeScale, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugResizeScale", "Augmentation wrapper for ecvl::ResizeScale.");
  cl.def(pybind11::init<const std::vector<double>&, const ecvl::InterpolationType&>(), pybind11::arg("scale"), pybind11::arg("interp") = ecvl::InterpolationType::linear);
  }
  // augmentations: AugFlip
  {
  pybind11::class_<ecvl::AugFlip, std::unique_ptr<ecvl::AugFlip, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugFlip", "Augmentation wrapper for ecvl::Flip2D.");
  cl.def(pybind11::init<const double &>(), pybind11::arg("p"));
  }
  // augmentations: AugMirror
  {
  pybind11::class_<ecvl::AugMirror, std::unique_ptr<ecvl::AugMirror, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugMirror", "Augmentation wrapper for ecvl::Mirror2D.");
  cl.def(pybind11::init<const double &>(), pybind11::arg("p"));
  }
  // augmentations: AugGaussianBlur
  {
  pybind11::class_<ecvl::AugGaussianBlur, std::unique_ptr<ecvl::AugGaussianBlur, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugGaussianBlur", "Augmentation wrapper for ecvl::GaussianBlur.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("sigma"));
  }
  // augmentations: AugAdditiveLaplaceNoise
  {
  pybind11::class_<ecvl::AugAdditiveLaplaceNoise, std::unique_ptr<ecvl::AugAdditiveLaplaceNoise, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugAdditiveLaplaceNoise", "Augmentation wrapper for ecvl::AdditiveLaplaceNoise.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("std_dev"));
  }
  // augmentations: AugAdditivePoissonNoise
  {
  pybind11::class_<ecvl::AugAdditivePoissonNoise, std::unique_ptr<ecvl::AugAdditivePoissonNoise, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugAdditivePoissonNoise", "Augmentation wrapper for ecvl::AdditivePoissonNoise.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("lambda"));
  }
  // augmentations: AugGammaContrast
  {
  pybind11::class_<ecvl::AugGammaContrast, std::unique_ptr<ecvl::AugGammaContrast, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugGammaContrast", "Augmentation wrapper for ecvl::GammaContrast.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("gamma"));
  }
  // augmentations: AugCoarseDropout
  {
  pybind11::class_<ecvl::AugCoarseDropout, std::unique_ptr<ecvl::AugCoarseDropout, pybind11::nodelete>, ecvl::Augmentation> cl(m, "AugCoarseDropout", "Augmentation wrapper for ecvl::CoarseDropout.");
  cl.def(pybind11::init<const std::array<double, 2>&, const std::array<double, 2>&, const double&>(), pybind11::arg("p"), pybind11::arg("drop_size"), pybind11::arg("per_channel"));
  }

  // support_eddl: DatasetAugmentations
  {
  pybind11::class_<ecvl::DatasetAugmentations, std::shared_ptr<ecvl::DatasetAugmentations>> cl(m, "DatasetAugmentations", "Dataset Augmentations. Represents the augmentations which will be applied to each split.");
  cl.def(pybind11::init<std::array<ecvl::Augmentation*, 3>>());
  cl.def("Apply", [](ecvl::DatasetAugmentations &o, enum ecvl::SplitType const & a0, class ecvl::Image & a1) -> void { return o.Apply(a0, a1); }, "", pybind11::arg("st"), pybind11::arg("img"));
  cl.def("Apply", (void (ecvl::DatasetAugmentations::*)(enum ecvl::SplitType, class ecvl::Image &, const class ecvl::Image &)) &ecvl::DatasetAugmentations::Apply, "C++: ecvl::DatasetAugmentations::Apply(enum ecvl::SplitType, class ecvl::Image &, const class ecvl::Image &) --> void", pybind11::arg("st"), pybind11::arg("img"), pybind11::arg("gt"));
  }

  // support_eddl: DLDataset
  {
  pybind11::class_<ecvl::DLDataset, std::shared_ptr<ecvl::DLDataset>, ecvl::Dataset> cl(m, "DLDataset", "Extends the DeepHealth Dataset with deep learning specific members");
  cl.def(pybind11::init([](const std::string& filename, const int batch_size) { return new ecvl::DLDataset(filename, batch_size); }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, std::array<ecvl::Augmentation*, 3> augs) {
    ecvl::DatasetAugmentations da(augs);
    return new ecvl::DLDataset(filename, batch_size, std::move(da));
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, std::array<ecvl::Augmentation*, 3> augs, ecvl::ColorType ctype) {
    ecvl::DatasetAugmentations da(augs);
    return new ecvl::DLDataset(filename, batch_size, std::move(da), ctype);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, std::array<ecvl::Augmentation*, 3> augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt) {
    ecvl::DatasetAugmentations da(augs);
    return new ecvl::DLDataset(filename, batch_size, std::move(da), ctype, ctype_gt);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, std::array<ecvl::Augmentation*, 3> augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt, bool verify) {
    ecvl::DatasetAugmentations da(augs);
    return new ecvl::DLDataset(filename, batch_size, std::move(da), ctype, ctype_gt, verify);
  }));
  cl.def_readwrite("batch_size_", &ecvl::DLDataset::batch_size_);
  cl.def_readwrite("n_channels_", &ecvl::DLDataset::n_channels_);
  cl.def_readwrite("n_channels_gt_", &ecvl::DLDataset::n_channels_gt_);
  cl.def_readwrite("current_split_", &ecvl::DLDataset::current_split_);
  cl.def_readwrite("resize_dims_", &ecvl::DLDataset::resize_dims_);
  cl.def_readwrite("current_batch_", &ecvl::DLDataset::current_batch_);
  cl.def_readwrite("ctype_", &ecvl::DLDataset::ctype_);
  cl.def_readwrite("ctype_gt_", &ecvl::DLDataset::ctype_gt_);
  // cl.def_readwrite("augs_", &ecvl::DLDataset::augs_);
  cl.def("GetSplit", (std::vector<int>& (ecvl::DLDataset::*)()) &ecvl::DLDataset::GetSplit, "C++: ecvl::DLDataset::GetSplit() --> std::vector<int>&");
  cl.def("GetSplit", (std::vector<int>& (ecvl::DLDataset::*)(const ecvl::SplitType&)) &ecvl::DLDataset::GetSplit, "C++: ecvl::DLDataset::GetSplit(const ecvl::SplitType&) --> std::vector<int>&");
  cl.def("ResetCurrentBatch", &ecvl::DLDataset::ResetCurrentBatch);
  cl.def("ResetAllBatches", &ecvl::DLDataset::ResetAllBatches);
  cl.def("SetSplit", &ecvl::DLDataset::SetSplit);
  cl.def("LoadBatch", [](ecvl::DLDataset& d, Tensor* images, Tensor* labels) {
    d.LoadBatch(images, labels);
  });
  cl.def("LoadBatch", [](ecvl::DLDataset& d, Tensor* images) {
    d.LoadBatch(images);
  });
  }

  // support_eddl: ImageToTensor
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
