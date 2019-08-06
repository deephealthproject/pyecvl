// File: ecvl/core/datatype.cpp
#include <array>
#include <ecvl/core/datatype.h>
#include <sstream> // __str__

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
	// ecvl::DataType file:ecvl/core/datatype.h line:15
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

	// ecvl::DataTypeSize(enum ecvl::DataType) file:ecvl/core/datatype.h line:29
	M("ecvl").def("DataTypeSize", (unsigned char (*)(enum ecvl::DataType)) &ecvl::DataTypeSize, "Provides the size in bytes of a given DataType.\n\nGiven one of the \n\n A DataType.\n\n The DataType size in bytes\n\nC++: ecvl::DataTypeSize(enum ecvl::DataType) --> unsigned char", pybind11::arg("dt"));

	// ecvl::DataTypeSize() file:ecvl/core/datatype.h line:45
	M("ecvl").def("DataTypeSize", (unsigned long (*)()) &ecvl::DataTypeSize, "Function to get the number of existing DataType at compile time.\n\n The number of existing DataType.\n\nC++: ecvl::DataTypeSize() --> unsigned long");

	// ecvl::DataTypeSignedSize() file:ecvl/core/datatype.h line:58
	M("ecvl").def("DataTypeSignedSize", (unsigned long (*)()) &ecvl::DataTypeSignedSize, "Function to get the number of existing signed DataType at compile time.\n\n The number of existing signed DataType.\n\nC++: ecvl::DataTypeSignedSize() --> unsigned long");

}


// File: ecvl/core/iterators.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/iterators.h>
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

