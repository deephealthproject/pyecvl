#pragma once
#include <pybind11/pybind11.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgcodecs.h>
#include <ecvl/core/imgproc.h>
#include <ecvl/eddl.h>

void bind_ecvl_functions(pybind11::module &m) {
  m.def("RearrangeChannels", &ecvl::RearrangeChannels);
  m.def("ImRead", [](const std::string& filename, ecvl::Image& dst) -> bool {
	  return ecvl::ImRead(filename, dst);
      });
  m.def("ImRead", [](const std::string& filename, ecvl::Image& dst, ecvl::ImageFormat f) -> bool {
	  return ecvl::ImRead(filename, dst, f);
      });
  m.def("ImWrite", [](const std::string& filename, ecvl::Image& src) -> bool {
	  return ecvl::ImWrite(filename, src);
      });
  m.def("ImWrite", [](const std::string& filename, ecvl::Image& src, ecvl::ImageFormat f) -> bool {
	  return ecvl::ImWrite(filename, src, f);
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
  // eddl: ImageToTensor
  m.def("ImageToTensor", &ecvl::ImageToTensor);
  // eddl: TensorToImage
  m.def("TensorToImage", [](Tensor* t) {
    return ecvl::TensorToImage(t);
  });
  m.def("TensorToImage", [](Tensor* t, ecvl::ColorType c_type) {
    return ecvl::TensorToImage(t, c_type);
  });
  // eddl: TensorToView
  m.def("TensorToView", [](Tensor* t) {
    return ecvl::TensorToView(t);
  });
  m.def("TensorToView", [](Tensor* t, ecvl::ColorType c_type) {
    return ecvl::TensorToView(t, c_type);
  });
  // eddl: DLDataset
  pybind11::class_<ecvl::DLDataset, std::shared_ptr<ecvl::DLDataset>, ecvl::Dataset> cl(m, "DLDataset", "");
  cl.def(pybind11::init([](const std::string& filename, int batch_size, std::string split) { return new ecvl::DLDataset(filename, batch_size, split); }));
  cl.def(pybind11::init([](const std::string& filename, int batch_size, std::string split, ecvl::ColorType ctype) { return new ecvl::DLDataset(filename, batch_size, split, ctype); }));
  cl.def_readwrite("batch_size_", &ecvl::DLDataset::batch_size_);
  cl.def_readwrite("current_batch_", &ecvl::DLDataset::current_batch_);
  cl.def_readwrite("n_channels_", &ecvl::DLDataset::n_channels_);
  cl.def_readwrite("ctype_", &ecvl::DLDataset::ctype_);
  cl.def_readwrite("split_str_", &ecvl::DLDataset::split_str_);
  cl.def("GetSplit", &ecvl::DLDataset::GetSplit);
  cl.def("SetSplit", &ecvl::DLDataset::SetSplit);
  // eddl: TrainingToTensor
  m.def("TrainingToTensor", [](const ecvl::Dataset& dataset, const std::vector<int>& size) -> pybind11::tuple {
    Tensor* images;
    Tensor* labels;
    ecvl::TrainingToTensor(dataset, size, images, labels);
    return pybind11::make_tuple(images, labels);
  });
  m.def("TrainingToTensor", [](const ecvl::Dataset& dataset, const std::vector<int>& size, ecvl::ColorType ctype) -> pybind11::tuple {
    Tensor* images;
    Tensor* labels;
    ecvl::TrainingToTensor(dataset, size, images, labels, ctype);
    return pybind11::make_tuple(images, labels);
  });
  // eddl: ValidationToTensor
  m.def("ValidationToTensor", [](const ecvl::Dataset& dataset, const std::vector<int>& size) -> pybind11::tuple {
    Tensor* images;
    Tensor* labels;
    ecvl::ValidationToTensor(dataset, size, images, labels);
    return pybind11::make_tuple(images, labels);
  });
  m.def("ValidationToTensor", [](const ecvl::Dataset& dataset, const std::vector<int>& size, ecvl::ColorType ctype) -> pybind11::tuple {
    Tensor* images;
    Tensor* labels;
    ecvl::ValidationToTensor(dataset, size, images, labels, ctype);
    return pybind11::make_tuple(images, labels);
  });
  // eddl: TestToTensor
  m.def("TestToTensor", [](const ecvl::Dataset& dataset, const std::vector<int>& size) -> pybind11::tuple {
    Tensor* images;
    Tensor* labels;
    ecvl::TestToTensor(dataset, size, images, labels);
    return pybind11::make_tuple(images, labels);
  });
  m.def("TestToTensor", [](const ecvl::Dataset& dataset, const std::vector<int>& size, ecvl::ColorType ctype) -> pybind11::tuple {
    Tensor* images;
    Tensor* labels;
    ecvl::TestToTensor(dataset, size, images, labels, ctype);
    return pybind11::make_tuple(images, labels);
  });
  // eddl: LoadBatch
  m.def("LoadBatch", [](ecvl::DLDataset& dataset, const std::vector<int>& size, Tensor* images, Tensor* labels) {
    return ecvl::LoadBatch(dataset, size, images, labels);
  });
}
