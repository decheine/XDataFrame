cmake_minimum_required(VERSION 3.10)

project(XDataFrame VERSION 1.0)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_TOOLCHAIN_FILE /home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)

# set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)


# set(BUILD_SHARED_LIBS OFF)
# Locate the ROOT package and include the components the project needs
# MultiProc     ROOT's multi-threading framework
# root-config --libs => -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps 
#                       -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore 
#                       -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

# Set the /lib and /bin directories to be used by the program
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



# set(CMAKE_TOOLCHAIN_FILE /home/nick/IRIS-HEP/vcpkg/scripts/buildsystems vcpkg.cmake)

find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint )

# instruct cmake to search for ryml
set(ryml_DIR /home/nick/IRIS-HEP/ryaml/install/lib/cmake/ryml )
find_package(ryml REQUIRED)

set(jsoncpp_DIR ~/IRIS-HEP/vcpkg/packages/jsoncpp_x64-linux/share/jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

# AWS SDK
# set(CMAKE_PREFIX_PATH ~/IRIS-HEP/vcpkg/packages/curl_x64-linux/share/curl)
set(LD_LIBRARY_PATH /usr/local/lib)
set(AWSSDK_DIR ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/AWSSDK)
set(aws-cpp-sdk-core_DIR ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-core)
set(aws-cpp-sdk-s3_DIR  ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-s3)
set(aws-cpp-sdk-kinesis_DIR  ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-kinesis)
set(aws-cpp-sdk-dynamodb_DIR  ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-dynamodb)
set(aws-c-event-stream_DIR ~/IRIS-HEP/vcpkg/packages/aws-c-event-stream_x64-linux/share/aws-c-event-stream/)
set(aws-checksums_DIR ~/IRIS-HEP/vcpkg/packages/aws-checksums_x64-linux/share/aws-checksums/)
set(aws-c-common_DIR ~/IRIS-HEP/vcpkg/packages/aws-c-common_x64-linux/share/aws-c-common/)
find_package(AWSSDK CONFIG COMPONENTS core dynamodb s3 REQUIRED)

set(CURL_DIR ~/IRIS-HEP/vcpkg/packages/curl_x64-linux/share/curl)
find_package( CURL CONFIG REQUIRED)

# Amazon AWS SDK External Project
# include(ExternalProject)

# ExternalProject_Add(aws-sdk-cpp
#     GIT_REPOSITORY    https://github.com/aws/aws-sdk-cpp.git
#     GIT_TAG           origin/master
#     CMAKE_ARGS        
#     BUILD_ALWAYS      TRUE
#     TEST_COMMAND      ""
# )



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include /home/nick/local/yaml-cpp/include 
        ${CURL_INCLUDE_DIRS}
        )

# Generate dictionaries for ROOT
# ROOT_GENERATE_DICTIONARY(G__XDataFrame XDataFrame.h LINKDEF XDataFrameLinkDef.h)



# Adding project subdirectories for different functional parts/modules
# RDataFrame
# add_subdirectory(RDataFrameHandler)

# ServiceX
# add_subdirectory(ServiceXHandler)

# Using Rapid YAML project for yaml parsing

# Adding local libraries ?
# add_library(RDataFrameHandler G__RDataFrameHandler)

file(GLOB SOURCES src/*.cpp)

# Executable
add_executable(XDataFrame exe/XDataFrame.cxx ${SOURCES})

message("-- Curl libraries " ${CURL_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LINK_LIBRARIES})

target_link_directories(XDataFrame PUBLIC /usr/lib/x86_64-linux-gnu/curl BEFORE)

# Linking Libraries
target_link_libraries(XDataFrame PUBLIC ROOT::Core
                                        ROOT::RIO
                                        ROOT::Net
                                        ROOT::Hist 
                                        ROOT::Tree 
                                        ROOT::Thread 
                                        ROOT::MultiProc
                                        ROOT::ROOTDataFrame
                                        ROOT::Gpad
                                        ROOT::Rint
                                        ryml::ryml
                                        CURL::libcurl
                                        OpenSSL::Crypto
                                        ${AWSSDK_LINK_LIBRARIES}


)

target_link_libraries(XDataFrame PRIVATE jsoncpp_object jsoncpp_static
                                        # ${ARROW_LIBS}
                                        aws-cpp-sdk-dynamodb
                                        aws-cpp-sdk-s3
                                        aws-cpp-sdk-core
                                        ${CURL_LINK_LIBRARIES}
                                        
                                        )

configure_file(include/XDataFrameConfig.h.in include/XDataFrameConfig.h)

target_include_directories(XDataFrame PUBLIC "${PROJECT_BINARY_DIR}" )   
target_include_directories(XDataFrame PRIVATE ${AWSSDK_INCLUDE_DIRS})   

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Installation


