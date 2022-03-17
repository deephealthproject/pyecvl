pipeline {
    agent none
    stages {
        stage('Parallel Stages') {
            parallel {
                stage('linux') {
                    agent {
                        docker {
                            label 'docker'
                            image 'dhealth/dev-pyecvl-base-cpu:5aa2785-4205ad6'
                        }
                    }
                    stages {
                        stage('Build') {
                            steps {
				echo 'Building'
				sh 'git submodule update --init --recursive third_party/pyeddl'
				sh 'rm -rf build'
				sh 'python3 setup.py install --user'
				dir("third_party/pyeddl") {
				    sh 'rm -rf build'
				    sh 'python3 setup.py install --user'
				}
                            }
                        }
                        stage('Test') {
                            steps {
				echo 'Testing'
				sh 'timeout 60 pytest tests'
				sh 'timeout 300 bash examples/run_all.sh /ecvl/examples/data'
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
