// File: ecvl/core/datatype.cpp
#include <array>
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/iterators.h>
#include <func_binder.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_ecvl_core_datatype(std::function< pybind11::module &(std::string const &namespace_) > &M)
{

	// ecvl::DataType file:ecvl/core/datatype.h line:25
	pybind11::enum_<ecvl::DataType>(M("ecvl"), "DataType", "DataType is an enum class which defines\ndata types allowed for images.\n\n  DataType")
		.value("int8", ecvl::DataType::int8)
		.value("int16", ecvl::DataType::int16)
		.value("int32", ecvl::DataType::int32)
		.value("int64", ecvl::DataType::int64)
		.value("float32", ecvl::DataType::float32)
		.value("float64", ecvl::DataType::float64)
		.value("uint8", ecvl::DataType::uint8)
		.value("uint16", ecvl::DataType::uint16)
		.value("none", ecvl::DataType::none);

;

	// ecvl::DataTypeSize(enum ecvl::DataType) file:ecvl/core/datatype.h line:39
	M("ecvl").def("DataTypeSize", (unsigned char (*)(enum ecvl::DataType)) &ecvl::DataTypeSize, "Provides the size in bytes of a given DataType.\n\nGiven one of the \n\n A DataType.\n\n The DataType size in bytes\n\nC++: ecvl::DataTypeSize(enum ecvl::DataType) --> unsigned char", pybind11::arg("dt"));

	// ecvl::DataTypeSize() file:ecvl/core/datatype.h line:55
	M("ecvl").def("DataTypeSize", (unsigned long (*)()) &ecvl::DataTypeSize, "Function to get the number of existing DataType at compile time.\n\n The number of existing DataType.\n\nC++: ecvl::DataTypeSize() --> unsigned long");

	// ecvl::DataTypeSignedSize() file:ecvl/core/datatype.h line:68
	M("ecvl").def("DataTypeSignedSize", (unsigned long (*)()) &ecvl::DataTypeSignedSize, "Function to get the number of existing signed DataType at compile time.\n\n The number of existing signed DataType.\n\nC++: ecvl::DataTypeSignedSize() --> unsigned long");

	{ // ecvl::Iterator file:ecvl/core/iterators.h line:12
		pybind11::class_<ecvl::Iterator<unsigned char>, std::shared_ptr<ecvl::Iterator<unsigned char>>> cl(M("ecvl"), "Iterator_unsigned_char_t", "");
		cl.def( pybind11::init( [](ecvl::Iterator<unsigned char> const &o){ return new ecvl::Iterator<unsigned char>(o); } ) );
		cl.def_readwrite("pos_", &ecvl::Iterator<unsigned char>::pos_);
		cl.def_readwrite("incrementor", &ecvl::Iterator<unsigned char>::incrementor);
		cl.def("plus_plus", (struct ecvl::Iterator<unsigned char> & (ecvl::Iterator<unsigned char>::*)()) &ecvl::Iterator<unsigned char>::operator++, "C++: ecvl::Iterator<unsigned char>::operator++() --> struct ecvl::Iterator<unsigned char> &", pybind11::return_value_policy::automatic);
		cl.def("__mul__", (unsigned char & (ecvl::Iterator<unsigned char>::*)() const) &ecvl::Iterator<unsigned char>::operator*, "C++: ecvl::Iterator<unsigned char>::operator*() const --> unsigned char &", pybind11::return_value_policy::automatic);
		cl.def("__eq__", (bool (ecvl::Iterator<unsigned char>::*)(const struct ecvl::Iterator<unsigned char> &) const) &ecvl::Iterator<unsigned char>::operator==, "C++: ecvl::Iterator<unsigned char>::operator==(const struct ecvl::Iterator<unsigned char> &) const --> bool", pybind11::arg("rhs"));
		cl.def("__ne__", (bool (ecvl::Iterator<unsigned char>::*)(const struct ecvl::Iterator<unsigned char> &) const) &ecvl::Iterator<unsigned char>::operator!=, "C++: ecvl::Iterator<unsigned char>::operator!=(const struct ecvl::Iterator<unsigned char> &) const --> bool", pybind11::arg("rhs"));
	}
	{ // ecvl::Iterator file:ecvl/core/iterators.h line:12
		pybind11::class_<ecvl::Iterator<signed char>, std::shared_ptr<ecvl::Iterator<signed char>>> cl(M("ecvl"), "Iterator_signed_char_t", "");
		cl.def( pybind11::init( [](ecvl::Iterator<signed char> const &o){ return new ecvl::Iterator<signed char>(o); } ) );
		cl.def_readwrite("pos_", &ecvl::Iterator<signed char>::pos_);
		cl.def_readwrite("incrementor", &ecvl::Iterator<signed char>::incrementor);
		cl.def("plus_plus", (struct ecvl::Iterator<signed char> & (ecvl::Iterator<signed char>::*)()) &ecvl::Iterator<signed char>::operator++, "C++: ecvl::Iterator<signed char>::operator++() --> struct ecvl::Iterator<signed char> &", pybind11::return_value_policy::automatic);
		cl.def("__mul__", (signed char & (ecvl::Iterator<signed char>::*)() const) &ecvl::Iterator<signed char>::operator*, "C++: ecvl::Iterator<signed char>::operator*() const --> signed char &", pybind11::return_value_policy::automatic);
		cl.def("__eq__", (bool (ecvl::Iterator<signed char>::*)(const struct ecvl::Iterator<signed char> &) const) &ecvl::Iterator<signed char>::operator==, "C++: ecvl::Iterator<signed char>::operator==(const struct ecvl::Iterator<signed char> &) const --> bool", pybind11::arg("rhs"));
		cl.def("__ne__", (bool (ecvl::Iterator<signed char>::*)(const struct ecvl::Iterator<signed char> &) const) &ecvl::Iterator<signed char>::operator!=, "C++: ecvl::Iterator<signed char>::operator!=(const struct ecvl::Iterator<signed char> &) const --> bool", pybind11::arg("rhs"));
	}
	{ // ecvl::Iterator file:ecvl/core/iterators.h line:12
		pybind11::class_<ecvl::Iterator<short>, std::shared_ptr<ecvl::Iterator<short>>> cl(M("ecvl"), "Iterator_short_t", "");
		cl.def( pybind11::init( [](ecvl::Iterator<short> const &o){ return new ecvl::Iterator<short>(o); } ) );
		cl.def_readwrite("pos_", &ecvl::Iterator<short>::pos_);
		cl.def_readwrite("incrementor", &ecvl::Iterator<short>::incrementor);
		cl.def("plus_plus", (struct ecvl::Iterator<short> & (ecvl::Iterator<short>::*)()) &ecvl::Iterator<short>::operator++, "C++: ecvl::Iterator<short>::operator++() --> struct ecvl::Iterator<short> &", pybind11::return_value_policy::automatic);
		cl.def("__mul__", (short & (ecvl::Iterator<short>::*)() const) &ecvl::Iterator<short>::operator*, "C++: ecvl::Iterator<short>::operator*() const --> short &", pybind11::return_value_policy::automatic);
		cl.def("__eq__", (bool (ecvl::Iterator<short>::*)(const struct ecvl::Iterator<short> &) const) &ecvl::Iterator<short>::operator==, "C++: ecvl::Iterator<short>::operator==(const struct ecvl::Iterator<short> &) const --> bool", pybind11::arg("rhs"));
		cl.def("__ne__", (bool (ecvl::Iterator<short>::*)(const struct ecvl::Iterator<short> &) const) &ecvl::Iterator<short>::operator!=, "C++: ecvl::Iterator<short>::operator!=(const struct ecvl::Iterator<short> &) const --> bool", pybind11::arg("rhs"));
	}
	{ // ecvl::Iterator file:ecvl/core/iterators.h line:12
		pybind11::class_<ecvl::Iterator<float>, std::shared_ptr<ecvl::Iterator<float>>> cl(M("ecvl"), "Iterator_float_t", "");
		cl.def( pybind11::init( [](ecvl::Iterator<float> const &o){ return new ecvl::Iterator<float>(o); } ) );
		cl.def_readwrite("pos_", &ecvl::Iterator<float>::pos_);
		cl.def_readwrite("incrementor", &ecvl::Iterator<float>::incrementor);
		cl.def("plus_plus", (struct ecvl::Iterator<float> & (ecvl::Iterator<float>::*)()) &ecvl::Iterator<float>::operator++, "C++: ecvl::Iterator<float>::operator++() --> struct ecvl::Iterator<float> &", pybind11::return_value_policy::automatic);
		cl.def("__mul__", (float & (ecvl::Iterator<float>::*)() const) &ecvl::Iterator<float>::operator*, "C++: ecvl::Iterator<float>::operator*() const --> float &", pybind11::return_value_policy::automatic);
		cl.def("__eq__", (bool (ecvl::Iterator<float>::*)(const struct ecvl::Iterator<float> &) const) &ecvl::Iterator<float>::operator==, "C++: ecvl::Iterator<float>::operator==(const struct ecvl::Iterator<float> &) const --> bool", pybind11::arg("rhs"));
		cl.def("__ne__", (bool (ecvl::Iterator<float>::*)(const struct ecvl::Iterator<float> &) const) &ecvl::Iterator<float>::operator!=, "C++: ecvl::Iterator<float>::operator!=(const struct ecvl::Iterator<float> &) const --> bool", pybind11::arg("rhs"));
	}
	{ // ecvl::ConstIterator file:ecvl/core/iterators.h line:32
		pybind11::class_<ecvl::ConstIterator<unsigned char>, std::shared_ptr<ecvl::ConstIterator<unsigned char>>> cl(M("ecvl"), "ConstIterator_unsigned_char_t", "");
		cl.def( pybind11::init( [](ecvl::ConstIterator<unsigned char> const &o){ return new ecvl::ConstIterator<unsigned char>(o); } ) );
		cl.def_readwrite("pos_", &ecvl::ConstIterator<unsigned char>::pos_);
		cl.def_readwrite("incrementor", &ecvl::ConstIterator<unsigned char>::incrementor);
		cl.def("plus_plus", (struct ecvl::ConstIterator<unsigned char> & (ecvl::ConstIterator<unsigned char>::*)()) &ecvl::ConstIterator<unsigned char>::operator++, "C++: ecvl::ConstIterator<unsigned char>::operator++() --> struct ecvl::ConstIterator<unsigned char> &", pybind11::return_value_policy::automatic);
		cl.def("__mul__", (const unsigned char & (ecvl::ConstIterator<unsigned char>::*)() const) &ecvl::ConstIterator<unsigned char>::operator*, "C++: ecvl::ConstIterator<unsigned char>::operator*() const --> const unsigned char &", pybind11::return_value_policy::automatic);
		cl.def("__eq__", (bool (ecvl::ConstIterator<unsigned char>::*)(const struct ecvl::ConstIterator<unsigned char> &) const) &ecvl::ConstIterator<unsigned char>::operator==, "C++: ecvl::ConstIterator<unsigned char>::operator==(const struct ecvl::ConstIterator<unsigned char> &) const --> bool", pybind11::arg("rhs"));
		cl.def("__ne__", (bool (ecvl::ConstIterator<unsigned char>::*)(const struct ecvl::ConstIterator<unsigned char> &) const) &ecvl::ConstIterator<unsigned char>::operator!=, "C++: ecvl::ConstIterator<unsigned char>::operator!=(const struct ecvl::ConstIterator<unsigned char> &) const --> bool", pybind11::arg("rhs"));
	}
}


