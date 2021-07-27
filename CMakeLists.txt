cmake_minimum_required(VERSION 3.16)

project(XDataFrameProject VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)




####################################################
# SPECIFY YOUR vcpkg.cmake LOCATION ON YOUR SYSTEM #
####################################################

set(VCPKG_LOCATION /home/nick/IRIS-HEP/vcpkg)

# Set your machines "triplet". On a 64 bit Windows machine, change to "x64-windows"
set(TRIPLET     x64-linux)


# set(CMAKE_TOOLCHAIN_FILE /home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)
include(/home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Locate packages

find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint )

# set(ryml_DIR /home/nick/IRIS-HEP/ryaml/install/lib/cmake/ryml )
set(c4core_DIR /home/nick/IRIS-HEP/vcpkg/packages/c4core_x64-linux/share/c4core)

# set(ryml_DIR /home/nick/IRIS-HEP/vcpkg/packages/ryml_x64-linux/share/ryml)
find_package(ryml CONFIG REQUIRED)

# set(jsoncpp_DIR ~/IRIS-HEP/vcpkg/packages/jsoncpp_x64-linux/share/jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

find_package(OpenSSL REQUIRED)

message(" - ryml include " ${ryml_LIBRARIES})
message(" - CURL include " ${CURL_INCLUDE_DIRS})


# Amazon AWS SDK External Project
# include(ExternalProject)

# set(AWS_TAGLIB "aws-sdk-cpp")

# set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")

# # when needing to fully download, it takes me 2m42s ... not great
# ExternalProject_Add(
#         ${AWS_TAGLIB}
#         GIT_REPOSITORY  https://github.com/aws/aws-sdk-cpp
#         # GIT_TAG         origin/master
#         CMAKE_ARGS      -DBUILD_ONLY="s3;cognito-identity"
#                         -DBUILD_SHARED_LIBS=OFF
#                         -DMINIMIZE_SIZE=ON
#                         -DCPP_STANDARD=14
#                         -DENABLE_TESTING=OFF
#                         -DBUILD_DEPS=ON
                        
#         GIT_SHALLOW    ON
# 	SOURCE_DIR     aws-sdk-cpp-prefix/src
# 	BUILD_ALWAYS   OFF
# 	INSTALL_DIR    ${EXTERNAL_INSTALL_LOCATION}
	
# 	# CMAKE_CACHE_ARGS
# 	# 	-DBUILD_SHARED_LIBS:BOOL=ON
# 	# 	-DENABLE_STATIC_RUNTIME:BOOL=OFF
# 	# 	-DBUILD_EXAMPLES:BOOL=ON
# 	# 	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>

# 	# BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR> --config Release --target INSTALL
# )
# message(" - External project done")

# include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
# link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# AWS SDK
set(AWSSDK_DIR /usr/local/lib/cmake/AWSSDK)

message("- Finding AWSSDK")
find_package(AWSSDK CONFIG COMPONENTS core dynamodb s3 REQUIRED)
message("- Done finding AWSSDK ")

# set(CURL_DIR /usr/bin/curl)
find_package( CURL REQUIRED )


# boost should be /usr/lib/x86_64-linux-gnu/cmake/Boost-1.71.0
# set(Boost_USE_STATIC_LIBS        ON)
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME    OFF)
# BOOST
# set(Boost_DIR "/usr/lib/x86_64-linux-gnu/cmake/Boost-1.71.0")
find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework )






# Testing
enable_testing()
add_subdirectory(tests)

message("-- Curl libraries " ${CURL_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LINK_LIBRARIES})
message("-- Boost libraries: " ${Boost_LIBRARIES})

message("-- Boost include dir " ${Boost_INCLUDE_DIR})

message("- include dir ")

# Handling vcpkg includes

# Must handle TRIPLET, depending on platform, like x64-linux or x64-windows

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
        ${VCPKG_LOCATION}/installed/${TRIPLET}/include
        ${Boost_INCLUDE_DIRS}
        
        # /home/nick/local/yaml-cpp/include 
        # /home/nick/IRIS-HEP/ryaml/install/include
        # /home/nick/IRIS-HEP/vcpkg/packages/jsoncpp_x64-linux/include
        # ${CURL_INCLUDE_DIRS}
        )


###########



# Generate dictionary
root_generate_dictionary(G__XDataFrameLib include/XDataFrame.h LINKDEF include/XDataFrameLinkDef.h)

add_library(XDataFrameLib SHARED 
                                src/XDataFrame.cpp 
                                include/XDataFrame.h 
                                G__XDataFrameLib.cxx
                                src/Hasher.cpp
                                src/MCache.cpp
                                src/RDataFrameHandler.cpp
                                src/Request.cpp
                                src/ServiceXHandler.cpp
                                include/Hasher.h
                                include/MCache.h
                                include/RDataFrameHandler.h
                                include/Request.h
                                include/ServiceXHandler.h
                               
)
target_include_directories(XDataFrameLib PUBLIC ${ROOT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include 
                                                ${VCPKG_LOCATION}/installed/${TRIPLET}/include
)

# target_link_libraries(XDataFrameLib boost_system)

target_link_libraries(XDataFrameLib PUBLIC ROOT::Core
                                        ROOT::RIO
                                        ROOT::Net
                                        ROOT::Hist 
                                        ROOT::Tree 
                                        ROOT::Thread 
                                        ROOT::MultiProc
                                        ROOT::ROOTDataFrame
                                        ROOT::Gpad
                                        ROOT::Rint
                                        CURL::libcurl
                                        OpenSSL::Crypto
                                        ${Boost_LIBRARIES}

)

target_link_libraries(XDataFrameLib PRIVATE jsoncpp_object jsoncpp_static
                                        aws-cpp-sdk-dynamodb
                                        aws-cpp-sdk-s3
                                        aws-cpp-sdk-core
                                        ryml::ryml
                                        ${CURL_LINK_LIBRARIES}
                                        
                                                                           
)




#############
# Executable part

add_executable(Demo demo/demo.cxx)

target_link_libraries(Demo PUBLIC XDataFrameLib)

# Setting the application directories, like bin and lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add compile flags
SET(GCC_COVERAGE_COMPILE_FLAGS "-DBOOST_NO_CXX11_SCOPED_ENUMS")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Installation


# add_test(testname Exename arg1 arg2 ...)
# add_test(NAME <name> [CONFIGURATIONS [Debug|Release|...]]
#          [WORKING_DIRECTORY dir]
#          COMMAND <command> [arg1 [arg2 ...]])

# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
#     include(CTest)
# endif()

