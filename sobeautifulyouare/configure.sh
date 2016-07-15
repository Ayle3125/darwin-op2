#!/bin/sh

if test -d all-build
then
	rm -rf all-build/*
else
	mkdir all-build
fi

if test -d bin
then 
	rm -rf bin/*
else
	mkdir bin
fi

cd all-build			# now in all-build

mkdir DarwinFramework && cp ../source/data/CMakeLists-DarwinFramework.txt DarwinFramework/CMakeLists.txt

mkdir DarwinLinux && cp ../source/data/CMakeLists-DarwinLinux.txt DarwinLinux/CMakeLists.txt

mkdir Communication && cp ../source/data/CMakeLists-Communication.txt Communication/CMakeLists.txt

mkdir Motion && cp ../source/data/CMakeLists-Motion.txt Motion/CMakeLists.txt

mkdir Strategy && cp ../source/data/CMakeLists-Strategy.txt Strategy/CMakeLists.txt

mkdir VisionBlob && cp ../source/data/CMakeLists-VisionBlob.txt VisionBlob/CMakeLists.txt

mkdir VisionCam && cp ../source/data/CMakeLists-VisionCam.txt VisionCam/CMakeLists.txt

mkdir VisionImgproc && cp ../source/data/CMakeLists-VisionImgproc.txt VisionImgproc/CMakeLists.txt

mkdir Demo && cp ../source/data/CMakeLists-Demo.txt Demo/CMakeLists.txt

cd .. && cp source/data/color.data bin/color.data		# main path
cp source/data/ball.txt bin/ball.txt
cp source/data/redbox.txt bin/redbox.txt
cp source/data/yellowbox.txt bin/yellowbox.txt
cp source/data/bluebox.txt bin/bluebox.txt
cp source/data/blue.txt bin/blue.txt
cp source/data/red.txt bin/red.txt
cp source/data/blue.jpg bin/blue.jpg
cp source/data/red.jpg bin/red.jpg
cp source/data/yellow.jpg bin/yellow.jpg
cp source/data/cmake-build.sh all-build/cmake-build.sh
chmod +x all-build/cmake-build.sh
cp source/data/make-build.sh all-build/make-build.sh
chmod +x all-build/make-build.sh


