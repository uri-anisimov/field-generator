pipeline 
{
    agent any
    environment
    {
        BUILD_DIR = "${env.WORKSPACE}/build"
        BUILD_TYPE = "Release"
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
                }
            }
        }
    }
}
