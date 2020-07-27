#!/usr/bin/env bash

set -euo pipefail

# Current Dockerfile.eddl-gpu in pyeddl has gcc 5 and cmake 3.14, which are
# too old for ecvl.

# pushd third_party/pyeddl
# docker build -t eddl-gpu -f Dockerfile.eddl-gpu .
# popd
docker build -t eddl-gpu -f Dockerfile.eddl-gpu .

docker build -t ecvl-gpu -f Dockerfile.ecvl-gpu .
docker build -t pyecvl-gpu -f Dockerfile.gpu .
