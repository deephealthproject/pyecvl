# PyECVL

Python bindings for ECVL.

```
docker build -t ecvl -f Dockerfile.ecvl .
bash generate_bindings.sh
docker build -t pyecvl .
```

Note that `generate_bindings.sh` copies the opencv includes from the ecvl img.
