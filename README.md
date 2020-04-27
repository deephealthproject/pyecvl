<div align="center">
  <img src="https://raw.githubusercontent.com/deephealthproject/pyecvl/master/docs/logo.png" height="220" width="185">
</div>

-----------------


[![Build Status](https://jenkins-master-deephealth-unix01.ing.unimore.it/badge/job/DeepHealth/job/pyecvl/job/master/linux_end?)](https://jenkins-master-deephealth-unix01.ing.unimore.it/job/DeepHealth/job/pyecvl/job/master/)

**PyECVL** is a Python wrapper for [ECVL](https://github.com/deephealthproject/ecvl), the European Computer Vision Library.

Here is a short example of what you can do with PyECVL:

```python
import numpy as np
import pyecvl.ecvl as ecvl

def inc_brightness(img, rate):
    a = np.array(img, copy=False)
    max_val = np.iinfo(a.dtype).max
    a[a > max_val - rate] = max_val
    a[a <= max_val - rate] += rate

def main():
    img = ecvl.ImRead("test.jpg")
    inc_brightness(img, 10)
    ecvl.ImWrite("test_mod.jpg", img)

if __name__ == "__main__":
    main()
```

The PyECVL documentation is available at
https://deephealthproject.github.io/pyecvl.

Quick links:

* [Installation](https://deephealthproject.github.io/pyecvl/installation.html)
* [Getting Started](https://deephealthproject.github.io/pyecvl/getting_started.html)