// File: ecvl/core/image.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgproc.h>
#include <ecvl/core/iterators.h>
#include <func_binder.hpp>
#include <image_addons.hpp>
#include <iterator>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_ecvl_core_image(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::MetaData file:ecvl/core/image.h line:19
		pybind11::class_<ecvl::MetaData, std::shared_ptr<ecvl::MetaData>> cl(M("ecvl"), "MetaData", "");
		cl.def("assign", (class ecvl::MetaData & (ecvl::MetaData::*)(const class ecvl::MetaData &)) &ecvl::MetaData::operator=, "C++: ecvl::MetaData::operator=(const class ecvl::MetaData &) --> class ecvl::MetaData &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	// ecvl::ColorType file:ecvl/core/image.h line:29
	pybind11::enum_<ecvl::ColorType>(M("ecvl"), "ColorType", "Enum class representing the ECVL supported color spaces.\n\n ColorType")
		.value("none", ecvl::ColorType::none)
		.value("GRAY", ecvl::ColorType::GRAY)
		.value("RGB", ecvl::ColorType::RGB)
		.value("RGBA", ecvl::ColorType::RGBA)
		.value("BGR", ecvl::ColorType::BGR)
		.value("HSV", ecvl::ColorType::HSV)
		.value("YCbCr", ecvl::ColorType::YCbCr);

;

	{ // ecvl::Image file:ecvl/core/image.h line:52
		pybind11::class_<ecvl::Image, std::shared_ptr<ecvl::Image>> cl(M("ecvl"), "Image", pybind11::buffer_protocol());
		cl.def( pybind11::init( [](){ return new ecvl::Image(); } ) );
		cl.def( pybind11::init( [](ecvl::Image const &o){ return new ecvl::Image(o); } ) );
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def("Begin", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::Begin<unsigned char>, "C++: ecvl::Image::Begin() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("End", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::End<unsigned char>, "C++: ecvl::Image::End() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(class ecvl::Image)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(class ecvl::Image) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Add", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Add(a0); }, "", pybind11::arg("rhs"));
		cl.def("Add", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Add, "In-place addition of an Image. \n\nC++: ecvl::Image::Add(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Sub", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Sub(a0); }, "", pybind11::arg("rhs"));
		cl.def("Sub", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Sub, "In-place subtraction of an Image. \n\nC++: ecvl::Image::Sub(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Mul", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Mul(a0); }, "", pybind11::arg("rhs"));
		cl.def("Mul", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Mul, "In-place multiplication for an Image. \n\nC++: ecvl::Image::Mul(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Div", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Div(a0); }, "", pybind11::arg("rhs"));
		cl.def("Div", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Div, "In-place division for an Image. \n\nC++: ecvl::Image::Div(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));

		image_addons(cl);
	}
	// ecvl::CopyImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/image.h line:839
	M("ecvl").def("CopyImage", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::CopyImage(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("CopyImage", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType)) &ecvl::CopyImage, "Copies the source Image into the destination Image.\n\nThe CopyImage() procedure takes an Image and copies its data into the destination Image.\nSource and destination cannot be the same Image. Source cannot be a Image with DataType::none.\nThe optional new_type parameter can\nbe used to change the DataType of the destination Image. This function is mainly designed to\nchange the DataType of an Image, copying its data into a new Image or to copy an Image into a\nView as a patch. So if you just want to copy an Image as it is, use the copy constructor or =\ninstead. Anyway, the procedure will handle all the possible situations that may happen trying\nto avoid unnecessary allocations.\nWhen the DataType is not specified the function will have the following behaviors:\n    - if the destination Image is empty the source will be directly copied into the destination.\n    - if source and destination have different size in memory or different channels and the destination\n        is the owner of data, the procedure will overwrite the destination Image creating a new Image\n        (channels and dimensions will be the same of the source Image, pixels type (DataType) will be the\n        same of the destination Image if they are not none or the same of the source otherwise).\n    - if source and destination have different size in memory or different channels and the destination is not\n        the owner of data, the procedure will throw an exception.\n    - if source and destination have different color types and the destination is the owner of\n        data, the procedure produces a destination Image with the same color type of the source.\n    - if source and destination have different color types and the destination is not the owner\n        of data, the procedure will throw an exception.\n    - if source and destination are the same Image, there are two options. If new_type is the same of the two\n        Image(s) or it is DataType::none, nothing happens. Otherwise, an exception is thrown.\nWhen the DataType is specified the function will have the same behavior, but the destination Image will have\nthe specified DataType.\n\n Source Image to be copied into destination Image.\n\n Destination Image that will hold a copy of the source Image. Cannot be the source Image.\n\n Desired type for the destination Image after the copy. If none (default) the destination\n            Image will preserve its type if it is not empty, otherwise it will have the same type of the\n            source Image.\n\n CopyImage\n\nC++: ecvl::CopyImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("new_type"));

	// ecvl::ThresholdingType file:ecvl/core/imgproc.h line:12
	pybind11::enum_<ecvl::ThresholdingType>(M("ecvl"), "ThresholdingType", "Enum class representing the ECVL thresholding types.\n\n     ThresholdingType")
		.value("BINARY", ecvl::ThresholdingType::BINARY)
		.value("BINARY_INV", ecvl::ThresholdingType::BINARY_INV);

;

	// ecvl::InterpolationType file:ecvl/core/imgproc.h line:21
	pybind11::enum_<ecvl::InterpolationType>(M("ecvl"), "InterpolationType", "Enum class representing the ECVL interpolation types.\n\n     InterpolationType")
		.value("nearest", ecvl::InterpolationType::nearest)
		.value("linear", ecvl::InterpolationType::linear)
		.value("area", ecvl::InterpolationType::area)
		.value("cubic", ecvl::InterpolationType::cubic)
		.value("lanczos4", ecvl::InterpolationType::lanczos4);

;

	// ecvl::Flip2D(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:66
	M("ecvl").def("Flip2D", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::Flip2D, "Flips an Image\n\nThe Flip2D procedure vertically flips an Image.\n\n The input Image.\n\n The output flipped Image.\n\nC++: ecvl::Flip2D(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::Mirror2D(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:76
	M("ecvl").def("Mirror2D", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::Mirror2D, "Mirrors an Image\n\nThe Mirror2D procedure horizontally flips an Image.\n\n The input Image.\n\n The output mirrored Image.\n\nC++: ecvl::Mirror2D(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::RotateFullImage2D(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType) file:ecvl/core/imgproc.h line:110
	M("ecvl").def("RotateFullImage2D", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2) -> void { return ecvl::RotateFullImage2D(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"));
	M("ecvl").def("RotateFullImage2D", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3) -> void { return ecvl::RotateFullImage2D(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("scale"));
	M("ecvl").def("RotateFullImage2D", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType)) &ecvl::RotateFullImage2D, "Rotates an Image resizing the output accordingly.\n\nThe RotateFullImage2D procedure rotates an Image of a given angle (expressed in degrees) in a clockwise manner.\nThe value of unknown pixels in the output Image are set to 0. The output Image is guaranteed to contain all the pixels\nof the rotated image. Thus, its dimensions can be different from those of the input.\nAn optional scale parameter can be provided. Different interpolation types are available, see \n\n\n The input Image.\n\n The rotated output Image.\n\n The rotation angle in degrees.\n\n Optional scaling factor.\n\n Interpolation type used. Default is InterpolationType::linear.\n\nC++: ecvl::RotateFullImage2D(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("scale"), pybind11::arg("interp"));

	// ecvl::ChangeColorSpace(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType) file:ecvl/core/imgproc.h line:123
	M("ecvl").def("ChangeColorSpace", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType)) &ecvl::ChangeColorSpace, "Copies the source Image into destination Image changing the color space.\n\nThe ChangeColorSpace procedure converts the color space of the source Image into the specified color space.\nNew data are copied into destination Image. Source and destination can be contiguous or not and can also\nbe the same Image.\n\n The input Image to convert in the new color space.\n\n The output Image in the \"new_type\" color space.\n\n The new color space in which the src Image must be converted.\n\nC++: ecvl::ChangeColorSpace(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("new_type"));

	// ecvl::Threshold(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType) file:ecvl/core/imgproc.h line:142
	M("ecvl").def("Threshold", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3) -> void { return ecvl::Threshold(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("thresh"), pybind11::arg("maxval"));
	M("ecvl").def("Threshold", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType)) &ecvl::Threshold, "Applies a fixed threshold to an input Image.\n\nThe Threshold function applies a fixed thresholding to an input Image. The function is useful to get a binary\nimage out of a grayscale (ColorType::GRAY) Image or to remove noise filtering out pixels with too small or too\nlarge values. Anyway, the function can be applied to any input Image.  The pixels up to \"thresh\" value will be\nset to 0, the pixels above this value will be set to \"maxvalue\" if \"thresh_type\" is ThresholdingType::BINARY\n(default). The opposite will happen if \"thresh_type\" is ThresholdingType::BINARY_INV.\n\n Input and output Images may have different color spaces.\n\n Input Image on which to apply the threshold.\n\n The output thresholded Image.\n\n Threshold value.\n\n The maximum values in the thresholded Image.\n\n Type of threshold to be applied, see \n\nC++: ecvl::Threshold(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("thresh"), pybind11::arg("maxval"), pybind11::arg("thresh_type"));

	// ecvl::OtsuThreshold(const class ecvl::Image &) file:ecvl/core/imgproc.h line:152
	M("ecvl").def("OtsuThreshold", (int (*)(const class ecvl::Image &)) &ecvl::OtsuThreshold, "Calculates the Otsu thresholding value.\n\nThe OtsuThreshold function calculates the Otsu threshold value over a given input Image. the Image must by ColorType::GRAY.\n\n Input Image on which to calculate the Otsu threshold value.\n\n Otsu threshold value.\n\nC++: ecvl::OtsuThreshold(const class ecvl::Image &) --> int", pybind11::arg("src"));

	// ecvl::Filter2D(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/imgproc.h line:162
	M("ecvl").def("Filter2D", [](const class ecvl::Image & a0, class ecvl::Image & a1, const class ecvl::Image & a2) -> void { return ecvl::Filter2D(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("ker"));
	M("ecvl").def("Filter2D", (void (*)(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType)) &ecvl::Filter2D, "Convolves an Image with a kernel\n\n Input Image.\n\n Output Image.\n\n Convolution kernel.\n\n Destination ecvl::DataType. If DataType::none, the same of src is used.\n\nC++: ecvl::Filter2D(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("ker"), pybind11::arg("type"));

	// ecvl::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, int, int, double, double) file:ecvl/core/imgproc.h line:185
	M("ecvl").def("GaussianBlur", [](const class ecvl::Image & a0, class ecvl::Image & a1, int const & a2, int const & a3, double const & a4) -> void { return ecvl::GaussianBlur(a0, a1, a2, a3, a4); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("sizeX"), pybind11::arg("sizeY"), pybind11::arg("sigmaX"));
	M("ecvl").def("GaussianBlur", (void (*)(const class ecvl::Image &, class ecvl::Image &, int, int, double, double)) &ecvl::GaussianBlur, "Blurs an Image using a Gaussian kernel.\n\n Input Image.\n\n Output Image.\n\n Horizontal size of the kernel. Must be positive and odd.\n\n Vertical size of the kernel. Must be positive and odd.\n\n Gaussian kernel standard deviation in X direction.\n\n Gaussian kernel standard deviation in Y direction. If zero, sigmaX is used. If both are zero, they are calculted from sizeX and sizeY.\n\nC++: ecvl::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, int, int, double, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("sizeX"), pybind11::arg("sizeY"), pybind11::arg("sigmaX"), pybind11::arg("sigmaY"));

}


// File: ecvl/core/imgproc.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgproc.h>
#include <ecvl/core/iterators.h>
#include <func_binder.hpp>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_ecvl_core_imgproc(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// ecvl::AdditiveLaplaceNoise(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:194
	M("ecvl").def("AdditiveLaplaceNoise", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::AdditiveLaplaceNoise, "Adds Laplace distributed noise to an Image.\n\n Input Image.\n\n Output Image.\n\n Standard deviation of the noise generating distribution. Suggested values are around 255 * 0.05 for uint8 Images.\n\nC++: ecvl::AdditiveLaplaceNoise(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("scale"));

	// ecvl::AdditivePoissonNoise(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:203
	M("ecvl").def("AdditivePoissonNoise", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::AdditivePoissonNoise, "Adds Poisson distributed noise to an Image.\n\n Input Image.\n\n Output Image.\n\n Lambda parameter of the Poisson distribution.\n\nC++: ecvl::AdditivePoissonNoise(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("lambda"));

	// ecvl::GammaContrast(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:211
	M("ecvl").def("GammaContrast", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::GammaContrast, "Adjust contrast by scaling each pixel value X to 255 * ((X/255) ** gamma).\n\n Input Image.\n\n Output Image.\n\n Exponent for the contrast adjustment.\n\nC++: ecvl::GammaContrast(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("gamma"));

	// ecvl::CoarseDropout(const class ecvl::Image &, class ecvl::Image &, double, double, bool) file:ecvl/core/imgproc.h line:222
	M("ecvl").def("CoarseDropout", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, bool)) &ecvl::CoarseDropout, "Sets rectangular areas within an Image to zero.\n\n Input Image.\n\n Output Image.\n\n Probability of any rectangle being set to zero.\n\n Size of rectangles in percentage of the input Image.\n\n Whether to use the same value for all channels of a pixel or not.\n\nC++: ecvl::CoarseDropout(const class ecvl::Image &, class ecvl::Image &, double, double, bool) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("drop_size"), pybind11::arg("per_channel"));

	// ecvl::IntegralImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/imgproc.h line:230
	M("ecvl").def("IntegralImage", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::IntegralImage(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("IntegralImage", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType)) &ecvl::IntegralImage, "Calculate the integral image of the source Image.\n\n Input Image. It must be with ColorType::GRAY, \"xyc\" and DataType::uint8.\n\n Output Image.\n\n DataType of the destination Image.\n\nC++: ecvl::IntegralImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("dst_type"));

	// ecvl::NonMaximaSuppression(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:237
	M("ecvl").def("NonMaximaSuppression", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::NonMaximaSuppression, "Calculate the Non-Maxima suppression of the source Image.\n\n Input Image. It must be with ColorType::GRAY, \"xyc\" and DataType::int32.\n\n Output Image.\n\nC++: ecvl::NonMaximaSuppression(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

}


// File: ecvl/core/imgcodecs.cpp
#include <bits/fs_path.h>
#include <ecvl/core/arithmetic.h>
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgcodecs.h>
#include <ecvl/core/iterators.h>
#include <func_binder.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <string_view>
#include <vector>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_ecvl_core_imgcodecs(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// ecvl::ImReadMode file:ecvl/core/imgcodecs.h line:14
	pybind11::enum_<ecvl::ImReadMode>(M("ecvl"), "ImReadMode", "Enum class representing the ECVL ImRead flags.\n\n     ImReadMode")
		.value("GRAYSCALE", ecvl::ImReadMode::GRAYSCALE)
		.value("COLOR", ecvl::ImReadMode::COLOR);

;

	// ecvl::Neg(class ecvl::Image &) file:ecvl/core/arithmetic.h line:25
	M("ecvl").def("Neg", (class ecvl::Image & (*)(class ecvl::Image &)) &ecvl::Neg, "In-place negation of an Image.  Neg\n\nThe Neg() function negates every value of an Image, and stores the\nthe result in the same image. The type of the image will not change.\n\n Image to be negated (in-place).\n\n Reference to the Image containing the result of the negation.\n\nC++: ecvl::Neg(class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("img"));

	// ecvl::And(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/arithmetic.h line:457
	M("ecvl").def("And", (void (*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &)) &ecvl::And, "Boolean and between two binary ecvl::Image.\n\nPerforms boolean and between two ecvl::Image with DataType::uint8 and ColorType::GRAY.\nThe result is stored into dst.\n\n First ecvl::Image operand.\n\n Second ecvl::Image operand.\n\n Destination ecvl::Image.\n\n.\n\nC++: ecvl::And(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"));

	// ecvl::Or(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/arithmetic.h line:470
	M("ecvl").def("Or", (void (*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &)) &ecvl::Or, "Boolean or between two binary ecvl::Image.\n\nPerforms boolean or between two ecvl::Image with DataType::uint8 and ColorType::GRAY.\nThe result is stored into dst.\n\n First ecvl::Image operand.\n\n Second ecvl::Image operand.\n\n Destination ecvl::Image.\n\n.\n\nC++: ecvl::Or(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"));

}


// File: ecvl/dataset_parser.cpp
#include <bits/fs_path.h>
#include <dataset_addons.hpp>
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/iterators.h>
#include <ecvl/dataset_parser.h>
#include <func_binder.hpp>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <string_view>
#include <vector>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_ecvl_dataset_parser(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::Sample file:ecvl/dataset_parser.h line:21
		pybind11::class_<ecvl::Sample, std::shared_ptr<ecvl::Sample>> cl(M("ecvl"), "Sample", "Sample image in a dataset.\n\nThis class provides the information to describe a dataset sample.\n`label_` and `label_path_` are mutually exclusive.\n Sample");
		cl.def( pybind11::init( [](){ return new ecvl::Sample(); } ) );
		cl.def( pybind11::init( [](ecvl::Sample const &o){ return new ecvl::Sample(o); } ) );
		cl.def_readwrite("location_", &ecvl::Sample::location_);
		cl.def_readwrite("label_", &ecvl::Sample::label_);
		cl.def_readwrite("label_path_", &ecvl::Sample::label_path_);
		cl.def_readwrite("values_", &ecvl::Sample::values_);
		cl.def("LoadImage", [](ecvl::Sample const &o) -> ecvl::Image { return o.LoadImage(); }, "");
		cl.def("LoadImage", [](ecvl::Sample const &o, enum ecvl::ColorType const & a0) -> ecvl::Image { return o.LoadImage(a0); }, "", pybind11::arg("ctype"));
		cl.def("LoadImage", (class ecvl::Image (ecvl::Sample::*)(enum ecvl::ColorType, const bool &) const) &ecvl::Sample::LoadImage, "Return an Image of the dataset.\n\n    The LoadImage() function opens the sample image, from `location_` or `label_path_` depending on `is_gt` parameter.\n\n    \n ecvl::ColorType of the returned Image.\n    \n\n Whether to load the sample image or its ground truth.\n\n    \n Image containing the loaded sample.\n\nC++: ecvl::Sample::LoadImage(enum ecvl::ColorType, const bool &) const --> class ecvl::Image", pybind11::arg("ctype"), pybind11::arg("is_gt"));
	}
	{ // ecvl::Split file:ecvl/dataset_parser.h line:46
		pybind11::class_<ecvl::Split, std::shared_ptr<ecvl::Split>> cl(M("ecvl"), "Split", "Splits of a dataset.\n\nThis class provides the splits a dataset can have: training, validation, and test.\n\n Split");
		cl.def( pybind11::init( [](ecvl::Split const &o){ return new ecvl::Split(o); } ) );
		cl.def( pybind11::init( [](){ return new ecvl::Split(); } ) );
		cl.def_readwrite("training_", &ecvl::Split::training_);
		cl.def_readwrite("validation_", &ecvl::Split::validation_);
		cl.def_readwrite("test_", &ecvl::Split::test_);
		cl.def("assign", (class ecvl::Split & (ecvl::Split::*)(const class ecvl::Split &)) &ecvl::Split::operator=, "C++: ecvl::Split::operator=(const class ecvl::Split &) --> class ecvl::Split &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // ecvl::Dataset file:ecvl/dataset_parser.h line:59
		pybind11::class_<ecvl::Dataset, std::shared_ptr<ecvl::Dataset>> cl(M("ecvl"), "Dataset", "DeepHealth Dataset.\n\nThis class implements the DeepHealth Dataset Format (https://github.com/deephealthproject/ecvl/wiki/DeepHealth-Toolkit-Dataset-Format).\n\n Dataset");
		cl.def( pybind11::init( [](){ return new ecvl::Dataset(); } ) );
		cl.def( pybind11::init( [](ecvl::Dataset const &o){ return new ecvl::Dataset(o); } ) );
		cl.def_readwrite("name_", &ecvl::Dataset::name_);
		cl.def_readwrite("description_", &ecvl::Dataset::description_);
		cl.def_readwrite("classes_", &ecvl::Dataset::classes_);
		cl.def_readwrite("features_", &ecvl::Dataset::features_);
		cl.def_readwrite("samples_", &ecvl::Dataset::samples_);
		cl.def_readwrite("split_", &ecvl::Dataset::split_);

		dataset_addons(cl);
	}
}


// File: ecvl/core/image_1.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/iterators.h>
#include <func_binder.hpp>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_ecvl_core_image_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::View file:ecvl/core/image.h line:466
		pybind11::class_<ecvl::View<ecvl::DataType::int8>, std::shared_ptr<ecvl::View<ecvl::DataType::int8>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_int8_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::int8>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::int8> const &o){ return new ecvl::View<ecvl::DataType::int8>(o); } ) );
		cl.def("Begin", (struct ecvl::Iterator<signed char> (ecvl::View<ecvl::DataType::int8>::*)()) &ecvl::View<ecvl::DataType::int8>::Begin, "C++: ecvl::View<ecvl::DataType::int8>::Begin() --> struct ecvl::Iterator<signed char>");
		cl.def("End", (struct ecvl::Iterator<signed char> (ecvl::View<ecvl::DataType::int8>::*)()) &ecvl::View<ecvl::DataType::int8>::End, "C++: ecvl::View<ecvl::DataType::int8>::End() --> struct ecvl::Iterator<signed char>");
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def("Begin", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::Begin<unsigned char>, "C++: ecvl::Image::Begin() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("End", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::End<unsigned char>, "C++: ecvl::Image::End() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(class ecvl::Image)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(class ecvl::Image) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Add", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Add(a0); }, "", pybind11::arg("rhs"));
		cl.def("Add", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Add, "In-place addition of an Image. \n\nC++: ecvl::Image::Add(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Sub", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Sub(a0); }, "", pybind11::arg("rhs"));
		cl.def("Sub", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Sub, "In-place subtraction of an Image. \n\nC++: ecvl::Image::Sub(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Mul", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Mul(a0); }, "", pybind11::arg("rhs"));
		cl.def("Mul", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Mul, "In-place multiplication for an Image. \n\nC++: ecvl::Image::Mul(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Div", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Div(a0); }, "", pybind11::arg("rhs"));
		cl.def("Div", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Div, "In-place division for an Image. \n\nC++: ecvl::Image::Div(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
	{ // ecvl::View file:ecvl/core/image.h line:466
		pybind11::class_<ecvl::View<ecvl::DataType::int16>, std::shared_ptr<ecvl::View<ecvl::DataType::int16>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_int16_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::int16>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::int16> const &o){ return new ecvl::View<ecvl::DataType::int16>(o); } ) );
		cl.def("Begin", (struct ecvl::Iterator<short> (ecvl::View<ecvl::DataType::int16>::*)()) &ecvl::View<ecvl::DataType::int16>::Begin, "C++: ecvl::View<ecvl::DataType::int16>::Begin() --> struct ecvl::Iterator<short>");
		cl.def("End", (struct ecvl::Iterator<short> (ecvl::View<ecvl::DataType::int16>::*)()) &ecvl::View<ecvl::DataType::int16>::End, "C++: ecvl::View<ecvl::DataType::int16>::End() --> struct ecvl::Iterator<short>");
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def("Begin", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::Begin<unsigned char>, "C++: ecvl::Image::Begin() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("End", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::End<unsigned char>, "C++: ecvl::Image::End() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(class ecvl::Image)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(class ecvl::Image) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Add", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Add(a0); }, "", pybind11::arg("rhs"));
		cl.def("Add", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Add, "In-place addition of an Image. \n\nC++: ecvl::Image::Add(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Sub", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Sub(a0); }, "", pybind11::arg("rhs"));
		cl.def("Sub", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Sub, "In-place subtraction of an Image. \n\nC++: ecvl::Image::Sub(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Mul", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Mul(a0); }, "", pybind11::arg("rhs"));
		cl.def("Mul", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Mul, "In-place multiplication for an Image. \n\nC++: ecvl::Image::Mul(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Div", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Div(a0); }, "", pybind11::arg("rhs"));
		cl.def("Div", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Div, "In-place division for an Image. \n\nC++: ecvl::Image::Div(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
	{ // ecvl::View file:ecvl/core/image.h line:466
		pybind11::class_<ecvl::View<ecvl::DataType::float32>, std::shared_ptr<ecvl::View<ecvl::DataType::float32>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_float32_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::float32>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::float32> const &o){ return new ecvl::View<ecvl::DataType::float32>(o); } ) );
		cl.def("Begin", (struct ecvl::Iterator<float> (ecvl::View<ecvl::DataType::float32>::*)()) &ecvl::View<ecvl::DataType::float32>::Begin, "C++: ecvl::View<ecvl::DataType::float32>::Begin() --> struct ecvl::Iterator<float>");
		cl.def("End", (struct ecvl::Iterator<float> (ecvl::View<ecvl::DataType::float32>::*)()) &ecvl::View<ecvl::DataType::float32>::End, "C++: ecvl::View<ecvl::DataType::float32>::End() --> struct ecvl::Iterator<float>");
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def("Begin", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::Begin<unsigned char>, "C++: ecvl::Image::Begin() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("End", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::End<unsigned char>, "C++: ecvl::Image::End() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(class ecvl::Image)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(class ecvl::Image) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Add", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Add(a0); }, "", pybind11::arg("rhs"));
		cl.def("Add", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Add, "In-place addition of an Image. \n\nC++: ecvl::Image::Add(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Sub", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Sub(a0); }, "", pybind11::arg("rhs"));
		cl.def("Sub", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Sub, "In-place subtraction of an Image. \n\nC++: ecvl::Image::Sub(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Mul", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Mul(a0); }, "", pybind11::arg("rhs"));
		cl.def("Mul", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Mul, "In-place multiplication for an Image. \n\nC++: ecvl::Image::Mul(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Div", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Div(a0); }, "", pybind11::arg("rhs"));
		cl.def("Div", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Div, "In-place division for an Image. \n\nC++: ecvl::Image::Div(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
	{ // ecvl::View file:ecvl/core/image.h line:466
		pybind11::class_<ecvl::View<ecvl::DataType::uint8>, std::shared_ptr<ecvl::View<ecvl::DataType::uint8>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_uint8_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::uint8>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::uint8> const &o){ return new ecvl::View<ecvl::DataType::uint8>(o); } ) );
		cl.def("Begin", (struct ecvl::Iterator<unsigned char> (ecvl::View<ecvl::DataType::uint8>::*)()) &ecvl::View<ecvl::DataType::uint8>::Begin, "C++: ecvl::View<ecvl::DataType::uint8>::Begin() --> struct ecvl::Iterator<unsigned char>");
		cl.def("End", (struct ecvl::Iterator<unsigned char> (ecvl::View<ecvl::DataType::uint8>::*)()) &ecvl::View<ecvl::DataType::uint8>::End, "C++: ecvl::View<ecvl::DataType::uint8>::End() --> struct ecvl::Iterator<unsigned char>");
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def("Begin", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::Begin<unsigned char>, "C++: ecvl::Image::Begin() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("End", (struct ecvl::ConstIterator<unsigned char> (ecvl::Image::*)() const) &ecvl::Image::End<unsigned char>, "C++: ecvl::Image::End() const --> struct ecvl::ConstIterator<unsigned char>");
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(class ecvl::Image)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(class ecvl::Image) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Add", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Add(a0); }, "", pybind11::arg("rhs"));
		cl.def("Add", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Add, "In-place addition of an Image. \n\nC++: ecvl::Image::Add(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Sub", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Sub(a0); }, "", pybind11::arg("rhs"));
		cl.def("Sub", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Sub, "In-place subtraction of an Image. \n\nC++: ecvl::Image::Sub(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Mul", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Mul(a0); }, "", pybind11::arg("rhs"));
		cl.def("Mul", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Mul, "In-place multiplication for an Image. \n\nC++: ecvl::Image::Mul(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("Div", [](ecvl::Image &o, const class ecvl::Image & a0) -> void { return o.Div(a0); }, "", pybind11::arg("rhs"));
		cl.def("Div", (void (ecvl::Image::*)(const class ecvl::Image &, bool)) &ecvl::Image::Div, "In-place division for an Image. \n\nC++: ecvl::Image::Div(const class ecvl::Image &, bool) --> void", pybind11::arg("rhs"), pybind11::arg("saturate"));
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
}


