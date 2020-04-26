.. _installation:

Installation
============

To install PyECVL, you need to install ECVL first. Installation instructions
for ECVL are available in the `ECVL README
<https://github.com/deephealthproject/ecvl/blob/master/README.md>`_.

As explained in the above README, Some ECVL components are optional. By
default, PyECVL assumes that ECVL has been installed with DICOM, OpenSlide and
EDDL support.

The latter enables an ECVL module that allows to interact with `EDDL
<https://github.com/deephealthproject/eddl>`_, the European Distributed Deep
Learning library (e.g., to convert ECVL images to/from EDDL tensors). In order
to use the same functionalities in Python, you need to install EDDL and its
Python version, `PyEDDL <https://github.com/deephealthproject/pyeddl>`_. Each
PyECVL version depends on specific ECVL and PyEDDL versions. If you are
installing from the GitHub repo, the correct versions of ECVL and PyEDDL are
available from the submodules (``third_party`` dir).

The following sections contain a complete walkthrough to install the current
version of PyECVL from scratch, assuming installation of all EDDL and ECVL
optional modules. We use Ubuntu Linux as an example platform.


Install ECVL and EDDL dependencies
----------------------------------

ECVL needs a compiler with C++17 support, such as gcc-8 or later. You also
need to install the development version of the OpenCV and OpenSlide
libraries. EDDL needs the development versions of the zlib and Eigen3
libraries. To enable ONNX I/O, you also need to install Google protobuf. On
Ubuntu, for instance, install the following with APT: ``gcc-8, g++-8,
libopencv-dev, libopenslide-dev, zlib1g-dev, libeigen3-dev, wget,
ca-certificates``. Install protobuf from source::

    wget -q https://github.com/protocolbuffers/protobuf/releases/download/v3.11.4/protobuf-all-3.11.4.tar.gz
    tar xf protobuf-all-3.11.4.tar.gz
    cd protobuf-3.11.4
    ./configure
    make -j$(nproc)
    make install


Install EDDL and ECVL
---------------------

Clone the GitHub repo::

    git clone --recurse-submodules https://github.com/deephealthproject/pyecvl.git
    cd pyecvl

Install EDDL::

    pushd pyecvl/third_party/pyeddl/third_party/eddl
    mkdir build
    pushd build
    cmake -D BUILD_SHARED_LIB=ON -D BUILD_PROTOBUF=ON -D BUILD_TESTS=OFF
    make -j$(nproc)
    make install
    popd
    popd

Install ECVL::

    pushd third_party/ecvl
    mkdir build
    pushd build
    cmake -DECVL_WITH_DICOM=ON -DECVL_WITH_OPENSLIDE=ON -DECVL_DATASET=ON -DECVL_BUILD_EDDL=ON
    make -j$(nproc)
    make install
    popd
    popd


Install PyEDDL and PyECVL
-------------------------

You need the development version of python3 and pip. On Ubuntu, install
``python3-dev`` and ``python3-pip``.

Install the Python dependencies::

    python3 -m pip install --upgrade setuptools pip numpy pybind11 pytest

The EDDL code includes Eigen headers like in this example: ``#include
<Eigen/Dense>``, e.g., with ``Eigen`` as the root directory. However, Eigen
installations usually have the header rooted at ``eigen3`` (for instance, the
apt installation places them in ``/usr/include/eigen3``). To work around this
you can either add a symlink or set `CPATH`, e.g.::

    export CPATH="/usr/include/eigen3:${CPATH}"

Install pyeddl and pyecvl::

    pushd third_party/pyeddl
    python3 setup.py install
    popd
    python3 setup.py install
