// File: ecvl/core/datatype.cpp
#include <array>
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgproc.h>
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

// ecvl::HardwareAbstractionLayer file:ecvl/core/hal.h line:58
struct PyCallBack_ecvl_HardwareAbstractionLayer : public ecvl::HardwareAbstractionLayer {
	using ecvl::HardwareAbstractionLayer::HardwareAbstractionLayer;

	unsigned char * MemAllocate(unsigned long a0) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "MemAllocate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<unsigned char *>::value) {
				static pybind11::detail::overload_caster_t<unsigned char *> caster;
				return pybind11::detail::cast_ref<unsigned char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<unsigned char *>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"HardwareAbstractionLayer::MemAllocate\"");
	}
	void MemDeallocate(unsigned char * a0) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "MemDeallocate");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"HardwareAbstractionLayer::MemDeallocate\"");
	}
	unsigned char * MemCopy(unsigned char * a0, const unsigned char * a1, unsigned long a2) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "MemCopy");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<unsigned char *>::value) {
				static pybind11::detail::overload_caster_t<unsigned char *> caster;
				return pybind11::detail::cast_ref<unsigned char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<unsigned char *>(std::move(o));
		}
		pybind11::pybind11_fail("Tried to call pure virtual function \"HardwareAbstractionLayer::MemCopy\"");
	}
	unsigned char * MemAllocateAndCopy(unsigned long a0, const unsigned char * a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "MemAllocateAndCopy");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<unsigned char *>::value) {
				static pybind11::detail::overload_caster_t<unsigned char *> caster;
				return pybind11::detail::cast_ref<unsigned char *>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<unsigned char *>(std::move(o));
		}
		return HardwareAbstractionLayer::MemAllocateAndCopy(a0, a1);
	}
	void FromCpu(class ecvl::Image & a0) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "FromCpu");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::FromCpu(a0);
	}
	void ToCpu(class ecvl::Image & a0) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "ToCpu");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::ToCpu(a0);
	}
	void Create(class ecvl::Image & a0) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Create");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Create(a0);
	}
	void Copy(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Copy");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Copy(a0, a1);
	}
	void CopyImage(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "CopyImage");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::CopyImage(a0, a1);
	}
	void Flip2D(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Flip2D");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Flip2D(a0, a1);
	}
	void Mirror2D(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mirror2D");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mirror2D(a0, a1);
	}
	void RotateFullImage2D(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, double a3, enum ecvl::InterpolationType a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "RotateFullImage2D");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::RotateFullImage2D(a0, a1, a2, a3, a4);
	}
	void ChangeColorSpace(const class ecvl::Image & a0, class ecvl::Image & a1, enum ecvl::ColorType a2) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "ChangeColorSpace");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::ChangeColorSpace(a0, a1, a2);
	}
	void Threshold(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, double a3, enum ecvl::ThresholdingType a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Threshold");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Threshold(a0, a1, a2, a3, a4);
	}
	int OtsuThreshold(const class ecvl::Image & a0) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "OtsuThreshold");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<int>::value) {
				static pybind11::detail::overload_caster_t<int> caster;
				return pybind11::detail::cast_ref<int>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<int>(std::move(o));
		}
		return HardwareAbstractionLayer::OtsuThreshold(a0);
	}
	void Filter2D(const class ecvl::Image & a0, class ecvl::Image & a1, const class ecvl::Image & a2, enum ecvl::DataType a3) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Filter2D");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Filter2D(a0, a1, a2, a3);
	}
	void GaussianBlur(const class ecvl::Image & a0, class ecvl::Image & a1, int a2, int a3, double a4, double a5) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "GaussianBlur");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4, a5);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::GaussianBlur(a0, a1, a2, a3, a4, a5);
	}
	void AdditiveLaplaceNoise(const class ecvl::Image & a0, class ecvl::Image & a1, double a2) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "AdditiveLaplaceNoise");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::AdditiveLaplaceNoise(a0, a1, a2);
	}
	void AdditivePoissonNoise(const class ecvl::Image & a0, class ecvl::Image & a1, double a2) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "AdditivePoissonNoise");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::AdditivePoissonNoise(a0, a1, a2);
	}
	void GammaContrast(const class ecvl::Image & a0, class ecvl::Image & a1, double a2) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "GammaContrast");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::GammaContrast(a0, a1, a2);
	}
	void CoarseDropout(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, double a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "CoarseDropout");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::CoarseDropout(a0, a1, a2, a3, a4);
	}
	void IntegralImage(const class ecvl::Image & a0, class ecvl::Image & a1, enum ecvl::DataType a2) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "IntegralImage");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::IntegralImage(a0, a1, a2);
	}
	void NonMaximaSuppression(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "NonMaximaSuppression");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::NonMaximaSuppression(a0, a1);
	}
	void ConnectedComponentsLabeling(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "ConnectedComponentsLabeling");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::ConnectedComponentsLabeling(a0, a1);
	}
	void Inpaint(const class ecvl::Image & a0, class ecvl::Image & a1, const class ecvl::Image & a2, double a3, enum ecvl::InpaintType a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Inpaint");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Inpaint(a0, a1, a2, a3, a4);
	}
	void Transpose(const class ecvl::Image & a0, class ecvl::Image & a1) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Transpose");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Transpose(a0, a1);
	}
	void ElasticTransform(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, double a3, enum ecvl::InterpolationType a4, enum ecvl::BorderType a5, const int & a6, const unsigned int a7) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "ElasticTransform");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4, a5, a6, a7);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::ElasticTransform(a0, a1, a2, a3, a4, a5, a6, a7);
	}
	void Salt(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, bool a3, const unsigned int a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Salt");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Salt(a0, a1, a2, a3, a4);
	}
	void Pepper(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, bool a3, const unsigned int a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Pepper");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Pepper(a0, a1, a2, a3, a4);
	}
	void SaltAndPepper(const class ecvl::Image & a0, class ecvl::Image & a1, double a2, bool a3, const unsigned int a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "SaltAndPepper");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::SaltAndPepper(a0, a1, a2, a3, a4);
	}
	bool IsOwner() const override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "IsOwner");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<bool>::value) {
				static pybind11::detail::overload_caster_t<bool> caster;
				return pybind11::detail::cast_ref<bool>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<bool>(std::move(o));
		}
		return HardwareAbstractionLayer::IsOwner();
	}
	void Neg(const class ecvl::Image & a0, class ecvl::Image & a1, enum ecvl::DataType a2, bool a3) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Neg");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Neg(a0, a1, a2, a3);
	}
	void Add(const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, signed char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(signed char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, signed char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(signed char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, signed char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(signed char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, signed char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(signed char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, int a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(int a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, int a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(int a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, int a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(int a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, int a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(int a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, long a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(long a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, long a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(long a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, long a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(long a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, long a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(long a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, float a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(float a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, float a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(float a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, float a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(float a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, float a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(float a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, double a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(double a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, double a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(double a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, double a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(double a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, double a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(double a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, unsigned char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(unsigned char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, unsigned char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(unsigned char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, unsigned char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(unsigned char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, unsigned char a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(unsigned char a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Add(const class ecvl::Image & a0, unsigned short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Add(unsigned short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Add");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Add(a0, a1, a2, a3, a4);
	}
	void Sub(const class ecvl::Image & a0, unsigned short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Sub(unsigned short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Sub");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Sub(a0, a1, a2, a3, a4);
	}
	void Mul(const class ecvl::Image & a0, unsigned short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Mul(unsigned short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Mul");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Mul(a0, a1, a2, a3, a4);
	}
	void Div(const class ecvl::Image & a0, unsigned short a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
	void Div(unsigned short a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType a3, bool a4) override { 
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const ecvl::HardwareAbstractionLayer *>(this), "Div");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3, a4);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::overload_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return HardwareAbstractionLayer::Div(a0, a1, a2, a3, a4);
	}
};

void bind_ecvl_core_datatype(std::function< pybind11::module &(std::string const &namespace_) > &M)
{

	// ecvl::DataType file:ecvl/core/datatype.h line:39
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

	// ecvl::DataTypeSize(enum ecvl::DataType) file:ecvl/core/datatype.h line:53
	M("ecvl").def("DataTypeSize", (unsigned char (*)(enum ecvl::DataType)) &ecvl::DataTypeSize, "Provides the size in bytes of a given DataType.\n\nGiven one of the \n\n A DataType.\n\n The DataType size in bytes\n\nC++: ecvl::DataTypeSize(enum ecvl::DataType) --> unsigned char", pybind11::arg("dt"));

	// ecvl::DataTypeSize() file:ecvl/core/datatype.h line:69
	M("ecvl").def("DataTypeSize", (unsigned long (*)()) &ecvl::DataTypeSize, "Function to get the number of existing DataType at compile time.\n\n The number of existing DataType.\n\nC++: ecvl::DataTypeSize() --> unsigned long");

	// ecvl::DataTypeSignedSize() file:ecvl/core/datatype.h line:82
	M("ecvl").def("DataTypeSignedSize", (unsigned long (*)()) &ecvl::DataTypeSignedSize, "Function to get the number of existing signed DataType at compile time.\n\n The number of existing signed DataType.\n\nC++: ecvl::DataTypeSignedSize() --> unsigned long");

	// ecvl::Device file:ecvl/core/hal.h line:30
	pybind11::enum_<ecvl::Device>(M("ecvl"), "Device", "Enum class representing the ECVL available devices\n\n Device")
		.value("NONE", ecvl::Device::NONE)
		.value("CPU", ecvl::Device::CPU)
		.value("GPU", ecvl::Device::GPU)
		.value("FPGA", ecvl::Device::FPGA);

;

	// ecvl::ThresholdingType file:ecvl/core/hal.h line:38
	pybind11::enum_<ecvl::ThresholdingType>(M("ecvl"), "ThresholdingType", "")
		.value("BINARY", ecvl::ThresholdingType::BINARY)
		.value("BINARY_INV", ecvl::ThresholdingType::BINARY_INV);

;

	// ecvl::InterpolationType file:ecvl/core/hal.h line:39
	pybind11::enum_<ecvl::InterpolationType>(M("ecvl"), "InterpolationType", "")
		.value("nearest", ecvl::InterpolationType::nearest)
		.value("linear", ecvl::InterpolationType::linear)
		.value("area", ecvl::InterpolationType::area)
		.value("cubic", ecvl::InterpolationType::cubic)
		.value("lanczos4", ecvl::InterpolationType::lanczos4);

;

	// ecvl::ColorType file:ecvl/core/hal.h line:40
	pybind11::enum_<ecvl::ColorType>(M("ecvl"), "ColorType", "")
		.value("none", ecvl::ColorType::none)
		.value("GRAY", ecvl::ColorType::GRAY)
		.value("RGB", ecvl::ColorType::RGB)
		.value("RGBA", ecvl::ColorType::RGBA)
		.value("BGR", ecvl::ColorType::BGR)
		.value("HSV", ecvl::ColorType::HSV)
		.value("YCbCr", ecvl::ColorType::YCbCr);

;

	// ecvl::MorphType file:ecvl/core/hal.h line:41
	pybind11::enum_<ecvl::MorphType>(M("ecvl"), "MorphType", "")
		.value("MORPH_ERODE", ecvl::MorphType::MORPH_ERODE)
		.value("MORPH_DILATE", ecvl::MorphType::MORPH_DILATE)
		.value("MORPH_OPEN", ecvl::MorphType::MORPH_OPEN)
		.value("MORPH_CLOSE", ecvl::MorphType::MORPH_CLOSE)
		.value("MORPH_GRADIENT", ecvl::MorphType::MORPH_GRADIENT)
		.value("MORPH_TOPHAT", ecvl::MorphType::MORPH_TOPHAT)
		.value("MORPH_BLACKHAT", ecvl::MorphType::MORPH_BLACKHAT)
		.value("MORPH_HITMISS", ecvl::MorphType::MORPH_HITMISS);

;

	// ecvl::InpaintType file:ecvl/core/hal.h line:42
	pybind11::enum_<ecvl::InpaintType>(M("ecvl"), "InpaintType", "")
		.value("INPAINT_NS", ecvl::InpaintType::INPAINT_NS)
		.value("INPAINT_TELEA", ecvl::InpaintType::INPAINT_TELEA);

;

	// ecvl::BorderType file:ecvl/core/hal.h line:43
	pybind11::enum_<ecvl::BorderType>(M("ecvl"), "BorderType", "")
		.value("BORDER_CONSTANT", ecvl::BorderType::BORDER_CONSTANT)
		.value("BORDER_REPLICATE", ecvl::BorderType::BORDER_REPLICATE)
		.value("BORDER_REFLECT", ecvl::BorderType::BORDER_REFLECT)
		.value("BORDER_WRAP", ecvl::BorderType::BORDER_WRAP)
		.value("BORDER_REFLECT_101", ecvl::BorderType::BORDER_REFLECT_101)
		.value("BORDER_TRANSPARENT", ecvl::BorderType::BORDER_TRANSPARENT);

;

	{ // ecvl::HardwareAbstractionLayer file:ecvl/core/hal.h line:58
		pybind11::class_<ecvl::HardwareAbstractionLayer, std::shared_ptr<ecvl::HardwareAbstractionLayer>, PyCallBack_ecvl_HardwareAbstractionLayer> cl(M("ecvl"), "HardwareAbstractionLayer", "Hardware Abstraction Layer (HAL) is an abstraction layer to interact with a hardware device at a\n    general level\n\n    HAL is an interface that allows ECVL to interact with hardwares devices at a general or abstract level\n    rather than at a detailed hardware level. It represents a proxy to the actual function implementations\n    that must be device specific.\n\n    Actual HALs must inherit from this base class. Most of the memory handling methods must be overwritten.\n    This base class also provides some general methods that can be shared by different devices.");
		cl.def( pybind11::init( [](){ return new PyCallBack_ecvl_HardwareAbstractionLayer(); } ) );
		cl.def_static("Factory", [](enum ecvl::Device const & a0) -> ecvl::HardwareAbstractionLayer * { return ecvl::HardwareAbstractionLayer::Factory(a0); }, "", pybind11::return_value_policy::automatic, pybind11::arg("dev"));
		cl.def_static("Factory", (class ecvl::HardwareAbstractionLayer * (*)(enum ecvl::Device, bool)) &ecvl::HardwareAbstractionLayer::Factory, "C++: ecvl::HardwareAbstractionLayer::Factory(enum ecvl::Device, bool) --> class ecvl::HardwareAbstractionLayer *", pybind11::return_value_policy::automatic, pybind11::arg("dev"), pybind11::arg("shallow"));
		cl.def("MemAllocate", (unsigned char * (ecvl::HardwareAbstractionLayer::*)(unsigned long)) &ecvl::HardwareAbstractionLayer::MemAllocate, "C++: ecvl::HardwareAbstractionLayer::MemAllocate(unsigned long) --> unsigned char *", pybind11::return_value_policy::automatic, pybind11::arg("nbytes"));
		cl.def("MemDeallocate", (void (ecvl::HardwareAbstractionLayer::*)(unsigned char *)) &ecvl::HardwareAbstractionLayer::MemDeallocate, "C++: ecvl::HardwareAbstractionLayer::MemDeallocate(unsigned char *) --> void", pybind11::arg("data"));
		cl.def("MemCopy", (unsigned char * (ecvl::HardwareAbstractionLayer::*)(unsigned char *, const unsigned char *, unsigned long)) &ecvl::HardwareAbstractionLayer::MemCopy, "C++: ecvl::HardwareAbstractionLayer::MemCopy(unsigned char *, const unsigned char *, unsigned long) --> unsigned char *", pybind11::return_value_policy::automatic, pybind11::arg("dst"), pybind11::arg("src"), pybind11::arg("nbytes"));
		cl.def("MemAllocateAndCopy", (unsigned char * (ecvl::HardwareAbstractionLayer::*)(unsigned long, const unsigned char *)) &ecvl::HardwareAbstractionLayer::MemAllocateAndCopy, "C++: ecvl::HardwareAbstractionLayer::MemAllocateAndCopy(unsigned long, const unsigned char *) --> unsigned char *", pybind11::return_value_policy::automatic, pybind11::arg("nbytes"), pybind11::arg("src"));
		cl.def("FromCpu", (void (ecvl::HardwareAbstractionLayer::*)(class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::FromCpu, "C++: ecvl::HardwareAbstractionLayer::FromCpu(class ecvl::Image &) --> void", pybind11::arg("src"));
		cl.def("ToCpu", (void (ecvl::HardwareAbstractionLayer::*)(class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::ToCpu, "C++: ecvl::HardwareAbstractionLayer::ToCpu(class ecvl::Image &) --> void", pybind11::arg("src"));
		cl.def("Create", (void (ecvl::HardwareAbstractionLayer::*)(class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::Create, "Specific function which allocates data for a partially initialized image object\n\n        This function delegates the operation of creating image data to the specific HAL. The default\n        version assumes a contiguous image, so the strides are exactly those expected from the dims_ vector.\n        Specific HALs could change the memory layout by operating on the specific fields.\n\nC++: ecvl::HardwareAbstractionLayer::Create(class ecvl::Image &) --> void", pybind11::arg("img"));
		cl.def("Copy", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::Copy, "C++: ecvl::HardwareAbstractionLayer::Copy(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("CopyImage", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::CopyImage, "Function for copying data from image of one type to one of another type\n\n        Probably this could be merged with Copy. The idea is to have a function which allows for changing\n        the datatype. Nevertheless, dst data has already been correctly initialized.\n\nC++: ecvl::HardwareAbstractionLayer::CopyImage(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("Flip2D", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::Flip2D, "C++: ecvl::HardwareAbstractionLayer::Flip2D(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("Mirror2D", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::Mirror2D, "C++: ecvl::HardwareAbstractionLayer::Mirror2D(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("RotateFullImage2D", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType)) &ecvl::HardwareAbstractionLayer::RotateFullImage2D, "C++: ecvl::HardwareAbstractionLayer::RotateFullImage2D(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("scale"), pybind11::arg("interp"));
		cl.def("ChangeColorSpace", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType)) &ecvl::HardwareAbstractionLayer::ChangeColorSpace, "C++: ecvl::HardwareAbstractionLayer::ChangeColorSpace(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("new_type"));
		cl.def("Threshold", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType)) &ecvl::HardwareAbstractionLayer::Threshold, "C++: ecvl::HardwareAbstractionLayer::Threshold(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("thresh"), pybind11::arg("maxval"), pybind11::arg("thresh_type"));
		cl.def("OtsuThreshold", (int (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::OtsuThreshold, "C++: ecvl::HardwareAbstractionLayer::OtsuThreshold(const class ecvl::Image &) --> int", pybind11::arg("src"));
		cl.def("Filter2D", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType)) &ecvl::HardwareAbstractionLayer::Filter2D, "C++: ecvl::HardwareAbstractionLayer::Filter2D(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("ker"), pybind11::arg("type"));
		cl.def("GaussianBlur", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, int, int, double, double)) &ecvl::HardwareAbstractionLayer::GaussianBlur, "C++: ecvl::HardwareAbstractionLayer::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, int, int, double, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("sizeX"), pybind11::arg("sizeY"), pybind11::arg("sigmaX"), pybind11::arg("sigmaY"));
		cl.def("AdditiveLaplaceNoise", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::HardwareAbstractionLayer::AdditiveLaplaceNoise, "C++: ecvl::HardwareAbstractionLayer::AdditiveLaplaceNoise(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("std_dev"));
		cl.def("AdditivePoissonNoise", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::HardwareAbstractionLayer::AdditivePoissonNoise, "C++: ecvl::HardwareAbstractionLayer::AdditivePoissonNoise(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("lambda"));
		cl.def("GammaContrast", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::HardwareAbstractionLayer::GammaContrast, "C++: ecvl::HardwareAbstractionLayer::GammaContrast(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("gamma"));
		cl.def("CoarseDropout", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, double, bool)) &ecvl::HardwareAbstractionLayer::CoarseDropout, "C++: ecvl::HardwareAbstractionLayer::CoarseDropout(const class ecvl::Image &, class ecvl::Image &, double, double, bool) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("drop_size"), pybind11::arg("per_channel"));
		cl.def("IntegralImage", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType)) &ecvl::HardwareAbstractionLayer::IntegralImage, "C++: ecvl::HardwareAbstractionLayer::IntegralImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("dst_type"));
		cl.def("NonMaximaSuppression", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::NonMaximaSuppression, "C++: ecvl::HardwareAbstractionLayer::NonMaximaSuppression(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("ConnectedComponentsLabeling", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::ConnectedComponentsLabeling, "C++: ecvl::HardwareAbstractionLayer::ConnectedComponentsLabeling(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("Inpaint", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, double, enum ecvl::InpaintType)) &ecvl::HardwareAbstractionLayer::Inpaint, "C++: ecvl::HardwareAbstractionLayer::Inpaint(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, double, enum ecvl::InpaintType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("inpaintMask"), pybind11::arg("inpaintRadius"), pybind11::arg("flag"));
		cl.def("Transpose", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::HardwareAbstractionLayer::Transpose, "C++: ecvl::HardwareAbstractionLayer::Transpose(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));
		cl.def("ElasticTransform", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType, enum ecvl::BorderType, const int &, const unsigned int)) &ecvl::HardwareAbstractionLayer::ElasticTransform, "C++: ecvl::HardwareAbstractionLayer::ElasticTransform(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType, enum ecvl::BorderType, const int &, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"), pybind11::arg("sigma"), pybind11::arg("interp"), pybind11::arg("border_type"), pybind11::arg("border_value"), pybind11::arg("seed"));
		cl.def("Salt", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int)) &ecvl::HardwareAbstractionLayer::Salt, "C++: ecvl::HardwareAbstractionLayer::Salt(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"), pybind11::arg("seed"));
		cl.def("Pepper", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int)) &ecvl::HardwareAbstractionLayer::Pepper, "C++: ecvl::HardwareAbstractionLayer::Pepper(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"), pybind11::arg("seed"));
		cl.def("SaltAndPepper", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int)) &ecvl::HardwareAbstractionLayer::SaltAndPepper, "C++: ecvl::HardwareAbstractionLayer::SaltAndPepper(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"), pybind11::arg("seed"));
		cl.def("IsOwner", (bool (ecvl::HardwareAbstractionLayer::*)() const) &ecvl::HardwareAbstractionLayer::IsOwner, "C++: ecvl::HardwareAbstractionLayer::IsOwner() const --> bool");
		cl.def("Neg", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Neg, "C++: ecvl::HardwareAbstractionLayer::Neg(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, signed char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(signed char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, int, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(int, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, long, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(long, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, float, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(float, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, double, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(double, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, unsigned char, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(unsigned char, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Add", (void (ecvl::HardwareAbstractionLayer::*)(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Add, "C++: ecvl::HardwareAbstractionLayer::Add(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Sub", (void (ecvl::HardwareAbstractionLayer::*)(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Sub, "C++: ecvl::HardwareAbstractionLayer::Sub(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Mul", (void (ecvl::HardwareAbstractionLayer::*)(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Mul, "C++: ecvl::HardwareAbstractionLayer::Mul(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(const class ecvl::Image &, unsigned short, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("Div", (void (ecvl::HardwareAbstractionLayer::*)(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::HardwareAbstractionLayer::Div, "C++: ecvl::HardwareAbstractionLayer::Div(unsigned short, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));
		cl.def("assign", (class ecvl::HardwareAbstractionLayer & (ecvl::HardwareAbstractionLayer::*)(const class ecvl::HardwareAbstractionLayer &)) &ecvl::HardwareAbstractionLayer::operator=, "C++: ecvl::HardwareAbstractionLayer::operator=(const class ecvl::HardwareAbstractionLayer &) --> class ecvl::HardwareAbstractionLayer &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}


// File: ecvl/core/image.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <func_binder.hpp>
#include <image_addons.hpp>
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

void bind_ecvl_core_image(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::MetaData file:ecvl/core/image.h line:39
		pybind11::class_<ecvl::MetaData, std::shared_ptr<ecvl::MetaData>> cl(M("ecvl"), "MetaData", "");
		cl.def("assign", (class ecvl::MetaData & (ecvl::MetaData::*)(const class ecvl::MetaData &)) &ecvl::MetaData::operator=, "C++: ecvl::MetaData::operator=(const class ecvl::MetaData &) --> class ecvl::MetaData &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // ecvl::Image file:ecvl/core/image.h line:72
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
		cl.def_readwrite("dev_", &ecvl::Image::dev_);
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("To", (void (ecvl::Image::*)(enum ecvl::Device)) &ecvl::Image::To, "C++: ecvl::Image::To(enum ecvl::Device) --> void", pybind11::arg("dev"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data.\n\n        \n Move the implementation to the specific hals if other shallow hals will be introduced.\n\n    \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Width", (int (ecvl::Image::*)() const) &ecvl::Image::Width, "Returns the width of Image. \n\nC++: ecvl::Image::Width() const --> int");
		cl.def("Height", (int (ecvl::Image::*)() const) &ecvl::Image::Height, "Returns the height of Image. \n\nC++: ecvl::Image::Height() const --> int");
		cl.def("Neg", (void (ecvl::Image::*)()) &ecvl::Image::Neg, "In-place negation. \n\nC++: ecvl::Image::Neg() --> void");
		cl.def("__sub__", (class ecvl::Image (ecvl::Image::*)() const) &ecvl::Image::operator-, "C++: ecvl::Image::operator-() const --> class ecvl::Image");
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));

		image_addons(cl);
	}
	// ecvl::CopyImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/image.h line:900
	M("ecvl").def("CopyImage", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::CopyImage(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("CopyImage", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType)) &ecvl::CopyImage, "Copies the source Image into the destination Image.\n\nThe CopyImage() procedure takes an Image and copies its data into the destination Image.\nSource and destination cannot be the same Image. Source cannot be a Image with DataType::none.\nThe optional new_type parameter can\nbe used to change the DataType of the destination Image. This function is mainly designed to\nchange the DataType of an Image, copying its data into a new Image or to copy an Image into a\nView as a patch. So if you just want to copy an Image as it is, use the copy constructor or =\ninstead. Anyway, the procedure will handle all the possible situations that may happen trying\nto avoid unnecessary allocations.\nWhen the DataType is not specified the function will have the following behaviors:\n    - if the destination Image is empty the source will be directly copied into the destination.\n    - if source and destination have different size in memory or different channels and the destination\n        is the owner of data, the procedure will overwrite the destination Image creating a new Image\n        (channels and dimensions will be the same of the source Image, pixels type (DataType) will be the\n        same of the destination Image if they are not none or the same of the source otherwise).\n    - if source and destination have different size in memory or different channels and the destination is not\n        the owner of data, the procedure will throw an exception.\n    - if source and destination have different color types and the destination is the owner of\n        data, the procedure produces a destination Image with the same color type of the source.\n    - if source and destination have different color types and the destination is not the owner\n        of data, the procedure will throw an exception.\n    - if source and destination are the same Image, there are two options. If new_type is the same of the two\n        Image(s) or it is DataType::none, nothing happens. Otherwise, an exception is thrown.\nWhen the DataType is specified the function will have the same behavior, but the destination Image will have\nthe specified DataType.\n\n Source Image to be copied into destination Image.\n\n Destination Image that will hold a copy of the source Image. Cannot be the source Image.\n\n Desired type for the destination Image after the copy. If none (default) the destination\n            Image will preserve its type if it is not empty, otherwise it will have the same type of the\n            source Image.\n\n CopyImage\n\nC++: ecvl::CopyImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("new_type"));

}


// File: ecvl/core/imgproc.cpp
#include <array>
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgproc.h>
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
	// ecvl::GetOpenCVInterpolation(enum ecvl::InterpolationType) file:ecvl/core/imgproc.h line:55
	M("ecvl").def("GetOpenCVInterpolation", (int (*)(enum ecvl::InterpolationType)) &ecvl::GetOpenCVInterpolation, "Given an InterpolationType, the GetOpenCVInterpolation function returns the associated OpenCV enum value.\n\n Interpolation type, see \n\n Associated OpenCV enum value.\n\nC++: ecvl::GetOpenCVInterpolation(enum ecvl::InterpolationType) --> int", pybind11::arg("interp"));

	// ecvl::Flip2D(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:91
	M("ecvl").def("Flip2D", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::Flip2D, "Flips an Image\n\nThe Flip2D procedure vertically flips an Image.\n\n The input Image.\n\n The output flipped Image.\n\nC++: ecvl::Flip2D(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::Mirror2D(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:101
	M("ecvl").def("Mirror2D", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::Mirror2D, "Mirrors an Image\n\nThe Mirror2D procedure horizontally flips an Image.\n\n The input Image.\n\n The output mirrored Image.\n\nC++: ecvl::Mirror2D(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::RotateFullImage2D(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType) file:ecvl/core/imgproc.h line:135
	M("ecvl").def("RotateFullImage2D", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2) -> void { return ecvl::RotateFullImage2D(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"));
	M("ecvl").def("RotateFullImage2D", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3) -> void { return ecvl::RotateFullImage2D(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("scale"));
	M("ecvl").def("RotateFullImage2D", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType)) &ecvl::RotateFullImage2D, "Rotates an Image resizing the output accordingly.\n\nThe RotateFullImage2D procedure rotates an Image of a given angle (expressed in degrees) in a clockwise manner.\nThe value of unknown pixels in the output Image are set to 0. The output Image is guaranteed to contain all the pixels\nof the rotated image. Thus, its dimensions can be different from those of the input.\nAn optional scale parameter can be provided. Different interpolation types are available, see \n\n\n The input Image.\n\n The rotated output Image.\n\n The rotation angle in degrees.\n\n Optional scaling factor.\n\n Interpolation type used. Default is InterpolationType::linear.\n\nC++: ecvl::RotateFullImage2D(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("angle"), pybind11::arg("scale"), pybind11::arg("interp"));

	// ecvl::ChangeColorSpace(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType) file:ecvl/core/imgproc.h line:148
	M("ecvl").def("ChangeColorSpace", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType)) &ecvl::ChangeColorSpace, "Copies the source Image into destination Image changing the color space.\n\nThe ChangeColorSpace procedure converts the color space of the source Image into the specified color space.\nNew data are copied into destination Image. Source and destination can be contiguous or not and can also\nbe the same Image.\n\n The input Image to convert in the new color space.\n\n The output Image in the \"new_type\" color space.\n\n The new color space in which the src Image must be converted.\n\nC++: ecvl::ChangeColorSpace(const class ecvl::Image &, class ecvl::Image &, enum ecvl::ColorType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("new_type"));

	// ecvl::Threshold(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType) file:ecvl/core/imgproc.h line:165
	M("ecvl").def("Threshold", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3) -> void { return ecvl::Threshold(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("thresh"), pybind11::arg("maxval"));
	M("ecvl").def("Threshold", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType)) &ecvl::Threshold, "Applies a fixed threshold to an input Image.\n\nThe Threshold function applies a fixed thresholding to an input Image. The function is useful to get a binary\nimage out of a grayscale (ColorType::GRAY) Image or to remove noise filtering out pixels with too small or too\nlarge values. Anyway, the function can be applied to any input Image. The pixels up to \"thresh\" value will be\nset to 0, the pixels above this value will be set to \"maxvalue\" if \"thresh_type\" is ThresholdingType::BINARY\n(default). The opposite will happen if \"thresh_type\" is ThresholdingType::BINARY_INV.\n\n Input Image on which to apply the threshold.\n\n The output thresholded Image.\n\n Threshold value.\n\n The maximum values in the thresholded Image.\n\n Type of threshold to be applied, see \n\nC++: ecvl::Threshold(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::ThresholdingType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("thresh"), pybind11::arg("maxval"), pybind11::arg("thresh_type"));

	// ecvl::OtsuThreshold(const class ecvl::Image &) file:ecvl/core/imgproc.h line:175
	M("ecvl").def("OtsuThreshold", (int (*)(const class ecvl::Image &)) &ecvl::OtsuThreshold, "Calculates the Otsu thresholding value.\n\nThe OtsuThreshold function calculates the Otsu threshold value over a given input Image. the Image must by ColorType::GRAY.\n\n Input Image on which to calculate the Otsu threshold value.\n\n Otsu threshold value.\n\nC++: ecvl::OtsuThreshold(const class ecvl::Image &) --> int", pybind11::arg("src"));

	// ecvl::Filter2D(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/imgproc.h line:185
	M("ecvl").def("Filter2D", [](const class ecvl::Image & a0, class ecvl::Image & a1, const class ecvl::Image & a2) -> void { return ecvl::Filter2D(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("ker"));
	M("ecvl").def("Filter2D", (void (*)(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType)) &ecvl::Filter2D, "Convolves an Image with a kernel\n\n Input Image.\n\n Output Image.\n\n Convolution kernel.\n\n Destination ecvl::DataType. If DataType::none, the same of src is used.\n\nC++: ecvl::Filter2D(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("ker"), pybind11::arg("type"));

	// ecvl::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, int, int, double, double) file:ecvl/core/imgproc.h line:208
	M("ecvl").def("GaussianBlur", [](const class ecvl::Image & a0, class ecvl::Image & a1, int const & a2, int const & a3, double const & a4) -> void { return ecvl::GaussianBlur(a0, a1, a2, a3, a4); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("sizeX"), pybind11::arg("sizeY"), pybind11::arg("sigmaX"));
	M("ecvl").def("GaussianBlur", (void (*)(const class ecvl::Image &, class ecvl::Image &, int, int, double, double)) &ecvl::GaussianBlur, "Blurs an Image using a Gaussian kernel.\n\n Input Image.\n\n Output Image.\n\n Horizontal size of the kernel. Must be positive and odd.\n\n Vertical size of the kernel. Must be positive and odd.\n\n Gaussian kernel standard deviation in X direction.\n\n Gaussian kernel standard deviation in Y direction. If zero, sigmaX is used. If both are zero, they are calculated from sizeX and sizeY.\n\nC++: ecvl::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, int, int, double, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("sizeX"), pybind11::arg("sizeY"), pybind11::arg("sigmaX"), pybind11::arg("sigmaY"));

	// ecvl::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:209
	M("ecvl").def("GaussianBlur", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::GaussianBlur, "C++: ecvl::GaussianBlur(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("sigma"));

	// ecvl::AdditiveLaplaceNoise(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:218
	M("ecvl").def("AdditiveLaplaceNoise", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::AdditiveLaplaceNoise, "Adds Laplace distributed noise to an Image.\n\n Input Image.\n\n Output Image.\n\n Standard deviation of the noise generating distribution. Suggested values are around 255 * 0.05 for uint8 Images.\n\nC++: ecvl::AdditiveLaplaceNoise(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("std_dev"));

	// ecvl::AdditivePoissonNoise(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:227
	M("ecvl").def("AdditivePoissonNoise", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::AdditivePoissonNoise, "Adds Poisson distributed noise to an Image.\n\n Input Image.\n\n Output Image.\n\n Lambda parameter of the Poisson distribution.\n\nC++: ecvl::AdditivePoissonNoise(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("lambda"));

	// ecvl::GammaContrast(const class ecvl::Image &, class ecvl::Image &, double) file:ecvl/core/imgproc.h line:235
	M("ecvl").def("GammaContrast", (void (*)(const class ecvl::Image &, class ecvl::Image &, double)) &ecvl::GammaContrast, "Adjust contrast by scaling each pixel value X to 255 * ((X/255) ** gamma).\n\n Input Image.\n\n Output Image.\n\n Exponent for the contrast adjustment.\n\nC++: ecvl::GammaContrast(const class ecvl::Image &, class ecvl::Image &, double) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("gamma"));

	// ecvl::CoarseDropout(const class ecvl::Image &, class ecvl::Image &, double, double, bool) file:ecvl/core/imgproc.h line:246
	M("ecvl").def("CoarseDropout", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, bool)) &ecvl::CoarseDropout, "Sets rectangular areas within an Image to zero.\n\n Input Image.\n\n Output Image.\n\n Probability of any rectangle being set to zero.\n\n Size of rectangles in percentage of the input Image.\n\n Whether to use the same value for all channels of a pixel or not.\n\nC++: ecvl::CoarseDropout(const class ecvl::Image &, class ecvl::Image &, double, double, bool) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("drop_size"), pybind11::arg("per_channel"));

	// ecvl::IntegralImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) file:ecvl/core/imgproc.h line:254
	M("ecvl").def("IntegralImage", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::IntegralImage(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("IntegralImage", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType)) &ecvl::IntegralImage, "Calculate the integral image of the source Image.\n\n Input Image. It must be with ColorType::GRAY, \"xyc\" and DataType::uint8.\n\n Output Image.\n\n DataType of the destination Image.\n\nC++: ecvl::IntegralImage(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("dst_type"));

	// ecvl::NonMaximaSuppression(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:261
	M("ecvl").def("NonMaximaSuppression", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::NonMaximaSuppression, "Calculate the Non-Maxima suppression of the source Image.\n\n Input Image. It must be with ColorType::GRAY, \"xyc\" and DataType::int32.\n\n Output Image.\n\nC++: ecvl::NonMaximaSuppression(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::ConnectedComponentsLabeling(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:276
	M("ecvl").def("ConnectedComponentsLabeling", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::ConnectedComponentsLabeling, "Labels connected components in an binary Image\n\n Input Image. It must be with channels \"xyc\", only one color channel and DataType::uint8.\n\n Output Image.\n\nC++: ecvl::ConnectedComponentsLabeling(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::Inpaint(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, double, enum ecvl::InpaintType) file:ecvl/core/imgproc.h line:377
	M("ecvl").def("Inpaint", [](const class ecvl::Image & a0, class ecvl::Image & a1, const class ecvl::Image & a2, double const & a3) -> void { return ecvl::Inpaint(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("inpaintMask"), pybind11::arg("inpaintRadius"));
	M("ecvl").def("Inpaint", (void (*)(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, double, enum ecvl::InpaintType)) &ecvl::Inpaint, "Restores the selected region in an image using the region neighborhood.\n\n Input Image.\n\n Output Image.\n\n Inpainting mask, an Image with 1-channel and DataType::uint8. Non-zero pixels indicate the area that needs to be inpainted.\n\n Radius of a circular neighborhood of each point inpainted that is considered by the algorithm.\n\n Inpainting method that could be InpaintType::INPAINT_NS or InpaintType::INPAINT_TELEA.\n\nC++: ecvl::Inpaint(const class ecvl::Image &, class ecvl::Image &, const class ecvl::Image &, double, enum ecvl::InpaintType) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("inpaintMask"), pybind11::arg("inpaintRadius"), pybind11::arg("flag"));

	// ecvl::Transpose(const class ecvl::Image &, class ecvl::Image &) file:ecvl/core/imgproc.h line:392
	M("ecvl").def("Transpose", (void (*)(const class ecvl::Image &, class ecvl::Image &)) &ecvl::Transpose, "Swap rows and columns of an Image.\n\n Input Image.\n\n Output transposed Image.\n\nC++: ecvl::Transpose(const class ecvl::Image &, class ecvl::Image &) --> void", pybind11::arg("src"), pybind11::arg("dst"));

	// ecvl::ElasticTransform(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType, enum ecvl::BorderType, const int &, const unsigned int) file:ecvl/core/imgproc.h line:427
	M("ecvl").def("ElasticTransform", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::ElasticTransform(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("ElasticTransform", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2) -> void { return ecvl::ElasticTransform(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"));
	M("ecvl").def("ElasticTransform", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3) -> void { return ecvl::ElasticTransform(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"), pybind11::arg("sigma"));
	M("ecvl").def("ElasticTransform", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3, enum ecvl::InterpolationType const & a4) -> void { return ecvl::ElasticTransform(a0, a1, a2, a3, a4); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"), pybind11::arg("sigma"), pybind11::arg("interp"));
	M("ecvl").def("ElasticTransform", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3, enum ecvl::InterpolationType const & a4, enum ecvl::BorderType const & a5) -> void { return ecvl::ElasticTransform(a0, a1, a2, a3, a4, a5); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"), pybind11::arg("sigma"), pybind11::arg("interp"), pybind11::arg("border_type"));
	M("ecvl").def("ElasticTransform", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, double const & a3, enum ecvl::InterpolationType const & a4, enum ecvl::BorderType const & a5, const int & a6) -> void { return ecvl::ElasticTransform(a0, a1, a2, a3, a4, a5, a6); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"), pybind11::arg("sigma"), pybind11::arg("interp"), pybind11::arg("border_type"), pybind11::arg("border_value"));
	M("ecvl").def("ElasticTransform", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType, enum ecvl::BorderType, const int &, const unsigned int)) &ecvl::ElasticTransform, "Elastic deformation of input Image.\nBased on https://github.com/albumentations-team/albumentations/blob/master/albumentations/augmentations/transforms.py#L1235.\n\n Input Image.\n\n Output Image.\n\n Scaling factor that controls the intensity of the deformation.\n\n Gaussian kernel standard deviation\n\n Interpolation type used. If src is DataType::int8 or DataType::int32, Interpolation::nearest is used. Default is InterpolationType::linear.\n\n Flag used to specify the pixel extrapolation method. Default is BorderType::BORDER_REFLECT_101.\n\n Padding value if border_type is BorderType::BORDER_CONSTANT.\n\n Seed to use for this function's random number generator.\n\nC++: ecvl::ElasticTransform(const class ecvl::Image &, class ecvl::Image &, double, double, enum ecvl::InterpolationType, enum ecvl::BorderType, const int &, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("alpha"), pybind11::arg("sigma"), pybind11::arg("interp"), pybind11::arg("border_type"), pybind11::arg("border_value"), pybind11::arg("seed"));

}


// File: ecvl/core/imgproc_1.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgproc.h>
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

void bind_ecvl_core_imgproc_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// ecvl::Salt(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) file:ecvl/core/imgproc.h line:465
	M("ecvl").def("Salt", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2) -> void { return ecvl::Salt(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"));
	M("ecvl").def("Salt", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, bool const & a3) -> void { return ecvl::Salt(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"));
	M("ecvl").def("Salt", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int)) &ecvl::Salt, "Adds salt noise (white pixels) to an Image.\n\n Input Image.\n\n Output Image.\n\n Probability of replacing a pixel with salt noise.\n\n If true, noise is not considered pixel-wise but channel-wise.\n\n Seed to use for this function's random number generator.\n\nC++: ecvl::Salt(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"), pybind11::arg("seed"));

	// ecvl::Pepper(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) file:ecvl/core/imgproc.h line:475
	M("ecvl").def("Pepper", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2) -> void { return ecvl::Pepper(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"));
	M("ecvl").def("Pepper", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, bool const & a3) -> void { return ecvl::Pepper(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"));
	M("ecvl").def("Pepper", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int)) &ecvl::Pepper, "Adds pepper noise (black pixels) to an Image.\n\n Input Image.\n\n Output Image.\n\n Probability of replacing a pixel with pepper noise.\n\n If true, noise is not considered pixel-wise but channel-wise.\n\n Seed to use for this function's random number generator.\n\nC++: ecvl::Pepper(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"), pybind11::arg("seed"));

	// ecvl::SaltAndPepper(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) file:ecvl/core/imgproc.h line:485
	M("ecvl").def("SaltAndPepper", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2) -> void { return ecvl::SaltAndPepper(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"));
	M("ecvl").def("SaltAndPepper", [](const class ecvl::Image & a0, class ecvl::Image & a1, double const & a2, bool const & a3) -> void { return ecvl::SaltAndPepper(a0, a1, a2, a3); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"));
	M("ecvl").def("SaltAndPepper", (void (*)(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int)) &ecvl::SaltAndPepper, "Adds salt and pepper noise (white and black pixels) to an Image. White and black pixels are equally likely.\n\n Input Image.\n\n Output Image.\n\n Probability of replacing a pixel with salt and pepper noise.\n\n If true, noise is not considered pixel-wise but channel-wise.\n\n Seed to use for this function's random number generator.\n\nC++: ecvl::SaltAndPepper(const class ecvl::Image &, class ecvl::Image &, double, bool, const unsigned int) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("p"), pybind11::arg("per_channel"), pybind11::arg("seed"));

}


// File: ecvl/core/imgcodecs.cpp
#include <ecvl/core/arithmetic.h>
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <ecvl/core/imgcodecs.h>
#include <func_binder.hpp>
#include <iterator>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
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
	// ecvl::ImReadMode file:ecvl/core/imgcodecs.h line:28
	pybind11::enum_<ecvl::ImReadMode>(M("ecvl"), "ImReadMode", "Enum class representing the ECVL ImRead flags.\n\n     ImReadMode")
		.value("GRAYSCALE", ecvl::ImReadMode::GRAYSCALE)
		.value("COLOR", ecvl::ImReadMode::COLOR);

;

	// ecvl::Add(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) file: line:69
	M("ecvl").def("Add", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2) -> void { return ecvl::Add(a0, a1, a2); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"));
	M("ecvl").def("Add", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType const & a3) -> void { return ecvl::Add(a0, a1, a2, a3); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"));
	M("ecvl").def("Add", (void (*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::Add, "C++: ecvl::Add(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));

	// ecvl::Sub(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) file: line:118
	M("ecvl").def("Sub", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2) -> void { return ecvl::Sub(a0, a1, a2); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"));
	M("ecvl").def("Sub", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType const & a3) -> void { return ecvl::Sub(a0, a1, a2, a3); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"));
	M("ecvl").def("Sub", (void (*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::Sub, "C++: ecvl::Sub(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));

	// ecvl::Mul(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) file: line:122
	M("ecvl").def("Mul", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2) -> void { return ecvl::Mul(a0, a1, a2); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"));
	M("ecvl").def("Mul", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType const & a3) -> void { return ecvl::Mul(a0, a1, a2, a3); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"));
	M("ecvl").def("Mul", (void (*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::Mul, "C++: ecvl::Mul(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));

	// ecvl::Div(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) file: line:126
	M("ecvl").def("Div", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2) -> void { return ecvl::Div(a0, a1, a2); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"));
	M("ecvl").def("Div", [](const class ecvl::Image & a0, const class ecvl::Image & a1, class ecvl::Image & a2, enum ecvl::DataType const & a3) -> void { return ecvl::Div(a0, a1, a2, a3); }, "", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"));
	M("ecvl").def("Div", (void (*)(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::Div, "C++: ecvl::Div(const class ecvl::Image &, const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src1"), pybind11::arg("src2"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));

	// ecvl::Neg(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) file:ecvl/core/arithmetic.h line:146
	M("ecvl").def("Neg", [](const class ecvl::Image & a0, class ecvl::Image & a1) -> void { return ecvl::Neg(a0, a1); }, "", pybind11::arg("src"), pybind11::arg("dst"));
	M("ecvl").def("Neg", [](const class ecvl::Image & a0, class ecvl::Image & a1, enum ecvl::DataType const & a2) -> void { return ecvl::Neg(a0, a1, a2); }, "", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("dst_type"));
	M("ecvl").def("Neg", (void (*)(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool)) &ecvl::Neg, "Negation of an Image.  Neg\n\n    The Neg() function negates every value of an Image, and stores the\n    the result in a destination Image with the specified type.\n\n    \n Image to be negated.\n    \n\n Destination Image. It will store the final result.\n    \n\n Desired type for the destination Image. If none (default) the destination\n                        Image will preserve its own type, if any, or it will inherit the DataType\n                        of src otherwise.\n    \n\n Whether to apply saturation or not. Default is true.\n\n    \n\n\n\nC++: ecvl::Neg(const class ecvl::Image &, class ecvl::Image &, enum ecvl::DataType, bool) --> void", pybind11::arg("src"), pybind11::arg("dst"), pybind11::arg("dst_type"), pybind11::arg("saturate"));

}


// File: unknown/unknown.cpp
#include <dataset_addons.hpp>
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <ecvl/dataset_parser.h>
#include <func_binder.hpp>
#include <memory>
#include <sample_addons.hpp>
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

void bind_unknown_unknown(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// ecvl::SplitType file: line:38
	pybind11::enum_<ecvl::SplitType>(M("ecvl"), "SplitType", "Enum class representing the Dataset supported splits.\n\n SplitType")
		.value("training", ecvl::SplitType::training)
		.value("validation", ecvl::SplitType::validation)
		.value("test", ecvl::SplitType::test);

;

	{ // ecvl::Sample file:ecvl/dataset_parser.h line:45
		pybind11::class_<ecvl::Sample, std::shared_ptr<ecvl::Sample>> cl(M("ecvl"), "Sample", "Sample image in a dataset.\n\nThis class provides the information to describe a dataset sample.\n`label_` and `label_path_` are mutually exclusive.\n Sample");
		cl.def( pybind11::init( [](ecvl::Sample const &o){ return new ecvl::Sample(o); } ) );
		cl.def( pybind11::init( [](){ return new ecvl::Sample(); } ) );
		cl.def_readwrite("location_", &ecvl::Sample::location_);
		cl.def_readwrite("label_", &ecvl::Sample::label_);
		cl.def_readwrite("label_path_", &ecvl::Sample::label_path_);
		cl.def_readwrite("values_", &ecvl::Sample::values_);
		cl.def_readwrite("size_", &ecvl::Sample::size_);
		cl.def("LoadImage", [](ecvl::Sample &o) -> ecvl::Image { return o.LoadImage(); }, "");
		cl.def("LoadImage", [](ecvl::Sample &o, enum ecvl::ColorType const & a0) -> ecvl::Image { return o.LoadImage(a0); }, "", pybind11::arg("ctype"));
		cl.def("LoadImage", (class ecvl::Image (ecvl::Sample::*)(enum ecvl::ColorType, const bool &)) &ecvl::Sample::LoadImage, "Return an Image of the dataset.\n\n    The LoadImage() function opens the sample image, from `location_` or `label_path_` depending on `is_gt` parameter.\n\n    \n ecvl::ColorType of the returned Image.\n    \n\n Whether to load the sample image or its ground truth.\n\n    \n Image containing the loaded sample.\n\nC++: ecvl::Sample::LoadImage(enum ecvl::ColorType, const bool &) --> class ecvl::Image", pybind11::arg("ctype"), pybind11::arg("is_gt"));
		cl.def("assign", (class ecvl::Sample & (ecvl::Sample::*)(const class ecvl::Sample &)) &ecvl::Sample::operator=, "C++: ecvl::Sample::operator=(const class ecvl::Sample &) --> class ecvl::Sample &", pybind11::return_value_policy::automatic, pybind11::arg(""));

		sample_addons(cl);
	}
	{ // ecvl::Split file:ecvl/dataset_parser.h line:72
		pybind11::class_<ecvl::Split, std::shared_ptr<ecvl::Split>> cl(M("ecvl"), "Split", "Splits of a dataset.\n\nThis class provides the splits a dataset can have: training, validation, and test.\n\n Split");
		cl.def( pybind11::init( [](ecvl::Split const &o){ return new ecvl::Split(o); } ) );
		cl.def( pybind11::init( [](){ return new ecvl::Split(); } ) );
		cl.def_readwrite("training_", &ecvl::Split::training_);
		cl.def_readwrite("validation_", &ecvl::Split::validation_);
		cl.def_readwrite("test_", &ecvl::Split::test_);
		cl.def("assign", (class ecvl::Split & (ecvl::Split::*)(const class ecvl::Split &)) &ecvl::Split::operator=, "C++: ecvl::Split::operator=(const class ecvl::Split &) --> class ecvl::Split &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // ecvl::Dataset file:ecvl/dataset_parser.h line:86
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


// File: ecvl/dataset_generator.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
#include <ecvl/dataset_generator.h>
#include <ecvl/dataset_parser.h>
#include <func_binder.hpp>
#include <generateclassificationdataset_addons.hpp>
#include <generatesegmentationdataset_addons.hpp>
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

// ecvl::GenerateSegmentationDataset file:ecvl/dataset_generator.h line:88
struct PyCallBack_ecvl_GenerateSegmentationDataset : public ecvl::GenerateSegmentationDataset {
	using ecvl::GenerateSegmentationDataset::GenerateSegmentationDataset;

};

// ecvl::GenerateClassificationDataset file:ecvl/dataset_generator.h line:121
struct PyCallBack_ecvl_GenerateClassificationDataset : public ecvl::GenerateClassificationDataset {
	using ecvl::GenerateClassificationDataset::GenerateClassificationDataset;

};

void bind_ecvl_dataset_generator(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // ecvl::GenerateDataset file:ecvl/dataset_generator.h line:26
		pybind11::class_<ecvl::GenerateDataset, std::shared_ptr<ecvl::GenerateDataset>> cl(M("ecvl"), "GenerateDataset", "Abstract class which fill the dataset object with name and description, features common to all types of datasets.\n\n GenerateDataset");
		cl.def_readonly("dataset_root_directory_", &ecvl::GenerateDataset::dataset_root_directory_);
		cl.def_readwrite("splits_", &ecvl::GenerateDataset::splits_);
		cl.def_readwrite("num_samples_", &ecvl::GenerateDataset::num_samples_);
		cl.def_readwrite("d_", &ecvl::GenerateDataset::d_);
		cl.def("LoadImagesAndSplits", (void (ecvl::GenerateDataset::*)()) &ecvl::GenerateDataset::LoadImagesAndSplits, "Call LoadSplitImages and load the splits with indexes of corresponding images.\n\n    If there aren't splits folders, only the list of images and corresponding labels will be loaded.\n\nC++: ecvl::GenerateDataset::LoadImagesAndSplits() --> void");
		cl.def("GetDataset", (class ecvl::Dataset (ecvl::GenerateDataset::*)()) &ecvl::GenerateDataset::GetDataset, "Return the Dataset object obtained from the directory structure.\n\n    \n Dataset obtained from the directory structure.\n\nC++: ecvl::GenerateDataset::GetDataset() --> class ecvl::Dataset");
	}
	{ // ecvl::GenerateSegmentationDataset file:ecvl/dataset_generator.h line:88
		pybind11::class_<ecvl::GenerateSegmentationDataset, std::shared_ptr<ecvl::GenerateSegmentationDataset>, PyCallBack_ecvl_GenerateSegmentationDataset, ecvl::GenerateDataset> cl(M("ecvl"), "GenerateSegmentationDataset", "Generate an ecvl::Dataset from a directory tree for a segmentation task.\n\nAssumes a directory structure where a top-level directory can have subdirectories\nnamed \"training\", \"validation\" and \"test\" (possibly not all present), each of\nwhich can have images and ground truth in different subdirectories (named \"images\" and \"ground_truth\")\nor in the same directory. If the ground truth images have a particular suffix or a different extension\n(necessary if they are in the same directory as the images) it's necessary to specify it in the constructor.\nFor more detailed information about the supported directory structure check https://github.com/deephealthproject/ecvl/wiki/ECVL-Dataset-Generator.\n\n GenerateSegmentationDataset");
		cl.def( pybind11::init( [](PyCallBack_ecvl_GenerateSegmentationDataset const &o){ return new PyCallBack_ecvl_GenerateSegmentationDataset(o); } ) );
		cl.def( pybind11::init( [](ecvl::GenerateSegmentationDataset const &o){ return new ecvl::GenerateSegmentationDataset(o); } ) );
		cl.def_readwrite("suffix_", &ecvl::GenerateSegmentationDataset::suffix_);
		cl.def_readwrite("gt_name_", &ecvl::GenerateSegmentationDataset::gt_name_);

		generatesegmentationdataset_addons(cl);
	}
	{ // ecvl::GenerateClassificationDataset file:ecvl/dataset_generator.h line:121
		pybind11::class_<ecvl::GenerateClassificationDataset, std::shared_ptr<ecvl::GenerateClassificationDataset>, PyCallBack_ecvl_GenerateClassificationDataset, ecvl::GenerateDataset> cl(M("ecvl"), "GenerateClassificationDataset", "Generate an ecvl::Dataset from a directory tree for a classification task.\n\nAssumes a directory structure where a top-level directory can have subdirectories\nnamed \"training\", \"validation\" and \"test\" (possibly not all present), each of\nwhich has in turn one subdirectory for each class, containing the images for that class.\nFor more detailed information about the supported directory structure check https://github.com/deephealthproject/ecvl/wiki/ECVL-Dataset-Generator.\n\n GenerateClassificationDataset");
		cl.def( pybind11::init( [](PyCallBack_ecvl_GenerateClassificationDataset const &o){ return new PyCallBack_ecvl_GenerateClassificationDataset(o); } ) );
		cl.def( pybind11::init( [](ecvl::GenerateClassificationDataset const &o){ return new ecvl::GenerateClassificationDataset(o); } ) );

		generateclassificationdataset_addons(cl);
	}
	{ // ecvl::View file:ecvl/core/image.h line:566
		pybind11::class_<ecvl::View<ecvl::DataType::int8>, std::shared_ptr<ecvl::View<ecvl::DataType::int8>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_int8_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::int8>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::int8> const &o){ return new ecvl::View<ecvl::DataType::int8>(o); } ) );
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def_readwrite("dev_", &ecvl::Image::dev_);
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("To", (void (ecvl::Image::*)(enum ecvl::Device)) &ecvl::Image::To, "C++: ecvl::Image::To(enum ecvl::Device) --> void", pybind11::arg("dev"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data.\n\n        \n Move the implementation to the specific hals if other shallow hals will be introduced.\n\n    \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Width", (int (ecvl::Image::*)() const) &ecvl::Image::Width, "Returns the width of Image. \n\nC++: ecvl::Image::Width() const --> int");
		cl.def("Height", (int (ecvl::Image::*)() const) &ecvl::Image::Height, "Returns the height of Image. \n\nC++: ecvl::Image::Height() const --> int");
		cl.def("Neg", (void (ecvl::Image::*)()) &ecvl::Image::Neg, "In-place negation. \n\nC++: ecvl::Image::Neg() --> void");
		cl.def("__sub__", (class ecvl::Image (ecvl::Image::*)() const) &ecvl::Image::operator-, "C++: ecvl::Image::operator-() const --> class ecvl::Image");
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
	{ // ecvl::View file:ecvl/core/image.h line:566
		pybind11::class_<ecvl::View<ecvl::DataType::int16>, std::shared_ptr<ecvl::View<ecvl::DataType::int16>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_int16_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::int16>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::int16> const &o){ return new ecvl::View<ecvl::DataType::int16>(o); } ) );
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def_readwrite("dev_", &ecvl::Image::dev_);
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("To", (void (ecvl::Image::*)(enum ecvl::Device)) &ecvl::Image::To, "C++: ecvl::Image::To(enum ecvl::Device) --> void", pybind11::arg("dev"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data.\n\n        \n Move the implementation to the specific hals if other shallow hals will be introduced.\n\n    \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Width", (int (ecvl::Image::*)() const) &ecvl::Image::Width, "Returns the width of Image. \n\nC++: ecvl::Image::Width() const --> int");
		cl.def("Height", (int (ecvl::Image::*)() const) &ecvl::Image::Height, "Returns the height of Image. \n\nC++: ecvl::Image::Height() const --> int");
		cl.def("Neg", (void (ecvl::Image::*)()) &ecvl::Image::Neg, "In-place negation. \n\nC++: ecvl::Image::Neg() --> void");
		cl.def("__sub__", (class ecvl::Image (ecvl::Image::*)() const) &ecvl::Image::operator-, "C++: ecvl::Image::operator-() const --> class ecvl::Image");
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
	{ // ecvl::View file:ecvl/core/image.h line:566
		pybind11::class_<ecvl::View<ecvl::DataType::float32>, std::shared_ptr<ecvl::View<ecvl::DataType::float32>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_float32_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::float32>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::float32> const &o){ return new ecvl::View<ecvl::DataType::float32>(o); } ) );
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def_readwrite("dev_", &ecvl::Image::dev_);
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("To", (void (ecvl::Image::*)(enum ecvl::Device)) &ecvl::Image::To, "C++: ecvl::Image::To(enum ecvl::Device) --> void", pybind11::arg("dev"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data.\n\n        \n Move the implementation to the specific hals if other shallow hals will be introduced.\n\n    \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Width", (int (ecvl::Image::*)() const) &ecvl::Image::Width, "Returns the width of Image. \n\nC++: ecvl::Image::Width() const --> int");
		cl.def("Height", (int (ecvl::Image::*)() const) &ecvl::Image::Height, "Returns the height of Image. \n\nC++: ecvl::Image::Height() const --> int");
		cl.def("Neg", (void (ecvl::Image::*)()) &ecvl::Image::Neg, "In-place negation. \n\nC++: ecvl::Image::Neg() --> void");
		cl.def("__sub__", (class ecvl::Image (ecvl::Image::*)() const) &ecvl::Image::operator-, "C++: ecvl::Image::operator-() const --> class ecvl::Image");
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
	{ // ecvl::View file:ecvl/core/image.h line:566
		pybind11::class_<ecvl::View<ecvl::DataType::uint8>, std::shared_ptr<ecvl::View<ecvl::DataType::uint8>>, ecvl::Image> cl(M("ecvl"), "View_ecvl_DataType_uint8_t", "");
		cl.def( pybind11::init( [](){ return new ecvl::View<ecvl::DataType::uint8>(); } ) );
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );

		cl.def( pybind11::init( [](ecvl::View<ecvl::DataType::uint8> const &o){ return new ecvl::View<ecvl::DataType::uint8>(o); } ) );
		cl.def_readwrite("elemtype_", &ecvl::Image::elemtype_);
		cl.def_readwrite("elemsize_", &ecvl::Image::elemsize_);
		cl.def_readwrite("dims_", &ecvl::Image::dims_);
		cl.def_readwrite("strides_", &ecvl::Image::strides_);
		cl.def_readwrite("channels_", &ecvl::Image::channels_);
		cl.def_readwrite("colortype_", &ecvl::Image::colortype_);
		cl.def_readwrite("spacings_", &ecvl::Image::spacings_);
		cl.def_readwrite("datasize_", &ecvl::Image::datasize_);
		cl.def_readwrite("contiguous_", &ecvl::Image::contiguous_);
		cl.def_readwrite("dev_", &ecvl::Image::dev_);
		cl.def("assign", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator=, "C++: ecvl::Image::operator=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("To", (void (ecvl::Image::*)(enum ecvl::Device)) &ecvl::Image::To, "C++: ecvl::Image::To(enum ecvl::Device) --> void", pybind11::arg("dev"));
		cl.def("IsEmpty", (bool (ecvl::Image::*)() const) &ecvl::Image::IsEmpty, "To check whether the Image contains data or not, regardless of the owning status. \n\nC++: ecvl::Image::IsEmpty() const --> bool");
		cl.def("IsOwner", (bool (ecvl::Image::*)() const) &ecvl::Image::IsOwner, "To check whether the Image is owner of the data.\n\n        \n Move the implementation to the specific hals if other shallow hals will be introduced.\n\n    \n\nC++: ecvl::Image::IsOwner() const --> bool");
		cl.def("Channels", (int (ecvl::Image::*)() const) &ecvl::Image::Channels, "Returns the number of channels. \n\nC++: ecvl::Image::Channels() const --> int");
		cl.def("Width", (int (ecvl::Image::*)() const) &ecvl::Image::Width, "Returns the width of Image. \n\nC++: ecvl::Image::Width() const --> int");
		cl.def("Height", (int (ecvl::Image::*)() const) &ecvl::Image::Height, "Returns the height of Image. \n\nC++: ecvl::Image::Height() const --> int");
		cl.def("Neg", (void (ecvl::Image::*)()) &ecvl::Image::Neg, "In-place negation. \n\nC++: ecvl::Image::Neg() --> void");
		cl.def("__sub__", (class ecvl::Image (ecvl::Image::*)() const) &ecvl::Image::operator-, "C++: ecvl::Image::operator-() const --> class ecvl::Image");
		cl.def("__iadd__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator+=, "C++: ecvl::Image::operator+=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__isub__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator-=, "C++: ecvl::Image::operator-=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__imul__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator*=, "C++: ecvl::Image::operator*=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__idiv__", (class ecvl::Image & (ecvl::Image::*)(const class ecvl::Image &)) &ecvl::Image::operator/=, "C++: ecvl::Image::operator/=(const class ecvl::Image &) --> class ecvl::Image &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
	}
}


// File: image_ext.cpp
#include <ecvl/core/datatype.h>
#include <ecvl/core/hal.h>
#include <ecvl/core/image.h>
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
	{ // ecvl::View_int8 file:image_ext.hpp line:24
		pybind11::class_<ecvl::View_int8, std::shared_ptr<ecvl::View_int8>, ecvl::View<ecvl::DataType::int8>> cl(M("ecvl"), "View_int8", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_int8_addons(cl);
	}
	{ // ecvl::View_int16 file:image_ext.hpp line:28
		pybind11::class_<ecvl::View_int16, std::shared_ptr<ecvl::View_int16>, ecvl::View<ecvl::DataType::int16>> cl(M("ecvl"), "View_int16", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_int16_addons(cl);
	}
	{ // ecvl::View_float32 file:image_ext.hpp line:32
		pybind11::class_<ecvl::View_float32, std::shared_ptr<ecvl::View_float32>, ecvl::View<ecvl::DataType::float32>> cl(M("ecvl"), "View_float32", "");
		cl.def( pybind11::init<class ecvl::Image &>(), pybind11::arg("img") );


		view_float32_addons(cl);
	}
	{ // ecvl::View_uint8 file:image_ext.hpp line:36
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
void bind_ecvl_core_imgproc_1(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_core_imgcodecs(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_unknown_unknown(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_ecvl_dataset_generator(std::function< pybind11::module &(std::string const &namespace_) > &M);
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
	bind_ecvl_core_imgproc_1(M);
	bind_ecvl_core_imgcodecs(M);
	bind_unknown_unknown(M);
	bind_ecvl_dataset_generator(M);
	bind_image_ext(M);

}

// Source list file: /pyecvl/codegen/bindings/_core.sources
// _core.cpp
// ecvl/core/datatype.cpp
// ecvl/core/image.cpp
// ecvl/core/imgproc.cpp
// ecvl/core/imgproc_1.cpp
// ecvl/core/imgcodecs.cpp
// unknown/unknown.cpp
// ecvl/dataset_generator.cpp
// image_ext.cpp

// Modules list file: /pyecvl/codegen/bindings/_core.modules
// ecvl 