// File: image_ext.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/iterators.h>
#include <func_binder.hpp>
#include <image_ext.hpp>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>
#include <view_float32_addons.hpp>
#include <view_int16_addons.hpp>
#include <view_int8_addons.hpp>
#include <view_uint8_addons.hpp>

#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <pybind11/stl.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*);
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>);
#endif

void bind_image_ext(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::View_int8 file:image_ext.hpp line:4
		pybind11::class_<ecvl::View_int8, std::shared_ptr<ecvl::View_int8>, ecvl::View<ecvl::DataType::int8>> cl(M("ecvl"), "View_int8", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_int8_addons(cl);
	}
	{ // ecvl::View_int16 file:image_ext.hpp line:8
		pybind11::class_<ecvl::View_int16, std::shared_ptr<ecvl::View_int16>, ecvl::View<ecvl::DataType::int16>> cl(M("ecvl"), "View_int16", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_int16_addons(cl);
	}
	{ // ecvl::View_float32 file:image_ext.hpp line:12
		pybind11::class_<ecvl::View_float32, std::shared_ptr<ecvl::View_float32>, ecvl::View<ecvl::DataType::float32>> cl(M("ecvl"), "View_float32", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_float32_addons(cl);
	}
	{ // ecvl::View_uint8 file:image_ext.hpp line:16
		pybind11::class_<ecvl::View_uint8, std::shared_ptr<ecvl::View_uint8>, ecvl::View<ecvl::DataType::uint8>> cl(M("ecvl"), "View_uint8", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_uint8_addons(cl);
	}
	bind_ecvl_functions(M("ecvl"));
}


#include <map>
#include <memory>
#include <stdexcept>
#include <functional>
#include <string>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_ecvl_core_datatype(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_image(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_imgproc(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_imgcodecs(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_dataset_parser(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_image_1(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_image_ext(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(_core, root_module) {
	root_module.doc() = "_core module";

	std::map <std::string, pybind11::module> modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return it->second;
	};

	modules[""] = root_module;

	std::vector< std::pair<std::string, std::string> > sub_modules {
		{"", "ecvl"},
	};
	for(auto &p : sub_modules ) modules[p.first.size() ? p.first+"::"+p.second : p.second] = modules[p.first].def_submodule(p.second.c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() );

	//pybind11::class_<std::shared_ptr<void>>(M(""), "_encapsulated_data_");

	bind_ecvl_core_datatype(M);
	bind_ecvl_core_image(M);
	bind_ecvl_core_imgproc(M);
	bind_ecvl_core_imgcodecs(M);
	bind_ecvl_dataset_parser(M);
	bind_ecvl_core_image_1(M);
	bind_image_ext(M);

}

// Source list file: /pyecvl/codegen/bindings/_core.sources
// _core.cpp
// ecvl/core/datatype.cpp
// ecvl/core/image.cpp
// ecvl/core/imgproc.cpp
// ecvl/core/imgcodecs.cpp
// ecvl/dataset_parser.cpp
// ecvl/core/image_1.cpp
// image_ext.cpp

// Modules list file: /pyecvl/codegen/bindings/_core.modules
// ecvl 
