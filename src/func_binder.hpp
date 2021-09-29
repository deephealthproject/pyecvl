// Copyright (c) 2019-2021 CRS4
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
#include <pybind11/chrono.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgcodecs.h>
#include <ecvl/core/imgproc.h>
#ifdef ECVL_EDDL
#include <ecvl/augmentations.h>
#include <ecvl/support_eddl.h>
#include <dataset_addons.hpp>
#endif
#ifdef ECVL_WITH_OPENSLIDE
#include <ecvl/core/support_openslide.h>
#endif
#include <ecvl/core/support_nifti.h>
#ifdef ECVL_WITH_DICOM
#include <ecvl/core/support_dcmtk.h>
#endif


#ifdef ECVL_EDDL
class PyLabel : public ecvl::Label {
public:
    using ecvl::Label::Label;

    void ToTensorPlane(Tensor* tensor, int offset) override {
	PYBIND11_OVERLOAD_PURE(void, ecvl::Label, ToTensorPlane, tensor, offset);
    }
};

class PyAugmentation : public ecvl::Augmentation {
public:
    using ecvl::Augmentation::Augmentation;

    void RealApply(ecvl::Image& img, const ecvl::Image& gt = ecvl::Image()) override {
	PYBIND11_OVERLOAD_PURE(void, ecvl::Augmentation, RealApply, img, gt);
    }

    std::shared_ptr<Augmentation> Clone() const override {
	PYBIND11_OVERLOAD_PURE(std::shared_ptr<Augmentation>, ecvl::Augmentation, Clone);
    }
};
#endif


