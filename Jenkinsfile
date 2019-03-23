pipeline 
{
    agent any
    environment
    {
        BUILD_DIR = "${env.WORKSPACE}/build"
        BUILD_TYPE = "Release"
        INSTALL_DIR = "${env.BUILD_DIR}/install"
        TEST_DIR = "${env.BUILD_DIR}/tmp"
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
                    sh(script:'make -j$(nproc) install')
                }
            }
        }
        stage('GTest')
        {
            steps
            {
                dir("${env.TMP_DIR}")
                {
                    gTest("${env.INSTALL_DIR}/bin/bgr2hsvTest")
                }
            }
        }
        stage('Visualize')
        {
            steps
            {
                visualize(30)
            }
        }
    }
}

def visualize(int timeout)
{
    def status = sh(script:"timeout 30 ${env.INSTALL_DIR}/bin/visualize", returnStatus: true)
    if (status != 124)
    {
        error("[visualise] with DISPLAY [${env.DISPLAY}] failed")
    }
}

def gTest(String tester, String args = "")
{
    def status = sh(script:"${tester} ${args}", returnStatus:true)
    if (status != 0)
    {
        error("[${tester}] GTeest failed")
    }
}