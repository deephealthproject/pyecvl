pipeline {
    agent none
    stages {
        stage('Parallel Stages') {
            parallel {
                stage('linux') {
                    agent {
                        docker {
                            label 'docker'
                            image 'simleo/ecvl:c811985'
                            args '-u root:root'
                        }
                    }
                    stages {
                        stage('Build') {
                            steps {
				echo 'Building'
				sh 'apt-get -y update && apt-get -y install --no-install-recommends python3-dev python3-pip git'
				sh 'git submodule update --init --recursive third_party/pyeddl'
				sh 'python3 -m pip install --upgrade --no-cache-dir setuptools pip numpy pybind11 pytest'
				sh 'python3 setup.py install'
				dir("third_party/pyeddl") {
				    sh 'python3 setup.py install'
				}
                            }
                        }
                        stage('Test') {
                            steps {
				echo 'Testing'
				sh 'pytest tests'
				sh 'python3 examples/dataset.py /ecvl/build/mnist/mnist.yml'
				sh 'python3 examples/ecvl_eddl.py /ecvl/data/test.jpg /ecvl/build/mnist/mnist.yml'
				sh 'python3 examples/img_format.py /ecvl/data/nifti/LR_nifti.nii'
				sh 'python3 examples/imgproc.py /ecvl/data/test.jpg'
				sh 'python3 examples/openslide.py /ecvl/data/hamamatsu/10-B1-TALG.ndpi'
				sh 'python3 examples/read_write.py /ecvl/data/test.jpg test_mod.jpg'
                            }
                        }
                        stage('linux_end') {
                            steps {
                                echo 'Success!'
                            }
                        }
                    }
                }
            }
        }
    }
}
