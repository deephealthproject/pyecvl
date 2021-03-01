# Copyright (c) 2019-2021 CRS4
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

"""\
PyECVL is a Python wrapper for ECVL, the European Computer Vision Library.
"""

import os
from setuptools import setup, Extension

import pybind11
from pyecvl.version import VERSION


def to_bool(s):
    s = s.lower()
    return s != "off" and s != "false"


EXTRA_COMPILE_ARGS = ['-std=c++17', '-fvisibility=hidden']
OPENCV_LIBS = [
    "opencv_core",
    "opencv_imgcodecs",
    "opencv_imgproc",
    "opencv_photo",
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
ECVL_LIBS = ["dataset", "ecvl_core"]
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
    version=VERSION,
    url="https://github.com/deephealthproject/pyecvl",
    description="Python wrapper for ECVL",
    long_description=__doc__,
    author="Simone Leo",
    author_email="<simone.leo@crs4.it>",
    license="MIT",
    platforms=["Linux"],
    classifiers=[
        "Programming Language :: Python :: 3.6",
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux",
        "Topic :: Scientific/Engineering",
        "Intended Audience :: Science/Research",
    ],
    packages=["pyecvl"],
    ext_modules=[ext],
    install_requires=["setuptools", "pybind11<2.6", "numpy"],
    zip_safe=False,
)
