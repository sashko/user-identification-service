#!/usr/bin/groovy

// Copyright (C) 2019 Luxoft Sweden AB

def image

node("component") {
    stage("Checkout") {
        checkout scm
    }

    stage("Build Docker container") {
        image = docker.build("qtivi-mopidy-plugin", "-f Dockerfile .")
    }

    image.inside {
        stage("Download Raspberry Pi SDK") {
            sh '''
            wget https://pelux.io/jenkins/job/pelux-manifests_NIGHTLY_rpi-qtauto/lastSuccessfulBuild/artifact/artifacts_rpi-qtauto/pelux-glibc-x86_64-core-image-pelux-qtauto-neptune-dev-cortexa7t2hf-neon-vfpv4-toolchain-*.sh
            '''
        }

        stage("Install Raspberry Pi SDK") {
            sh '''
            chmod +x *.sh
            sudo ./pelux-glibc-x86_64-core-image-pelux-qtauto-neptune-dev-cortexa7t2hf-neon-vfpv4-toolchain-master.sh -y -d /opt/pelux-sdk-x86_64/master
            '''
        }

        stage("Build with Raspberry Pi SDK") {
            sh '''
            source /opt/pelux-sdk-x86_64/master/environment-setup-cortexa7t2hf-neon-vfpv4-pelux-linux-gnueabi
            mkdir bulid
            cd build
            meson ..
            ninja
            '''
        }
    }
}
