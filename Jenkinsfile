
//pipeline generated with snippet generator assist(button pipeline syntax)
pipeline{
//    agent {
//  label '192.168.1.100:5505/build_agent_mskbo_jenkins:latest'
//}
//agent {
    //docker {
        //image 'mskbo_build:latest'
        //label 'agent1'
        //registryUrl 'http://127.0.0.1:5505'//using virtual network jenkins IP
        //registryCredentialsId 'myPredefinedCredentialsInJenkins'
    //}
    agent {
  dockerfile {
    dir './mskbo/docker/mskbo_docker/dockerfile'
    filename 'Dockerfile'
  }
//}
}
    stages{
        stage("build source MSKBO"){
                steps{
                echo 'Building..'
                git credentialsId: 'c0e07e54-5619-43d4-939b-c09f8348369b', url: 'https://gitea.mskbo.keenetic.name/MSKBOdev/mskbo.git'
                sh './mskbo/install'
                }
        }
    }
}