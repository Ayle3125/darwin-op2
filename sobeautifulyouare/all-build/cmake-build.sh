#!/bin/sh
cd DarwinFramework && cmake . && make && cd ..
cd DarwinLinux && cmake . && make && cd ..
cd Communication && cmake .  && make && cd ..
cd Motion && cmake .  && make && cd ..
cd VisionCam && cmake .  && make && cd ..
cd VisionBlob && cmake .  && make && cd ..
cd VisionImgproc && cmake . -DOpenCV_DIR=/usr/local/opencv/release  && make &&  cd ..
cd Strategy && cmake . -DOpenCV_DIR=/usr/local/opencv/release && make &&  cd ..
cd Demo && cmake . -DOpenCV_DIR=/usr/local/opencv/release  && make  && cd ..
#if DarWin cmake . -DOpenCV_DIR=/usr/local/opencv/release


