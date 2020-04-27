.. _installation:

Installation
============

To install PyECVL, you need to install ECVL first. Installation instructions
for ECVL are available in the `ECVL README
<https://github.com/deephealthproject/ecvl/blob/master/README.md>`_.

As shown in the above README, Some ECVL components are optional. By
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

The following sections contain instructions to install PyECVL from scratch,
assuming installation of all EDDL and ECVL optional modules. We use Ubuntu
Linux as an example platform.


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
you can either add a symlink or set ``CPATH``, e.g.::

    export CPATH="/usr/include/eigen3:${CPATH}"

Install pyeddl and pyecvl::

    pushd third_party/pyeddl
    python3 setup.py install
    popd
    python3 setup.py install

Alternatively, in the case of tagged releases, you can also install PyEDDL and
PyECVL with pip. The following table shows the required ECVL and PyEDDL
versions for each PyECVL version:

+----------------+--------------+----------------+
| PyECVL version | ECVL version | PyEDDL version |
+================+==============+================+
| 0.1.0          | 0.1.0        | 0.1.0          |
+----------------+--------------+----------------+
| 0.2.0          | 0.2.0        | 0.6.0          |
+----------------+--------------+----------------+

Thus, for instance, to install PyECVL 0.2.0::

    python3 -m pip install pyeddl==0.6.0
    python3 -m pip install pyecvl==0.2.0


Disabling unwanted modules
--------------------------

By default, PyECVL assumes a complete ECVL installation, including optional
modules (except for the GUI), and builds bindings for all of them. You can
disable support for specific modules via environment variables. For instance,
suppose you installed ECVL without OpenSlide support: by default, PyECVL will
try to build the bindings for OpenSlide-specific ECVL tools and link the
OpenSlide library, which might not even be present on your system. To avoid
this, set the ``ECVL_WITH_OPENSLIDE`` environment variable to ``OFF`` (or
``FALSE``) before building PyECVL. Similarly, you can turn off DICOM and EDDL
support by setting ``ECVL_WITH_DICOM`` and ``ECVL_EDDL`` to ``OFF``.


ECVL installed in an arbitrary directory
----------------------------------------

The above installation instructions assume installation in standard system
paths (such as ``/usr/local/include``, ``/usr/local/lib``). However, ECVL can
be installed in an arbitrary directory, for instance::

    cd third_party/ecvl
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=/home/myuser/ecvl -DECVL_WITH_DICOM=ON \
      -DECVL_WITH_OPENSLIDE=ON -DECVL_DATASET=ON -DECVL_BUILD_EDDL=ON ..
    make
    make install

You can tell the PyECVL setup script about this via the ``ECVL_DIR``
environment variable::

    export ECVL_DIR=/home/myuser/ecvl
    python3 setup.py install

In this way, ``setup.py`` will look for additional include files in
``/home/myuser/ecvl/include`` and for additional libraries in
``/home/myuser/ecvl/lib``.

Similarly, if EDDL is installed in an arbitrary path, you can tell the setup
script via the ``EDDL_DIR`` environment variable.
