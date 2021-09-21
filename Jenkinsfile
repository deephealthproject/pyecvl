pipeline {
    agent none
    stages {
        stage('Parallel Stages') {
            parallel {
                stage('linux') {
                    agent {
                        docker {
                            label 'docker'
                            image 'simleo/pyecvl-base:4c1b616-1e82e5c'
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
				sh 'pytest tests'
				sh 'bash examples/run_all.sh /ecvl/examples/data'
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