void bind_ecvl_core_iterators(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::Iterator file:ecvl/core/iterators.h line:12
		pybind11::class_<ecvl::Iterator<signed char>, std::shared_ptr<ecvl::Iterator<signed char>>> cl(M("ecvl"), "Iterator_signed_char_t", "");
		pybind11::handle cl_type = cl;

		cl.def( pybind11::init( [](ecvl::Iterator<signed char> const &o){ return new ecvl::Iterator<signed char>(o); } ) );
		cl.def_readwrite("pos_", &ecvl::Iterator<signed char>::pos_);
		cl.def_readwrite("incrementor", &ecvl::Iterator<signed char>::incrementor);
		cl.def("plus_plus", (struct ecvl::Iterator<signed char> & (ecvl::Iterator<signed char>::*)()) &ecvl::Iterator<signed char>::operator++, "C++: ecvl::Iterator<signed char>::operator++() --> struct ecvl::Iterator<signed char> &", pybind11::return_value_policy::automatic);
		cl.def("__mul__", (signed char & (ecvl::Iterator<signed char>::*)() const) &ecvl::Iterator<signed char>::operator*, "C++: ecvl::Iterator<signed char>::operator*() const --> signed char &", pybind11::return_value_policy::automatic);
		cl.def("__eq__", (bool (ecvl::Iterator<signed char>::*)(const struct ecvl::Iterator<signed char> &) const) &ecvl::Iterator<signed char>::operator==, "C++: ecvl::Iterator<signed char>::operator==(const struct ecvl::Iterator<signed char> &) const --> bool", pybind11::arg("rhs"));
		cl.def("__ne__", (bool (ecvl::Iterator<signed char>::*)(const struct ecvl::Iterator<signed char> &) const) &ecvl::Iterator<signed char>::operator!=, "C++: ecvl::Iterator<signed char>::operator!=(const struct ecvl::Iterator<signed char> &) const --> bool", pybind11::arg("rhs"));
	}
	{ // ecvl::ConstIterator file:ecvl/core/iterators.h line:32
		pybind11::class_<ecvl::ConstIterator<unsigned char>, std::shared_ptr<ecvl::ConstIterator<unsigned char>>> cl(M("ecvl"), "ConstIterator_unsigned_char_t", "");
		pybind11::handle cl_type = cl;

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
#include <ecvl/core/arithmetic.h>
#include <ecvl/core/datatype.h>
#include <ecvl/core/image.h>
#include <ecvl/core/iterators.h>
#include <image_addons.h>
#include <iterator>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <vector>
#include <view_ext.h>
#include <view_int8_addons.h>

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
	{ // ecvl::MetaData file:ecvl/core/image.h line:17
		pybind11::class_<ecvl::MetaData, std::shared_ptr<ecvl::MetaData>> cl(M("ecvl"), "MetaData", "");
		pybind11::handle cl_type = cl;

		cl.def("assign", (class ecvl::MetaData & (ecvl::MetaData::*)(const class ecvl::MetaData &)) &ecvl::MetaData::operator=, "C++: ecvl::MetaData::operator=(const class ecvl::MetaData &) --> class ecvl::MetaData &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	// ecvl::ColorType file:ecvl/core/image.h line:27
	pybind11::enum_<ecvl::ColorType>(M("ecvl"), "ColorType", "Enum class representing the ECVL supported color spaces.\n\n ColorType")
		.value("none", ecvl::ColorType::none)
		.value("GRAY", ecvl::ColorType::GRAY)
		.value("RGB", ecvl::ColorType::RGB)
		.value("RGBA", ecvl::ColorType::RGBA)
		.value("BGR", ecvl::ColorType::BGR)
		.value("HSV", ecvl::ColorType::HSV)
		.value("YCbCr", ecvl::ColorType::YCbCr);

;

	{ // ecvl::Image file:ecvl/core/image.h line:40
		pybind11::class_<ecvl::Image, std::shared_ptr<ecvl::Image>> cl(M("ecvl"), "Image", "Image class");
		pybind11::handle cl_type = cl;

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
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains or not data, regardless the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");

		image_addons(cl);
	}
	{ // ecvl::View file:ecvl/core/image.h line:364
		pybind11::class_<ecvl::View<ecvl::DataType::int8>, std::shared_ptr<ecvl::View<ecvl::DataType::int8>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_int8_t", "");
		pybind11::handle cl_type = cl;

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
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains or not data, regardless the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data. \n\nC++: ecvl::Image::IsOwner() const --> bool");
	}
	// ecvl::CopyImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/image.h line:623
	M("ecvl").def("CopyImage", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::CopyImage(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("CopyImage", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType)) &ecvl::CopyImage, "Copies the source Image into the destination Image.\n\nThe CopyImage() procedure takes an Image and copies its data into the destination Image.\nSource and destination cannot be the same Image. Source cannot be a Image with DataType::none.\nThe optional new_type parameter can \nbe used to change the DataType of the destination Image. This function is mainly designed to \nchange the DataType of an Image, copying its data into a new Image or to copy an Image into a\nView as a patch. So if you just want to copy an Image as it is, use the copy constructor or = \ninstead. Anyway, the procedure will handle all the possible situations that may happen trying \nto avoid unnecessary allocations.\nWhen the DataType is not specified the function will have the following behaviors:\n    - if the destination Image is empty the source will be directly copied into the destination. \n    - if source and destination have different size in memory or different channels and the destination \n        is the owner of data, the procedure will overwrite the destination Image creating a new Image \n        (channels and dimensions will be the same of the source Image, pixels type (DataType) will be the \n        same of the destination Image if they are not none or the same of the source otherwise).\n    - if source and destination have different size in memory or different channels and the destination is not\n        the owner of data, the procedure will throw an exception.\n    - if source and destination have different color types and the destination is the owner of \n        data, the procedure produces a destination Image with the same color type of the source.\n    - if source and destination have different color types and the destination is not the owner \n        of data, the procedure will throw an exception.\n    - if source and destination are the same Image, there are two options. If new_type is the same of the two \n        Image(s) or it is DataType::none, nothing happens. Otherwise, an exception is thrown.\nWhen the DataType is specified the function will have the same behavior, but the destination Image will have \nthe specified DataType.\n\n Source Image to be copied into destination Image.\n\n Destination Image that will hold a copy of the source Image. Cannot be the source Image.\n\n Desired type for the destination Image after the copy. If none (default) the destination \n            Image will preserve its type if it is not empty, otherwise it will have the same type of the \n            source Image. \n\nC++: ecvl::CopyImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("new_type"));

	// ecvl::Neg(class ecvl::Image &) file:ecvl/core/arithmetic.h line:79
	M("ecvl").def("Neg", (class ecvl::Image & (*)(class ecvl::Image &)) &ecvl::Neg, "In-place negation of an Image.  Neg\n\nThe Neg() function negates every value of an Image, and stores the\nthe result in the same image. The type of the image will not change.\n\n Image to be negated (in-place).\n\n Reference to the Image containing the result of the negation.\n\nC++: ecvl::Neg(class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("img"));

	{ // ecvl::View_int8 file:view_ext.h line:4
		pybind11::class_<ecvl::View_int8, std::shared_ptr<ecvl::View_int8>, ecvl::View<ecvl::DataType::int8>> cl(M("ecvl"), "View_int8", "");
		pybind11::handle cl_type = cl;

		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_int8_addons(cl);
	}
}


#include <map>
#include <memory>
#include <stdexcept>
#include <functional>
#include <string>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_ecvl_core_datatype(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_iterators(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_image(std::function< pybind11::module &(std::string const &namespace_) > &M);


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
	bind_ecvl_core_iterators(M);
	bind_ecvl_core_image(M);

}

// Source list file: /pyecvl/codegen/bindings/_core.sources
// _core.cpp
// ecvl/core/datatype.cpp
// ecvl/core/iterators.cpp
// ecvl/core/image.cpp

// Modules list file: /pyecvl/codegen/bindings/_core.modules
// ecvl 
