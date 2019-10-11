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