void bind_ecvl_functions(pybind11::module &m) {

using timedelta = std::chrono::duration<int64_t, std::nano>;

#ifdef ECVL_EDDL
  m.attr("ECVL_EDDL") = pybind11::bool_(true);
#else
  m.attr("ECVL_EDDL") = pybind11::bool_(false);
#endif
#ifdef ECVL_WITH_OPENSLIDE
  m.attr("ECVL_WITH_OPENSLIDE") = pybind11::bool_(true);
#else
  m.attr("ECVL_WITH_OPENSLIDE") = pybind11::bool_(false);
#endif
#ifdef ECVL_WITH_DICOM
  m.attr("ECVL_WITH_DICOM") = pybind11::bool_(true);
#else
  m.attr("ECVL_WITH_DICOM") = pybind11::bool_(false);
#endif

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

  // imgproc
  m.def("ResizeDim", [](const class ecvl::Image& src, class ecvl::Image& dst, const std::vector<int>& newdims) -> void { return ecvl::ResizeDim(src, dst, newdims); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("newdims"));
  m.def("ResizeDim", (void (*)(const class ecvl::Image&, class ecvl::Image&, const std::vector<int>&, enum ecvl::InterpolationType)) &ecvl::ResizeDim, "Resizes an Image to the specified dimensions.\n\nC++: ecvl::ResizeDim(const class ecvl::Image&, class ecvl::Image&, const std::vector<int>&, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("newdims"), pybind11::arg("interp"));
  m.def("ResizeScale", [](const class ecvl::Image& src, class ecvl::Image& dst, const std::vector<double>& scales) -> void { return ecvl::ResizeScale(src, dst, scales); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("scales"));
  m.def("ResizeScale", (void (*)(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, enum ecvl::InterpolationType)) &ecvl::ResizeScale, "Resizes an Image by scaling the dimensions to a given scale factor.\n\nC++: ecvl::ResizeScale(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("scales"), pybind11::arg("interp"));
  m.def("Rotate2D", [](const class ecvl::Image& src, class ecvl::Image& dst, double angle) -> void { return ecvl::Rotate2D(src, dst, angle); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"));
  m.def("Rotate2D", [](const class ecvl::Image& src, class ecvl::Image& dst, double angle, const std::vector<double>& center) -> void { return ecvl::Rotate2D(src, dst, angle, center); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("center"));
  m.def("Rotate2D", [](const class ecvl::Image& src, class ecvl::Image& dst, double angle, const std::vector<double>& center, double scale) -> void { return ecvl::Rotate2D(src, dst, angle, center, scale); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("center"), pybind11::arg("scale"));
  m.def("Rotate2D", (void (*)(const class ecvl::Image&, class ecvl::Image&, double, const std::vector<double>&, double, enum ecvl::InterpolationType)) &ecvl::Rotate2D, "Rotates an Image.\n\nC++: ecvl::Rotate2D(const class ecvl::Image&, class ecvl::Image&, double, const std::vector<double>&, double, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("center"), pybind11::arg("scale"), pybind11::arg("interp"));
  m.def("MultiThreshold", (void (*)(const ecvl::Image&, ecvl::Image&, const std::vector<int>&, int, int)) &ecvl::MultiThreshold, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("thresholds"), pybind11::arg("minval") = 0, pybind11::arg("maxval") = 255);
  m.def("OtsuMultiThreshold", (std::vector<int> (*)(const ecvl::Image&, int)) &ecvl::OtsuMultiThreshold, "", pybind11::arg("src"), pybind11::arg("n_thresholds") = 2);
  m.def("SeparableFilter2D", [](const class ecvl::Image& src, class ecvl::Image& dst, const std::vector<double>& kerX, const std::vector<double>& kerY) -> void { return ecvl::SeparableFilter2D(src, dst, kerX, kerY); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("kerX"), pybind11::arg("kerY"));
  m.def("SeparableFilter2D", (void (*)(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, const std::vector<double>&, enum ecvl::DataType)) &ecvl::SeparableFilter2D, "Convolves an Image with a couple of 1-dimensional kernels.\n\nC++: ecvl::SeparableFilter2D(const class ecvl::Image&, class ecvl::Image&, const std::vector<double>&, const std::vector<double>&, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("kerX"), pybind11::arg("kerY"), pybind11::arg("type"));
  m.def("GetMaxN", (std::vector<std::array<int, 2>> (*)(const class ecvl::Image&, size_t)) &ecvl::GetMaxN, "Get the n maximum values that are in the source Image.\n\nC++: ecvl::GetMaxN(const class ecvl::Image&, size_t) --> std::vector<std::array<int, 2>>", pybind11::arg("src"), pybind11::arg("n"));
  m.def("FindContours", [](const class ecvl::Image& src) -> std::vector<std::vector<std::array<int, 2>>> {
	  std::vector<std::vector<ecvl::Point2i>> contours;
	  ecvl::FindContours(src, contours);
	  return contours;
      }, "Find contours in a binary image");
  m.def("Stack", (void (*)(const std::vector<ecvl::Image>&, class ecvl::Image &)) &ecvl::Stack, "Stack a sequence of Images along a new depth dimension (images dimensions must match)", pybind11::arg("src"), pybind11::arg("dst"));
  m.def("HConcat", (void (*)(const std::vector<ecvl::Image>&, class ecvl::Image &)) &ecvl::HConcat, "Horizontal concatenation of images (with the same number of rows)", pybind11::arg("src"), pybind11::arg("dst"));
  m.def("VConcat", (void (*)(const std::vector<ecvl::Image>&, class ecvl::Image &)) &ecvl::VConcat, "Vertical concatenation of images (with the same number of columns)", pybind11::arg("src"), pybind11::arg("dst"));
  m.def("Morphology", (void (*)(const ecvl::Image&, ecvl::Image&, ecvl::MorphType, ecvl::Image&, ecvl::Point2i, int, ecvl::BorderType, const int&)) &ecvl::Morphology, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("op"), pybind11::arg("kernel"), pybind11::arg("anchor") = std::array<int, 2>({-1, -1}), pybind11::arg("iterations") = 1, pybind11::arg("border_type") = ecvl::BorderType::BORDER_CONSTANT, pybind11::arg("border_value") = 0);
  m.def("Inpaint", (void (*)(const ecvl::Image&, ecvl::Image&, const ecvl::Image&, double, ecvl::InpaintType)) &ecvl::Inpaint, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("inpaintMask"), pybind11::arg("inpaintRadius"), pybind11::arg("flag") = ecvl::InpaintType::INPAINT_TELEA);
  m.def("MeanStdDev", [](const ecvl::Image& src) -> pybind11::tuple {
    std::vector<double> mean;
    std::vector<double> stddev;
    ecvl::MeanStdDev(src, mean, stddev);
    return pybind11::make_tuple(mean, stddev);
  });
  m.def("GridDistortion", (void (*)(const ecvl::Image&, ecvl::Image&, int, const std::array<float, 2>&, ecvl::InterpolationType, ecvl::BorderType, const int&, const unsigned)) &ecvl::GridDistortion, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("num_steps") = 5, pybind11::arg("distort_limit") = std::array<float, 2>({-0.3f, 0.3f}), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("border_type") = ecvl::BorderType::BORDER_REFLECT_101, pybind11::arg("border_value") = 0, pybind11::arg("seed") = std::default_random_engine::default_seed);
  m.def("OpticalDistortion", (void (*)(const ecvl::Image&, ecvl::Image&, const std::array<float, 2>&, const std::array<float, 2>&, ecvl::InterpolationType, ecvl::BorderType, const int&, const unsigned)) &ecvl::OpticalDistortion, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("distort_limit") = std::array<float, 2>({-0.3f, 0.3f}), pybind11::arg("shift_limit") = std::array<float, 2>({-0.1f, 0.1f}), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("border_type") = ecvl::BorderType::BORDER_REFLECT_101, pybind11::arg("border_value") = 0, pybind11::arg("seed") = std::default_random_engine::default_seed);
  m.def("CentralMoments", (void (*)(const ecvl::Image&, ecvl::Image&, std::vector<double>, int, ecvl::DataType)) &ecvl::CentralMoments, "", pybind11::arg("src"), pybind11::arg("moments"), pybind11::arg("center"), pybind11::arg("order") = 3, pybind11::arg("type") = ecvl::DataType::float64);
  m.def("DrawEllipse", (void (*)(ecvl::Image&, ecvl::Point2i, ecvl::Size2i, double, const ecvl::Scalar&, int)) &ecvl::DrawEllipse, "", pybind11::arg("src"), pybind11::arg("center"), pybind11::arg("axes"), pybind11::arg("angle"), pybind11::arg("color"), pybind11::arg("thickness") = 1);
  m.def("DropColorChannel", (void (*)(ecvl::Image&)) &ecvl::DropColorChannel, "", pybind11::arg("src"));
  m.def("Normalize", [](const ecvl::Image& src, ecvl::Image& dst, const std::vector<double>& mean, const std::vector<double>& std) -> void {
    if (mean.size() == 1 && std.size() == 1) {
      // Make it consistent with C++ Normalize(src, dst, {1.2}, {0.2})
      Normalize(src, dst, mean[0], std[0]);
    } else {
      Normalize(src, dst, mean, std);
    }
  });
  m.def("CenterCrop", (void (*)(const ecvl::Image&, ecvl::Image&, const std::vector<int>&)) &ecvl::CenterCrop, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("size"));

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
  pybind11::class_<ecvl::Augmentation, std::shared_ptr<ecvl::Augmentation>, PyAugmentation> cl(m, "Augmentation", "Abstract class which represent a generic Augmentation function.");
  cl.def(pybind11::init<>());
  cl.def_readwrite("params_", &ecvl::Augmentation::params_);
  cl.def("Apply", [](ecvl::Augmentation &o, class ecvl::Image & a0) -> void { return o.Apply(a0); }, "", pybind11::arg("img"));
  cl.def("Apply", (void (ecvl::Augmentation::*)(class ecvl::Image &, const class ecvl::Image &)) &ecvl::Augmentation::Apply, "Generate the random value for each parameter and call the specialized augmentation functions.", pybind11::arg("img"), pybind11::arg("gt"));
  }
  // augmentations: AugmentationFactory
  {
  pybind11::class_<ecvl::AugmentationFactory, std::shared_ptr<ecvl::AugmentationFactory>> cl(m, "AugmentationFactory", "");
  cl.def_static("create", [](std::string& s) -> std::shared_ptr<ecvl::Augmentation> {
    std::stringstream ss(s);
    return ecvl::AugmentationFactory::create(ss);
  }, "", pybind11::arg("is"));
  cl.def_static("create", [](const std::string& name, std::string& s) -> std::shared_ptr<ecvl::Augmentation> {
    std::stringstream ss(s);
    return ecvl::AugmentationFactory::create(name, ss);
  }, "", pybind11::arg("name"), pybind11::arg("is"));
  }
  // augmentations::SequentialAugmentationContainer
  {
  pybind11::class_<ecvl::SequentialAugmentationContainer, std::shared_ptr<ecvl::SequentialAugmentationContainer>, ecvl::Augmentation> cl(m, "SequentialAugmentationContainer", "Represents a container for multiple augmentations which will be sequentially applied to the Dataset images.");
  cl.def(pybind11::init<>());
  cl.def(pybind11::init<std::vector<std::shared_ptr<ecvl::Augmentation>>>());
  cl.def(pybind11::init<const ecvl::SequentialAugmentationContainer&>());
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::SequentialAugmentationContainer((std::istream&)ss);
  }));
  }
  // augmentations::OneOfAugmentationContainer
  {
  pybind11::class_<ecvl::OneOfAugmentationContainer, std::shared_ptr<ecvl::OneOfAugmentationContainer>, ecvl::Augmentation> cl(m, "OneOfAugmentationContainer", "Represents a container for multiple augmentations from which one will be randomly chosen, and applied with a probability specified by the user.");
  cl.def(pybind11::init<double>());
  cl.def(pybind11::init<double, std::vector<std::shared_ptr<ecvl::Augmentation>>>());
  cl.def(pybind11::init<const ecvl::OneOfAugmentationContainer&>());
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::OneOfAugmentationContainer((std::istream&)ss);
  }));
  }
  // augmentations: AugRotate
  {
  pybind11::class_<ecvl::AugRotate, std::shared_ptr<ecvl::AugRotate>, ecvl::Augmentation> cl(m, "AugRotate", "Augmentation wrapper for ecvl::Rotate2D.");
  cl.def(pybind11::init<const std::array<double, 2>&, const std::vector<double>&, const double&, const ecvl::InterpolationType&, const ecvl::InterpolationType&>(), pybind11::arg("angle"), pybind11::arg("center") = std::vector<double>(), pybind11::arg("scale") = 1., pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("gt_interp") = ecvl::InterpolationType::nearest);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugRotate(ss);
  }));
  }
  // augmentations: AugResizeDim
  {
  pybind11::class_<ecvl::AugResizeDim, std::shared_ptr<ecvl::AugResizeDim>, ecvl::Augmentation> cl(m, "AugResizeDim", "Augmentation wrapper for ecvl::ResizeDim.");
  cl.def(pybind11::init<const std::vector<int>&, const ecvl::InterpolationType&, const ecvl::InterpolationType&>(), pybind11::arg("dims"), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("gt_interp") = ecvl::InterpolationType::nearest);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugResizeDim(ss);
  }));
  }
  // augmentations: AugResizeScale
  {
  pybind11::class_<ecvl::AugResizeScale, std::shared_ptr<ecvl::AugResizeScale>, ecvl::Augmentation> cl(m, "AugResizeScale", "Augmentation wrapper for ecvl::ResizeScale.");
  cl.def(pybind11::init<const std::vector<double>&, const ecvl::InterpolationType&, const ecvl::InterpolationType&>(), pybind11::arg("scale"), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("gt_interp") = ecvl::InterpolationType::nearest);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugResizeScale(ss);
  }));
  }
  // augmentations: AugFlip
  {
  pybind11::class_<ecvl::AugFlip, std::shared_ptr<ecvl::AugFlip>, ecvl::Augmentation> cl(m, "AugFlip", "Augmentation wrapper for ecvl::Flip2D.");
  cl.def(pybind11::init<const double &>(), pybind11::arg("p"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugFlip(ss);
  }));
  }
  // augmentations: AugMirror
  {
  pybind11::class_<ecvl::AugMirror, std::shared_ptr<ecvl::AugMirror>, ecvl::Augmentation> cl(m, "AugMirror", "Augmentation wrapper for ecvl::Mirror2D.");
  cl.def(pybind11::init<const double &>(), pybind11::arg("p"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugMirror(ss);
  }));
  }
  // augmentations: AugGaussianBlur
  {
  pybind11::class_<ecvl::AugGaussianBlur, std::shared_ptr<ecvl::AugGaussianBlur>, ecvl::Augmentation> cl(m, "AugGaussianBlur", "Augmentation wrapper for ecvl::GaussianBlur.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("sigma"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugGaussianBlur(ss);
  }));
  }
  // augmentations: AugAdditiveLaplaceNoise
  {
  pybind11::class_<ecvl::AugAdditiveLaplaceNoise, std::shared_ptr<ecvl::AugAdditiveLaplaceNoise>, ecvl::Augmentation> cl(m, "AugAdditiveLaplaceNoise", "Augmentation wrapper for ecvl::AdditiveLaplaceNoise.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("std_dev"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugAdditiveLaplaceNoise(ss);
  }));
  }
  // augmentations: AugAdditivePoissonNoise
  {
  pybind11::class_<ecvl::AugAdditivePoissonNoise, std::shared_ptr<ecvl::AugAdditivePoissonNoise>, ecvl::Augmentation> cl(m, "AugAdditivePoissonNoise", "Augmentation wrapper for ecvl::AdditivePoissonNoise.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("lambda"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugAdditivePoissonNoise(ss);
  }));
  }
  // augmentations: AugGammaContrast
  {
  pybind11::class_<ecvl::AugGammaContrast, std::shared_ptr<ecvl::AugGammaContrast>, ecvl::Augmentation> cl(m, "AugGammaContrast", "Augmentation wrapper for ecvl::GammaContrast.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("gamma"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugGammaContrast(ss);
  }));
  }
  // augmentations: AugCoarseDropout
  {
  pybind11::class_<ecvl::AugCoarseDropout, std::shared_ptr<ecvl::AugCoarseDropout>, ecvl::Augmentation> cl(m, "AugCoarseDropout", "Augmentation wrapper for ecvl::CoarseDropout.");
  cl.def(pybind11::init<const std::array<double, 2>&, const std::array<double, 2>&, const double&>(), pybind11::arg("p"), pybind11::arg("drop_size"), pybind11::arg("per_channel"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugCoarseDropout(ss);
  }));
  }
  // augmentations: AugTranspose
  {
  pybind11::class_<ecvl::AugTranspose, std::shared_ptr<ecvl::AugTranspose>, ecvl::Augmentation> cl(m, "AugTranspose", "Augmentation wrapper for ecvl::Transpose.");
  cl.def(pybind11::init<double>(), pybind11::arg("p"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugTranspose(ss);
  }));
  }
  // augmentations: AugBrightness
  {
  pybind11::class_<ecvl::AugBrightness, std::shared_ptr<ecvl::AugBrightness>, ecvl::Augmentation> cl(m, "AugBrightness", "Augmentation wrapper brightness adjustment.");
  cl.def(pybind11::init<const std::array<double, 2>&>(), pybind11::arg("beta"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugBrightness(ss);
  }));
  }
  // augmentations: AugGridDistortion
  {
  pybind11::class_<ecvl::AugGridDistortion, std::shared_ptr<ecvl::AugGridDistortion>, ecvl::Augmentation> cl(m, "AugGridDistortion", "Augmentation wrapper for ecvl::GridDistortion.");
  cl.def(pybind11::init<const std::array<int, 2>&, const std::array<float, 2>&, const ecvl::InterpolationType&, const ecvl::BorderType&, const int&>(), pybind11::arg("num_steps"), pybind11::arg("distort_limit"), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("border_type") = ecvl::BorderType::BORDER_REFLECT_101, pybind11::arg("border_value") = 0);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugGridDistortion(ss);
  }));
  }
  // augmentations: AugElasticTransform
  {
  pybind11::class_<ecvl::AugElasticTransform, std::shared_ptr<ecvl::AugElasticTransform>, ecvl::Augmentation> cl(m, "AugElasticTransform", "Augmentation wrapper for ecvl::ElasticTransform.");
  cl.def(pybind11::init<const std::array<double, 2>&, const std::array<double, 2>&, const ecvl::InterpolationType&, const ecvl::BorderType&, const int&>(), pybind11::arg("alpha"), pybind11::arg("sigma"), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("border_type") = ecvl::BorderType::BORDER_REFLECT_101, pybind11::arg("border_value") = 0);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugElasticTransform(ss);
  }));
  }
  // augmentations: AugOpticalDistortion
  {
  pybind11::class_<ecvl::AugOpticalDistortion, std::shared_ptr<ecvl::AugOpticalDistortion>, ecvl::Augmentation> cl(m, "AugOpticalDistortion", "Augmentation wrapper for ecvl::OpticalDistortion.");
  cl.def(pybind11::init<const std::array<float, 2>&, const std::array<float, 2>&, const ecvl::InterpolationType&, const ecvl::BorderType&, const int&>(), pybind11::arg("distort_limit"), pybind11::arg("shift_limit"), pybind11::arg("interp") = ecvl::InterpolationType::linear, pybind11::arg("border_type") = ecvl::BorderType::BORDER_REFLECT_101, pybind11::arg("border_value") = 0);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugOpticalDistortion(ss);
  }));
  }
  // augmentations: AugSalt
  {
  pybind11::class_<ecvl::AugSalt, std::shared_ptr<ecvl::AugSalt>, ecvl::Augmentation> cl(m, "AugSalt", "Augmentation wrapper for ecvl::Salt.");
  cl.def(pybind11::init<const std::array<double, 2>&, const double&>(), pybind11::arg("p"), pybind11::arg("per_channel"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugSalt(ss);
  }));
  }
  // augmentations: AugPepper
  {
  pybind11::class_<ecvl::AugPepper, std::shared_ptr<ecvl::AugPepper>, ecvl::Augmentation> cl(m, "AugPepper", "Augmentation wrapper for ecvl::Pepper.");
  cl.def(pybind11::init<const std::array<double, 2>&, const double&>(), pybind11::arg("p"), pybind11::arg("per_channel"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugPepper(ss);
  }));
  }
  // augmentations: AugSaltAndPepper
  {
  pybind11::class_<ecvl::AugSaltAndPepper, std::shared_ptr<ecvl::AugSaltAndPepper>, ecvl::Augmentation> cl(m, "AugSaltAndPepper", "Augmentation wrapper for ecvl::SaltAndPepper.");
  cl.def(pybind11::init<const std::array<double, 2>&, const double&>(), pybind11::arg("p"), pybind11::arg("per_channel"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugSaltAndPepper(ss);
  }));
  }
  // augmentations: AugNormalize
  {
  pybind11::class_<ecvl::AugNormalize, std::shared_ptr<ecvl::AugNormalize>, ecvl::Augmentation> cl(m, "AugNormalize", "Augmentation wrapper for ecvl::Normalize.");
  cl.def(pybind11::init<const double&, const double&>(), pybind11::arg("mean"), pybind11::arg("std"));
  cl.def(pybind11::init<const std::vector<double>&, const std::vector<double>&>(), pybind11::arg("mean"), pybind11::arg("std"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugNormalize(ss);
  }));
  }
  // augmentations: AugCenterCrop
  {
  pybind11::class_<ecvl::AugCenterCrop, std::shared_ptr<ecvl::AugCenterCrop>, ecvl::Augmentation> cl(m, "AugCenterCrop", "Augmentation wrapper for ecvl::CenterCrop.");
  cl.def(pybind11::init<>());
  cl.def(pybind11::init<const std::vector<int>&>(), pybind11::arg("size"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugCenterCrop(ss);
  }));
  }
  // augmentations: AugToFloat32
  {
  pybind11::class_<ecvl::AugToFloat32, std::shared_ptr<ecvl::AugToFloat32>, ecvl::Augmentation> cl(m, "AugToFloat32", "Augmentation ToFloat32.");
  cl.def(pybind11::init<const double&, const double&>(), pybind11::arg("divisor") = 1., pybind11::arg("divisor_gt") = 1.);
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugToFloat32(ss);
  }));
  }
  // augmentations: AugDivBy255
  {
  pybind11::class_<ecvl::AugDivBy255, std::shared_ptr<ecvl::AugDivBy255>, ecvl::Augmentation> cl(m, "AugDivBy255", "Augmentation DivBy255.");
  cl.def(pybind11::init<>());
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugDivBy255(ss);
  }));
  }
  // augmentations: AugScaleTo
  {
  pybind11::class_<ecvl::AugScaleTo, std::shared_ptr<ecvl::AugScaleTo>, ecvl::Augmentation> cl(m, "AugScaleTo", "Augmentation wrapper for ecvl::ScaleTo.");
  cl.def(pybind11::init<const double&, const double&>(), pybind11::arg("new_min"), pybind11::arg("new_max"));
  cl.def(pybind11::init([](const std::string& s) {
    std::stringstream ss(s);
    return new ecvl::AugScaleTo(ss);
  }));
  }

  // support_eddl: DatasetAugmentations
  {
  pybind11::class_<ecvl::DatasetAugmentations, std::shared_ptr<ecvl::DatasetAugmentations>> cl(m, "DatasetAugmentations", "Dataset Augmentations. Represents the augmentations which will be applied to each split.");
  cl.def(pybind11::init<std::vector<std::shared_ptr<ecvl::Augmentation>>>());
  cl.def(pybind11::init<const ecvl::DatasetAugmentations&>());
  cl.def("Apply", [](ecvl::DatasetAugmentations &o, const int a0, ecvl::Image& a1) -> bool { return o.Apply(a0, a1); }, "", pybind11::arg("split"), pybind11::arg("img"));
  cl.def("Apply", (bool (ecvl::DatasetAugmentations::*)(const int, class ecvl::Image &, const class ecvl::Image &)) &ecvl::DatasetAugmentations::Apply, "", pybind11::arg("split"), pybind11::arg("img"), pybind11::arg("gt"));
  cl.def("Apply", [](ecvl::DatasetAugmentations &o, enum ecvl::SplitType const & a0, class ecvl::Image & a1) -> bool { return o.Apply(a0, a1); }, "", pybind11::arg("st"), pybind11::arg("img"));
  cl.def("Apply", (bool (ecvl::DatasetAugmentations::*)(enum ecvl::SplitType, class ecvl::Image &, const class ecvl::Image &)) &ecvl::DatasetAugmentations::Apply, "C++: ecvl::DatasetAugmentations::Apply(enum ecvl::SplitType, class ecvl::Image &, const class ecvl::Image &) --> bool", pybind11::arg("st"), pybind11::arg("img"), pybind11::arg("gt"));
  cl.def("IsEmpty", &ecvl::DatasetAugmentations::IsEmpty);
  }

  // support_eddl: Label
  {
  pybind11::class_<ecvl::Label, std::shared_ptr<ecvl::Label>, PyLabel> cl(m, "Label", "Represents a sample label, which may have different representations depending on the task.");
  cl.def(pybind11::init<>());
  cl.def("ToTensorPlane", &ecvl::Label::ToTensorPlane);
  }

  // support_eddl: LabelClass
  {
  pybind11::class_<ecvl::LabelClass, std::shared_ptr<ecvl::LabelClass>, ecvl::Label> cl(m, "LabelClass", "Label for classification task");
  cl.def(pybind11::init<>());
  cl.def_readwrite("label", &ecvl::LabelClass::label);
  cl.def("ToTensorPlane", &ecvl::LabelClass::ToTensorPlane);
  }

  // support_eddl: LabelImage
  {
  pybind11::class_<ecvl::LabelImage, std::shared_ptr<ecvl::LabelImage>, ecvl::Label> cl(m, "LabelImage", "Label for segmentation task");
  cl.def(pybind11::init<>());
  cl.def_readwrite("gt", &ecvl::LabelImage::gt);
  cl.def("ToTensorPlane", &ecvl::LabelImage::ToTensorPlane);
  }

  // support_eddl: ProducersConsumerQueue
  {
  pybind11::class_<ecvl::ProducersConsumerQueue, std::shared_ptr<ecvl::ProducersConsumerQueue>> cl(m, "ProducersConsumerQueue", "Manages the producers-consumer queue of samples.");
  cl.def(pybind11::init<>());
  cl.def(pybind11::init<unsigned>(), pybind11::arg("mxsz"));
  cl.def(pybind11::init<unsigned, unsigned>(), pybind11::arg("mxsz"), pybind11::arg("thresh"));
  cl.def("Push", [](ecvl::ProducersConsumerQueue& q, const ecvl::Sample& sample, pybind11::object image, const std::shared_ptr<ecvl::Label>& label) -> void {
   // Cast to ecvl::Image crashes with a segfault for empty images
   if (image.attr("IsEmpty")().cast<bool>()) {
     throw std::invalid_argument("image is empty");
   }
   q.Push(sample, image.cast<ecvl::Image>(), label);
  });
  cl.def("Pop", [](ecvl::ProducersConsumerQueue& q) -> pybind11::tuple {
    ecvl::Sample sample;
    ecvl::Image image;
    std::shared_ptr<ecvl::Label> label;
    q.Pop(sample, image, label);
    return pybind11::make_tuple(sample, image, label);
  });
  cl.def("IsFull", &ecvl::ProducersConsumerQueue::IsFull);
  cl.def("IsEmpty", &ecvl::ProducersConsumerQueue::IsEmpty);
  cl.def("Length", &ecvl::ProducersConsumerQueue::Length);
  cl.def("SetSize", [](ecvl::ProducersConsumerQueue& q, int max_size) -> void {
    q.SetSize(max_size);
  });
  cl.def("SetSize", (void (ecvl::ProducersConsumerQueue::*)(int, int)) &ecvl::ProducersConsumerQueue::SetSize, "", pybind11::arg("max_size"), pybind11::arg("thresh"));
  cl.def("Clear", &ecvl::ProducersConsumerQueue::Clear);
  }

  // support_eddl: ThreadCounters
  {
  pybind11::class_<ecvl::ThreadCounters, std::shared_ptr<ecvl::ThreadCounters>> cl(m, "ThreadCounters", "Represents the thread counters.");
  cl.def_readwrite("counter_", &ecvl::ThreadCounters::counter_);
  cl.def_readwrite("min_", &ecvl::ThreadCounters::min_);
  cl.def_readwrite("max_", &ecvl::ThreadCounters::max_);
  cl.def(pybind11::init<int, int>(), pybind11::arg("min"), pybind11::arg("max"));
  cl.def(pybind11::init<int, int, int>(), pybind11::arg("counter"), pybind11::arg("min"), pybind11::arg("max"));
  cl.def("Reset", &ecvl::ThreadCounters::Reset);
  }

  // support_eddl: DLDataset
  {
  pybind11::class_<ecvl::DLDataset, std::shared_ptr<ecvl::DLDataset>, ecvl::Dataset> cl(m, "DLDataset", "Extends the DeepHealth Dataset with deep learning specific members");
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations augs) {
    return new ecvl::DLDataset(filename, batch_size, augs);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations augs, ecvl::ColorType ctype) {
    return new ecvl::DLDataset(filename, batch_size, augs, ctype);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt) {
    return new ecvl::DLDataset(filename, batch_size, augs, ctype, ctype_gt);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations& augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt, int num_workers) {
    return new ecvl::DLDataset(filename, batch_size, augs, ctype, ctype_gt, num_workers);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations& augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt, int num_workers, int queue_ratio_size) {
    return new ecvl::DLDataset(filename, batch_size, augs, ctype, ctype_gt, num_workers, queue_ratio_size);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations& augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt, int num_workers, int queue_ratio_size, std::vector<bool> drop_last) {
    return new ecvl::DLDataset(filename, batch_size, augs, ctype, ctype_gt, num_workers, queue_ratio_size, drop_last);
  }));
  cl.def(pybind11::init([](const std::string& filename, const int batch_size, ecvl::DatasetAugmentations& augs, ecvl::ColorType ctype, ecvl::ColorType ctype_gt, int num_workers, int queue_ratio_size, std::vector<bool> drop_last, bool verify) {
    return new ecvl::DLDataset(filename, batch_size, augs, ctype, ctype_gt, num_workers, queue_ratio_size, drop_last, verify);
  }));
  cl.def_readwrite("n_channels_", &ecvl::DLDataset::n_channels_);
  cl.def_readwrite("n_channels_gt_", &ecvl::DLDataset::n_channels_gt_);
  cl.def_readwrite("resize_dims_", &ecvl::DLDataset::resize_dims_);
  cl.def("ResetBatch", [](ecvl::DLDataset& d) {
	  return d.ResetBatch();
  });
  cl.def("ResetBatch", [](ecvl::DLDataset& d, pybind11::object o) {
	  return d.ResetBatch(toSplit(o));
  });
  cl.def("ResetBatch", [](ecvl::DLDataset& d, pybind11::object o, bool shuffle) {
	  return d.ResetBatch(toSplit(o), shuffle);
  });
  cl.def("ResetAllBatches", &ecvl::DLDataset::ResetAllBatches);
  cl.def("LoadBatch", [](ecvl::DLDataset& d, Tensor* images, Tensor* labels) {
    d.LoadBatch(images, labels);
  });
  cl.def("LoadBatch", [](ecvl::DLDataset& d, Tensor* images) {
    d.LoadBatch(images);
  });
  cl.def("SetSplitSeed", &ecvl::DLDataset::SetSplitSeed);
  cl.def("SetBatchSize", &ecvl::DLDataset::SetBatchSize);
  cl.def("ProduceImageLabel", &ecvl::DLDataset::ProduceImageLabel);
  cl.def("ThreadFunc", &ecvl::DLDataset::ThreadFunc);
  cl.def("GetBatch", &ecvl::DLDataset::GetBatch);
  cl.def("Start", &ecvl::DLDataset::Start);
  cl.def("Stop", &ecvl::DLDataset::Stop);
  cl.def("GetQueueSize", &ecvl::DLDataset::GetQueueSize);
  cl.def("SetAugmentations", &ecvl::DLDataset::SetAugmentations);
  cl.def("GetNumBatches", [](ecvl::DLDataset& d) {
    return d.GetNumBatches();
  });
  cl.def("GetNumBatches", [](ecvl::DLDataset& d, pybind11::object o) {
    return d.GetNumBatches(toSplit(o));
  });
  cl.def("SetWorkers", &ecvl::DLDataset::SetWorkers);
  cl.def("sleep_for", [](ecvl::DLDataset& d, timedelta delta) {
    std::this_thread::sleep_for(delta);
  });

  }

  // support_eddl: ImageToTensor
  m.def("ImageToTensor", [](const ecvl::Image& img) {
    Tensor* t;
    ecvl::ImageToTensor(img, t);
    return t;
  });
  m.def("ImageToTensor", [](const ecvl::Image& img, Tensor* t, int offset) {
    ecvl::ImageToTensor(img, t, offset);
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
  // support_eddl: MakeGrid
  m.def("MakeGrid", [](Tensor* t) {
    return ecvl::MakeGrid(t);
  });
  m.def("MakeGrid", [](Tensor* t, int cols) {
    return ecvl::MakeGrid(t, cols);
  });
  m.def("MakeGrid", [](Tensor* t, int cols, bool normalize) {
    return ecvl::MakeGrid(t, cols, normalize);
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
