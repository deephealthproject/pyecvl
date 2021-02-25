.. _installation:

Installation
============

.. note::

    We recommend using the `DeepHealth Docker images
    <https://github.com/deephealthproject/docker-libs>`_, which provide
    ready-to-use containers for the DeepHealth components, including
    PyECVL. If you want to install PyECVL manually instead, read on.

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

ECVL needs a compiler with C++17 support. You also need to install the
development version of the OpenCV and OpenSlide libraries. EDDL needs the
development versions of the zlib and Eigen3 libraries. To enable ONNX I/O, you
also need to install Google protobuf. On Ubuntu, for instance, install the
following with APT: ``libopencv-dev, libopenslide-dev, zlib1g-dev,
libeigen3-dev, wget, ca-certificates``. Install protobuf from source::

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
    cmake -DECVL_SHARED=ON -DECVL_WITH_DICOM=ON -DECVL_WITH_OPENSLIDE=ON -DECVL_DATASET=ON -DECVL_BUILD_EDDL=ON
    make -j$(nproc)
    make install
    popd
    popd


Install PyEDDL and PyECVL
-------------------------

You need the development version of python3 and pip. On Ubuntu, install
``python3-dev`` and ``python3-pip``.

Install the Python dependencies. Note that, at the moment, the pybind11
version needs to be less than 2.6::

    python3 -m pip install --upgrade setuptools pip
    python3 -m pip install --upgrade numpy 'pybind11<2.6' pytest

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
| 0.2.1          | 0.2.0        | 0.6.0          |
+----------------+--------------+----------------+
| 0.3.0          | 0.2.1        | 0.6.0          |
+----------------+--------------+----------------+
| 0.4.*          | 0.2.2        | 0.8.0          |
+----------------+--------------+----------------+
| 0.5.0          | 0.2.3        | 0.8.0          |
+----------------+--------------+----------------+
| 0.5.1          | 0.2.3        | 0.9.0          |
+----------------+--------------+----------------+
| 0.5.2          | 0.2.3        | 0.10.1         |
+----------------+--------------+----------------+
| 0.6.0          | 0.3.0        | 0.10.1         |
+----------------+--------------+----------------+
| 0.7.0          | 0.3.1        | 0.12.0         |
+----------------+--------------+----------------+
| 0.7.1          | 0.3.1        | 0.13.0         |
+----------------+--------------+----------------+

Thus, for instance, to install PyECVL 0.6.0::

    python3 -m pip install pyeddl==0.10.1
    python3 -m pip install pyecvl==0.6.0


Disabling optional modules
--------------------------

ECVL and PyECVL have a number of optional components whose compilation can be disabled at
build time.  The build settings for these components must match across the two libraries.

.. warning::
    If you compile both libraries with the their respective default settings
    the resulting Python extention won't work (you'll have undefined symbols).

By default, **PyECVL assumes a complete installation, but ECVL does not**.

That is, PyECVL by default includes all optional modules (except for the GUI),
and builds bindings for all of them; on the other hand, ECVL includes only a
subset of the optional components.

You can control the inclusion of specific modules via build variables set at
library compile time.

This is the list of optional components and respective variable names.

+------------+---------------------+----------------------+---------------------+--------------------+
| Module     | PyECVL Variable     | Default PyECVL Value | ECVL Variable       | Default ECVL Value |
+============+=====================+======================+=====================+====================+
| DICOM      | ECVL_WITH_DICOM     | ON                   | ECVL_WITH_DICOM     | OFF                |
+------------+---------------------+----------------------+---------------------+--------------------+
| OPENSLIDE  | ECVL_WITH_OPENSLIDE | ON                   | ECVL_WITH_OPENSLIDE | OFF                |
+------------+---------------------+----------------------+---------------------+--------------------+
| DATASET    | (N/A)               | ON                   | ECVL_DATASET        | OFF                |
+------------+---------------------+----------------------+---------------------+--------------------+
| EDDL       | ECVL_EDDL           | ON                   | ECVL_BUILD_EDDL     | ON                 |      
+------------+---------------------+----------------------+---------------------+--------------------+

Note that it's currently not possible to turn off the ``DATASET`` module in
PyECVL, so you *must* compile ECVL with ``ECVL_DATASET`` support.

For a description of the modules, [see the ecvl installation instructions](https://github.com/deephealthproject/ecvl).

.. note::

    To set the variables for the ECVL build, pass them to `cmake` as in:

        ``cmake -DECVL_SHARED=ON -DECVL_WITH_DICOM=ON``

    To set the variables for the PyECVL build, set them in the environment, as in:

        ``export ECVL_WITH_OPENSLIDE=OFF; python3 setup.py install``


For instance, suppose you wanted to install PyECVL with OpenSlide support:

1. Build ECVL with at least ``-DECVL_WITH_OPENSLIDE=ON``;
2. Build PyECVL with the **environment variable** ``ECVL_WITH_OPENSLIDE=ON`` (default value).

Conversely, to build without OpenSlide support:

1. Build ECVL with ``-DECVL_WITH_OPENSLIDE=OFF`` (default value);
2. Build PyECVL with the **environment variable** ``ECVL_WITH_OPENSLIDE=OFF``.


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


FAQ
-----

ImportError: undefined symbol ... ecvl ... OpenSlide
+++++++++++++++++++++++++++++++++++++++++++++++++++++

You likely have an ECVL library build without OpenSlide support
(``ECVL_WITH_OPENSLIDE=OFF`` -- default value) and PyECVL library build with
OpenSlide support (``ECVL_WITH_OPENSLIDE=ON`` -- default value).

The full stack trace might look like this::

    ImportError                               Traceback (most recent call last)
    <ipython-input-3-ee58876f5538> in <module>
          4 
          5 import numpy as np
    ----> 6 import pyecvl.ecvl as ecvl
          7 import pyeddl.eddl as eddl
          8 import pyeddl.eddlT as eddlT~/projects/p138-dh2/.conda/envs/p138-dh2-env-kdh467/lib/python3.6/site-packages/pyecvl/ecvl.py in <module>
         19 # SOFTWARE.
         20 
    ---> 21 from . import _core
         22 _ecvl = _core.ecvl
         23 ImportError: /home/jovyan/projects/p138-dh2/.conda/envs/p138-dh2-env-kdh467/lib/python3.6/site-packages/pyecvl/_core.cpython-36m-x86_64-linux-gnu.so: undefined symbol: _ZN4ecvl18OpenSlideGetLevelsERKNSt10filesystem7__cxx114pathERSt6vectorISt5arrayIiLm2EESaIS7_EE

