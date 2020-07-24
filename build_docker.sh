#!/usr/bin/env bash

set -euo pipefail

pushd third_party/pyeddl
docker build -t eddl -f Dockerfile.eddl .
popd
docker build -t ecvl -f Dockerfile.ecvl .
docker build -t pyecvl .
docker build -t pyecvl-docs -f Dockerfile.docs .
rm -rf /tmp/html && docker run --rm pyecvl-docs bash -c "tar -c -C /pyecvl/docs/source/_build html" | tar -x -C /tmp
