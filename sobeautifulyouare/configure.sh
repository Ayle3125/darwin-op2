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
cp source/data/golf.txt bin/golf.txt
cp source/data/blue.jpg bin/blue.jpg
cp source/data/red.jpg bin/red.jpg
cp source/data/golf.jpg bin/golf.jpg
cp source/data/yellow.jpg bin/yellow.jpg

cp source/data/hongqiu.jpg bin/hongqiu.jpg
cp source/data/golfgoal.jpg bin/golfgoal.jpg
cp source/data/golfgoal.txt bin/golfgoal.txt
cp source/data/lanmen.jpg bin/lanmen.jpg
cp source/data/lanmen.txt bin/lanmen.txt
cp source/data/lvqiu.jpg bin/lvqiu.jpg
cp source/data/hongqiu.txt bin/hongqiu.txt
cp source/data/lvqiu.txt bin/lvqiu.txt

cp source/data/cmake-build.sh all-build/cmake-build.sh
chmod +x all-build/cmake-build.sh
cp source/data/make-build.sh all-build/make-build.sh
chmod +x all-build/make-build.sh


