#!/usr/bin/env bash

set -euo pipefail

pushd third_party/pyeddl
docker build -t eddl-gpu -f Dockerfile.eddl-gpu .
popd

docker build -t ecvl-gpu -f Dockerfile.ecvl-gpu .
docker build -t pyecvl-gpu -f Dockerfile.gpu .
