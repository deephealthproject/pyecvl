"""\
Performs image processing on an input image.
"""

import argparse
import os
import sys

import numpy as np
import pyecvl._core.ecvl as ecvl


def main(args):
    head, ext = os.path.splitext(os.path.basename(args.in_fn))
    tmp = ecvl.Image()
    img = ecvl.ImRead(args.in_fn)

    print("Resizing image by new width, height")
    ecvl.ResizeDim(img, tmp, [225, 300], ecvl.InterpolationType.nearest)
    ecvl.ImWrite("%s_resized%s" % (head, ext), tmp)

    print("Resizing image by scale factor")
    ecvl.ResizeScale(img, tmp, [2, 2], ecvl.InterpolationType.cubic)
    ecvl.ImWrite("%s_resized_scale%s" % (head, ext), tmp)

    print("Flipping image")
    ecvl.Flip2D(img, tmp)
    ecvl.ImWrite("%s_flipped%s" % (head, ext), tmp)

    print("Mirroring image")
    ecvl.Mirror2D(img, tmp)
    ecvl.ImWrite("%s_mirrored%s" % (head, ext), tmp)

    print("Rotating image")
    ecvl.Rotate2D(img, tmp, 60)
    ecvl.ImWrite("%s_rotated%s" % (head, ext), tmp)

    print("Rotating image with scaling and resizing")
    ecvl.RotateFullImage2D(img, tmp, 60, 1.5)
    ecvl.ImWrite("%s_rotated_full%s" % (head, ext), tmp)

    print("Changing color space to gray")
    ecvl.ChangeColorSpace(img, tmp, ecvl.ColorType.GRAY)
    ecvl.ImWrite("%s_gray%s" % (head, ext), tmp)

    print("Calculating Otsu threshold")  # image must be gray
    thr = ecvl.OtsuThreshold(tmp)
    print("  %d" % thr)

    print("Applying fixed threshold")
    ecvl.Threshold(tmp, tmp, thr, 255)
    ecvl.ImWrite("%s_threshold%s" % (head, ext), tmp)

    print("Labeling connected components")
    labels = ecvl.Image()
    ecvl.ConnectedComponentsLabeling(tmp, labels)
    ecvl.ImWrite("%s_labels%s" % (head, ext), labels)

    print("Finding contours")
    contours = ecvl.FindContours(tmp)
    print("  [%r ... %r]" % (contours[0], contours[-1]))

    print("Applying filter")
    # kernel must be float64, "xyc" and with one color channel
    kernel = ecvl.Image(
        [3, 3, 1], ecvl.DataType.float64, "xyc", ecvl.ColorType.GRAY
    )
    a = np.array(kernel, copy=False)
    a.fill(0.11)
    ecvl.Filter2D(img, tmp, kernel)
    ecvl.ImWrite("%s_filter%s" % (head, ext), tmp)

    print("Applying separable filter")
    ecvl.SeparableFilter2D(img, tmp, [1, 2, 1], [1, 0, -1])
    ecvl.ImWrite("%s_separable_filter%s" % (head, ext), tmp)

    print("Blurring with gaussian kernel")
    ecvl.GaussianBlur(img, tmp, 5, 5, 0.0)
    ecvl.ImWrite("%s_gaussian_blur%s" % (head, ext), tmp)

    print("Adding Laplace noise")
    stddev = 255 * 0.05
    ecvl.AdditiveLaplaceNoise(img, tmp, stddev)
    ecvl.ImWrite("%s_laplace_noise%s" % (head, ext), tmp)

    print("Adjusting contrast")
    gamma = 3
    ecvl.GammaContrast(img, tmp, gamma)
    ecvl.ImWrite("%s_gamma_contrast%s" % (head, ext), tmp)

    print("Setting rectangles to zero (coarse dropout)")
    prob, drop_size, per_channel = 0.5, 0.1, True
    ecvl.CoarseDropout(img, tmp, prob, drop_size, per_channel)
    ecvl.ImWrite("%s_coarse_dropout%s" % (head, ext), tmp)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
