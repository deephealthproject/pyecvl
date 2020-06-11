#!/usr/bin/env bash

set -euo pipefail

docker build -t manylinux-cuda101 -f Dockerfile.manylinux-cuda101 .
docker build -t ecvl-manylinux-gpu -f Dockerfile.ecvl-manylinux-gpu .
docker build -t pyecvl-manylinux-gpu -f Dockerfile.manylinux-gpu .
# copy the wheels to /tmp/wheels on the host
docker run --rm pyecvl-manylinux-gpu bash -c "tar -c -C /pyecvl wheels" | tar -x -C /tmp
