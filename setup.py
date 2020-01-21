import os
from distutils.core import setup, Extension

import pybind11


def to_bool(s):
    s = s.lower()
    return s != "off" and s != "false"


EXTRA_COMPILE_ARGS = ['-std=c++17', '-fvisibility=hidden']
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
ECVL_LIBS = ["dataset_parser", "ecvl_core"]
OTHER_LIBS = ["stdc++fs", "yaml-cpp"]
ALL_LIBS = ECVL_LIBS + OPENCV_LIBS + OTHER_LIBS
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

# optional modules, on by default. Set env var to "OFF" or "FALSE" to disable
ECVL_WITH_DICOM = to_bool(os.getenv("ECVL_WITH_DICOM", "ON"))
if ECVL_WITH_DICOM:
    EXTRA_COMPILE_ARGS.append('-DECVL_WITH_DICOM')
    ALL_LIBS.extend(DICOM_LIBS)
ECVL_WITH_OPENSLIDE = to_bool(os.getenv("ECVL_WITH_OPENSLIDE", "ON"))
if ECVL_WITH_OPENSLIDE:
    EXTRA_COMPILE_ARGS.append('-DECVL_WITH_OPENSLIDE')
    ALL_LIBS.append("openslide")
ECVL_EDDL = to_bool(os.getenv("ECVL_EDDL", "ON"))
if ECVL_EDDL:
    EXTRA_COMPILE_ARGS.append('-DECVL_EDDL')
    ALL_LIBS.extend(["ecvl_eddl", "eddl"])


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
