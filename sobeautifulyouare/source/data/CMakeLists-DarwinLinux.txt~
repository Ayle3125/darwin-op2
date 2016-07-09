
######################################################
#   - Modified by Paul in Nov, 2015                  #
#   - Demo about Darwin Robot                        #
######################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

#########################################################
#   - All variables which are used to name all direct-  #
#   - ories will be showed at next                      #
#########################################################

##### Set variables of the whole project #####
SET(ROBOT_DIR ${PROJECT_SOURCE_DIR}/../../)
SET(SOURCE_DIR ${ROBOT_DIR}/source)
SET(BINARY_DIR ${ROBOT_DIR}/bin)

SET(SOURCE_DARWIN_DIR ${SOURCE_DIR}/darwin)
SET(SOURCE_DATA_DIR ${SOURCE_DIR}/data)
SET(SOURCE_INCLUDE_DIR ${SOURCE_DIR}/include)
SET(SOURCE_MODULE_DIR ${SOURCE_DIR}/module)

#######################################################
#     - Darwin Module 								  #
#######################################################
###########  Framework ################
SET(DARWIN_DATA_DIR ${SOURCE_DARWIN_DIR}/Data)
SET(DARWIN_FRAMEWORK_DIR ${SOURCE_DARWIN_DIR}/Framework)
SET(DARWIN_LINUX_DIR ${SOURCE_DARWIN_DIR}/Linux)

SET(DARWIN_FRAMEWORK_INCLUDE_DIR ${DARWIN_FRAMEWORK_DIR}/include)
SET(DARWIN_FRAMEWORK_SRC_DIR ${DARWIN_FRAMEWORK_DIR}/src)

SET(DARWIN_FRAMEWORK_SRC_MATH_DIR ${DARWIN_FRAMEWORK_SRC_DIR}/math)
SET(DARWIN_FRAMEWORK_SRC_MININI_DIR ${DARWIN_FRAMEWORK_SRC_DIR}/minIni)
SET(DARWIN_FRAMEWORK_SRC_MOTION_DIR ${DARWIN_FRAMEWORK_SRC_DIR}/motion)
SET(DARWIN_FRAMEWORK_SRC_VISION_DIR ${DARWIN_FRAMEWORK_SRC_DIR}/vision)

SET(DARWIN_FRAMEWORK_SRC_MOTION_MODULES_DIR ${DARWIN_FRAMEWORK_SRC_MOTION_DIR}/modules)

########## Linux ####################
SET(DARWIN_LINUX_BUILD_DIR ${DARWIN_LINUX_DIR}/build)
SET(DARWIN_LINUX_INCLUDE_DIR ${DARWIN_LINUX_DIR}/include)

SET(DARWIN_LINUX_BUILD_STREAMER_DIR ${DARWIN_LINUX_BUILD_DIR}/streamer)

#############################################
#     - Modules 					    #
#############################################
SET(MODULE_COMMUNICATION_DIR ${SOURCE_MODULE_DIR}/communication)
SET(MODULE_MOTION_DIR ${SOURCE_MODULE_DIR}/motion)
SET(MODULE_STRATEGY_DIR ${SOURCE_MODULE_DIR}/strategy)
SET(MODULE_VISION_DIR ${SOURCE_MODULE_DIR}/vision)

SET(MODULE_VISION_BLOB_DIR ${MODULE_VISION_DIR}/blob)
SET(MODULE_VISION_CAM_DIR ${MODULE_VISION_DIR}/cam)
SET(MODULE_VISION_IMGPROC_DIR ${MODULE_VISION_DIR}/imgproc)

###################################################################
#   - Especially all include directories will be showed at next   #
#   - some variables defined upper will be used                   #
###################################################################

SET(DARWIN_INCLUDE_DIR ${DARWIN_FRAMEWORK_INCLUDE_DIR} ${DARWIN_FRAMEWORK_SRC_MININI_DIR} ${DARWIN_LINUX_BUILD_STREAMER_DIR} ${DARWIN_LINUX_INCLUDE_DIR})

SET(MODULE_INCLUDE_DIR ${MODULE_COMMUNICATION_DIR} ${MODULE_MOTION_DIR} ${MODULE_STRATEGY_DIR} ${MODULE_VISION_BLOB_DIR} ${MODULE_VISION_CAM_DIR} ${MODULE_VISION_IMGPROC_DIR})

#####################################################################
#####   - Prepare for building libraries and runtimes files     #####
#####################################################################

##### Set variables of the input or output directories #####
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROBOT_DIR}/bin)
SET(PROJECT_LIBRARY_PATH ${ROBOT_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${ROBOT_DIR}/bin)

#############################################################

INCLUDE_DIRECTORIES(BEFORE ${DARWIN_INCLUDE_DIR} ${MODULE_INCLUDE_DIR})

#############################################################
##### - build the darwin framework library              #####
#############################################################

SET(DARWIN_LINUX_LIB_SRCS ${DARWIN_LINUX_BUILD_DIR}/LinuxActionScript.cpp ${DARWIN_LINUX_BUILD_DIR}/LinuxCamera.cpp ${DARWIN_LINUX_BUILD_DIR}/LinuxCM730.cpp ${DARWIN_LINUX_BUILD_DIR}/LinuxMotionTimer.cpp ${DARWIN_LINUX_BUILD_DIR}/LinuxNetwork.cpp ${DARWIN_LINUX_BUILD_STREAMER_DIR}/httpd.cpp ${DARWIN_LINUX_BUILD_STREAMER_DIR}/jpeg_utils.cpp ${DARWIN_LINUX_BUILD_STREAMER_DIR}/mjpg_streamer.cpp)

FIND_LIBRARY(DARWIN_FRAMEWORK darwin_framework ${PROJECT_LIBRARY_PATH})

ADD_LIBRARY(darwin_linux SHARED ${DARWIN_LINUX_LIB_SRCS})

TARGET_LINK_LIBRARIES(darwin_linux pthread jpeg ${DARWIN_FRAMEWORK} dl rt)










