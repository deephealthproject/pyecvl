SHELL := /bin/bash
ECVL_REV := $(shell git -C third_party/ecvl rev-parse --short HEAD)
PYEDDL_REV := $(shell git -C third_party/pyeddl rev-parse --short HEAD)
JENKINS_IMG := dhealth/dev-pyecvl-base-cpu
JENKINS_TAG := $(ECVL_REV)-$(PYEDDL_REV)

# all: pyecvl-cpu pyecvl-gpu pyecvl-cudnn

# eddl images
eddl-base: third_party/pyeddl
	make -C $< eddl-base

eddl-cpu: third_party/pyeddl
	make -C $< eddl-cpu

eddl-gpu: third_party/pyeddl
	make -C $< eddl-gpu

eddl-cudnn: third_party/pyeddl
	make -C $< eddl-cudnn

# ecvl/pyecvl images
ecvl-base-cpu: docker/Dockerfile.ecvl-base eddl-cpu
	docker build --build-arg target=cpu -t dhealth/dev-ecvl-base-cpu -f $< .

ecvl-base-gpu: docker/Dockerfile.ecvl-base eddl-gpu
	docker build --build-arg target=gpu -t dhealth/dev-ecvl-base-gpu -f $< .

ecvl-base-cudnn: docker/Dockerfile.ecvl-base eddl-cudnn
	docker build --build-arg target=cudnn -t dhealth/dev-ecvl-base-cudnn -f $< .

ecvl-cpu: docker/Dockerfile.ecvl-cpu ecvl-base-cpu
	docker build -t dhealth/dev-ecvl-cpu -f $< .

ecvl-gpu: docker/Dockerfile.ecvl-gpu ecvl-base-gpu
	docker build -t dhealth/dev-ecvl-gpu -f $< .

ecvl-cudnn: docker/Dockerfile.ecvl-cudnn ecvl-base-cudnn
	docker build -t dhealth/dev-ecvl-cudnn -f $< .

pyecvl-base-cpu: docker/Dockerfile.pyecvl-base ecvl-cpu
	docker build --build-arg target=cpu -t dhealth/dev-pyecvl-base-cpu -f $< .

pyecvl-base-gpu: docker/Dockerfile.pyecvl-base ecvl-gpu
	docker build --build-arg target=gpu -t dhealth/dev-pyecvl-base-gpu -f $< .

pyecvl-base-cudnn: docker/Dockerfile.pyecvl-base ecvl-cudnn
	docker build --build-arg target=cudnn -t dhealth/dev-pyecvl-base-cudnn -f $< .

pyecvl-cpu: docker/Dockerfile.pyecvl-cpu pyecvl-base-cpu
	docker build -t dhealth/dev-pyecvl-cpu -f $< .

pyecvl-gpu: docker/Dockerfile.pyecvl-gpu pyecvl-base-gpu
	docker build -t dhealth/dev-pyecvl-gpu -f $< .

pyecvl-cudnn: docker/Dockerfile.pyecvl-cudnn pyecvl-base-cudnn
	docker build -t dhealth/dev-pyecvl-cudnn -f $< .

docs: docker/Dockerfile.docs pyecvl-cpu
	docker build -t dhealth/dev-pyecvl-docs -f $< .

ecvl-minimal: docker/Dockerfile.ecvl-minimal
	docker build -t dhealth/dev-ecvl-minimal -f $< .

pyecvl-minimal: docker/Dockerfile.pyecvl-minimal ecvl-minimal
	docker build -t dhealth/dev-pyecvl-minimal -f $< .

#commands
test-cpu: pyecvl-cpu
	docker run --rm dhealth/dev-pyecvl-cpu pytest tests

test-gpu: pyecvl-gpu
	docker run --rm dhealth/dev-pyecvl-gpu pytest tests

test-cudnn: pyecvl-cudnn
	docker run --rm dhealth/dev-pyecvl-cudnn pytest tests

test-minimal: pyecvl-minimal
	docker run --rm dhealth/dev-pyecvl-minimal pytest tests

run-examples-cpu: pyecvl-cpu
	docker run --rm dhealth/dev-pyecvl-cpu bash examples/run_all.sh /ecvl/examples/data

run-examples-gpu: pyecvl-gpu
	docker run --rm dhealth/dev-pyecvl-gpu bash examples/run_all.sh /ecvl/examples/data

run-examples-cudnn: pyecvl-cudnn
	docker run --rm dhealth/dev-pyecvl-cudnn bash examples/run_all.sh /ecvl/examples/data

run-examples-minimal: pyecvl-minimal
	docker run --rm dhealth/dev-pyecvl-minimal bash examples/run_all.sh /ecvl/examples/data

get-docs: docs
	rm -rf /tmp/html && docker run --rm dhealth/dev-pyecvl-docs bash -c "tar -c -C /pyecvl/docs/source/_build html" | tar -x -C /tmp

update-jenkins-image: pyecvl-base-cpu
	docker tag $(JENKINS_IMG) $(JENKINS_IMG):$(JENKINS_TAG) && \
	docker push $(JENKINS_IMG):$(JENKINS_TAG) && \
	sed -i 's|$(JENKINS_IMG):[a-f0-9-]\+|$(JENKINS_IMG):$(JENKINS_TAG)|g' Jenkinsfile
