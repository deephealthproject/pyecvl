# PyECVL

**PyECVL** is a Python wrapper for [ECVL](https://github.com/deephealthproject/ecvl), the European Computer Vision Library.


## Quick start

    git clone --recurse-submodules https://github.com/deephealthproject/pyecvl.git
    cd pyecvl
    python3 -m pip install numpy pybind11 pytest
    python3 setup.py install
    pytest tests

See [full installation instructions below](#installation).


## Getting started

```python
import os

import numpy as np
import pyecvl._core.ecvl as ecvl


THIS_DIR = os.path.dirname(os.path.abspath(__file__))
TEST_IMG = os.path.join(
    THIS_DIR, os.pardir, "third_party", "ecvl", "data", "test.jpg"
)


def inc_brightness(img, rate):
    a = np.array(img, copy=False)
    max_val = np.iinfo(a.dtype).max
    a[a > max_val - rate] = max_val
    a[a <= max_val - rate] += rate


def main():
    in_path = TEST_IMG
    img = ecvl.Image()
    ecvl.ImRead(in_path, img)
    inc_brightness(img, 10)
    out_path = os.path.basename(TEST_IMG)
    ecvl.ImWrite(out_path, img)


if __name__ == "__main__":
    main()
```


## Installation

### Requirements

- Python 3
- ECVL
- NumPy
- pybind11
- pytest (if you want to run the tests)


### ECVL Installation

Complete ECVL installation instructions are available at
https://github.com/deephealthproject/ecvl. Here is a sample build sequence:

```
cd third_party/ecvl
mkdir build
cd build
cmake -DECVL_WITH_OPENSLIDE=ON -DECVL_DATASET_PARSER=ON -DECVL_BUILD_EDDL=ON ..
make
make install
```

Make sure ECVL installation artifacts are in "standard" system locations, such
as `/usr/local/include` and `/usr/local/lib`. The ECVL installation procedure
should automatically take care of this.


### PyECVL installation

Install PyECVL as follows:

```
python3 -m pip install numpy pybind11 pytest
python3 setup.py install
```

Then, you can test your installation by running the PyECVL tests:

    pytest tests
