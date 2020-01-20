import os
from distutils.core import setup, Extension

import pybind11


EXTRA_COMPILE_ARGS = ['-std=c++17', '-fvisibility=hidden', '-DECVL_WITH_DICOM']
OPENCV_LIBS = [
    "opencv_core",
    "opencv_imgcodecs",
    "opencv_imgproc",
]
DICOM_LIBS = [
    "dcmdata",
    "dcmimage",
    "dcmimgle",
    "dcmjpeg",
    "i2d",
    "ijg8",
    "ijg12",
    "ijg16",
    "oflog",
    "ofstd",
]
ECVL_LIBS = ["ecvl_eddl", "dataset_parser", "ecvl_core"]
OTHER_LIBS = ["stdc++fs", "eddl", "openslide", "yaml-cpp"]
ALL_LIBS = ECVL_LIBS + OPENCV_LIBS + DICOM_LIBS + OTHER_LIBS
INCLUDE_DIRS = [
    "src",
    pybind11.get_include(),
    pybind11.get_include(user=True)
]
LIBRARY_DIRS = []
RUNTIME_LIBRARY_DIRS = []
EDDL_DIR = os.getenv("EDDL_DIR")
if EDDL_DIR:
    INCLUDE_DIRS.append(os.path.join(EDDL_DIR, "include"))
    LIBRARY_DIRS.append(os.path.join(EDDL_DIR, "lib"))
    RUNTIME_LIBRARY_DIRS.append(os.path.join(EDDL_DIR, "lib"))
ECVL_DIR = os.getenv("ECVL_DIR")
if ECVL_DIR:
    INCLUDE_DIRS.append(os.path.join(ECVL_DIR, "include"))
    LIBRARY_DIRS.append(os.path.join(ECVL_DIR, "lib"))
    RUNTIME_LIBRARY_DIRS.append(os.path.join(ECVL_DIR, "lib"))


ext = Extension(
    "pyecvl._core",
    sources=["src/_core.cpp"],
    include_dirs=INCLUDE_DIRS,
    library_dirs=LIBRARY_DIRS,
    runtime_library_dirs=RUNTIME_LIBRARY_DIRS,
    libraries=ALL_LIBS,
    extra_compile_args=EXTRA_COMPILE_ARGS,
)


setup(
    name="pyecvl",
    packages=["pyecvl"],
    ext_modules=[ext]
)
