pipeline {
    agent none
    stages {
        stage('Parallel Stages') {
            parallel {
                stage('linux') {
                    agent {
                        docker {
                            label 'docker'
                            image 'simleo/ecvl:6adebb5'
                            args '-u root:root'
                        }
                    }
                    stages {
                        stage('Build') {
                            steps {
				echo 'Building'
				sh 'cp -rf . /tmp/pyecvl'
				dir("/tmp/pyecvl") {
				    sh 'apt-get -y update && apt-get -y install --no-install-recommends python3-dev python3-pip git'
				    sh 'git submodule update --init --recursive third_party/pyeddl'
				    sh 'python3 -m pip install --upgrade --no-cache-dir setuptools pip numpy pybind11 pytest'
				    sh 'rm -rf build'
				    sh 'python3 setup.py install'
				    dir("third_party/pyeddl") {
					sh 'rm -rf build'
					sh 'python3 setup.py install'
				    }
				}
                            }
                        }
                        stage('Test') {
                            steps {
				echo 'Testing'
				dir("/tmp/pyecvl") {
				    sh 'pytest tests'
				    sh 'python3 examples/dataset.py /ecvl/examples/data/mnist/mnist.yml'
				    sh 'python3 examples/ecvl_eddl.py /ecvl/examples/data/test.jpg /ecvl/examples/data/mnist/mnist.yml'
				    sh 'python3 examples/img_format.py /ecvl/examples/data/nifti/LR_nifti.nii /ecvl/examples/data/dicom/ISIC_0000008.dcm'
				    sh 'python3 examples/imgproc.py /ecvl/examples/data/test.jpg'
				    sh 'python3 examples/openslide.py "/ecvl/examples/data/hamamatsu/test3-DAPI 2 (387).ndpi"'
				    sh 'python3 examples/read_write.py /ecvl/examples/data/test.jpg test_mod.jpg'
				}
                            }
                        }
                        stage('linux_end') {
                            steps {
                                echo 'Success!'
                            }
                        }
                    }
                    post {
                        cleanup {
                            deleteDir()
                        }
                    }
                }
            }
        }
    }
}
