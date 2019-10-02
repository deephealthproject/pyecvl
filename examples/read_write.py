import itertools
import os

import pyecvl._core.ecvl as ecvl


THIS_DIR = os.path.dirname(os.path.abspath(__file__))
TEST_IMG = os.path.join(
    THIS_DIR, os.pardir, "third_party", "ecvl", "data", "test.jpg"
)


def main():
    in_path = TEST_IMG
    img = ecvl.Image()
    ecvl.ImRead(in_path, img)
    view = ecvl.View_uint8(img)
    for idx in itertools.product(*[range(_) for _ in img.dims_]):
        view[idx] = min(view[idx] + 10, 255)
    out_path = os.path.basename(TEST_IMG)
    ecvl.ImWrite(out_path, img)


if __name__ == "__main__":
    main()
