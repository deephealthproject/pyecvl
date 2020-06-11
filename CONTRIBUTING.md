# How to contribute

PyECVL uses the [binder](https://github.com/RosettaCommons/binder) tool to
generate [pybind11](https://github.com/pybind/pybind11) bindings. The
resulting files are committed to the repository, and can be regenerated with:

```
bash generate_bindings.sh
```

Note that the above script uses the ecvl Docker image to get the opencv
includes needed for bindings generation. Therefore, if you don't have it,
build the ecvl image before running `generate_bindings`:

```
docker build -t ecvl -f Dockerfile.ecvl .
```

Regenerating the bindings can be necessary after updating the reference ECVL
revision or after making changes to the code generation setup (configuration
and include list). Note that add-ons are often necessary to complete the
bindings (see `codegen/config.cfg`).

To test the bindings on Docker, build the PyECVL image with:

```
docker build -t pyecvl .
```

Then you can run tests and/or examples on Docker, e.g.:

```
docker run --rm -it pyecvl bash
cd examples
python3 read_write.py
```


## How to build the manylinux wheels

A Docker setup is in place to build manylinux binary wheels for PyECVL. See
the `build_manylinux_wheels_gpu.sh` script in the repository root
directory. The script copies the generated wheels to `/tmp/wheels` on the
host. You can test them with:

```
python3 -m pip install pyecvl -f /tmp/wheels/
```

Note that the GPU wheels are built for CUDA 10.1.
