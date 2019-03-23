pipeline 
{
    agent any
    environment
    {
        BUILD_DIR = "${env.WORKSPACE}/build"
        BUILD_TYPE = "Release"
        INSTALL_DIR = "${env.BUILD_DIR}/install"
        TEST_DIR = "${env.BUILD_DIR}/tmp"
        DISPLAY = "$DISPLAY"
        LD_LIBRARY_PATH = "$LD_LIBRARY_PATH"
    }
    stages 
    {
        stage('Build') 
        {
            steps 
            {
                dir("${env.BUILD_DIR}")
                {
                    sh(script:"cmake -DCMAKE_BUILD_TYPE=${env.BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${env.INSTALL_DIR} ${env.WORKSPACE}")
                    sh(script:'make -j$(nproc)')
                    remove("${env.INSTALL_DIR}")
                    sh(script:'make -j$(nproc) install')
                }
            }
        }
        stage('GTest')
        {
            steps
            {
                remove("${env.TEST_DIR}")
                dir("${env.TEST_DIR}")
                {
                    gTest("${env.INSTALL_DIR}/bin/bgr2hsvTest", "--gtest_output=xml:${env.TEST_DIR}/bgr2hsvTest.xml")
                }
            }
        }
    }
    post
    {
        always
        {
            xunit
            {
xunit([GoogleTest(deleteOutputFiles: true, failIfNotNew: true, pattern: "${env.TEST_DIR}/*.xml", skipNoTestFiles: false, stopProcessingIfError: true)])
            }
        }
    }
}

def remove(String files)
{
    sh(script:"rm -rf ${files}")
}

def gTest(String tester, String args = "")
{
    def status = sh(script:"${tester} ${args}", returnStatus:true)
    if (status != 0)
    {
        error("[${tester}] GTest failed")
    }
}