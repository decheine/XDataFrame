cmake_minimum_required(VERSION 3.10)

project(XDataFrame VERSION 1.0)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Locate the ROOT package and include the components the project needs
# MultiProc     ROOT's multi-threading framework
# root-config --libs => -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps 
#                       -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore 
#                       -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic


set(CMAKE_TOOLCHAIN_FILE /home/nick/IRIS-HEP/vcpkg/scripts/buildsystems vcpkg.cmake)

# Setting prefix path to look for package config files
set(ryml_DIR /home/nick/IRIS-HEP/ryaml/install/lib/cmake/ryml )

find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint )



# instruct cmake to search for ryml
find_package(ryml REQUIRED)

find_package( CURL REQUIRED)

set(jsoncpp_DIR ~/IRIS-HEP/vcpkg/packages/jsoncpp_x64-linux/share/jsoncpp)

find_package(jsoncpp CONFIG REQUIRED)

include(FindPkgConfig)

set(Brotli_DIR ~/IRIS-HEP/vcpkg/packages/brotli_x64-linux/share/unofficial-brotli)
# find_package(Brotli)

# Snappy, arrow dependency
# set(Snappy_LIB ~/IRIS-HEP/vcpkg/packages/snappy_x64-linux/include)
# set(Snappy_DIR ~/IRIS-HEP/vcpkg/packages/snappy_x64-linux/share/snappy)
# set(Snappy_INCLUDE_DIR ~/IRIS-HEP/vcpkg/packages/snappy_x64-linux/include)

# set(Arrow_DIR ~/IRIS-HEP/vcpkg/packages/arrow_x64-linux/share/arrow)
# set(arrow_DIR ~/IRIS-HEP/vcpkg/packages/arrow_x64-linux/share/arrow)

# find_package(Arrow CONFIG REQUIRED)

# set(ARROW_LIBS "LZ4::lz4 re2::re2 arrow_static zstd::libzstd")



# Amazon AWS SDK External Project
include(ExternalProject)

ExternalProject_Add(aws-sdk-cpp
    GIT_REPOSITORY    https://github.com/aws/aws-sdk-cpp.git
    GIT_TAG           <tag>
    CMAKE_ARGS        <CMake-options>
    BUILD_ALWAYS      TRUE
    TEST_COMMAND      ""
)



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include /home/nick/local/yaml-cpp/include 
        ${CURL_INCLUDE_DIRS})

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
                                        ${CURL_LIBRARIES}
                                        
)

target_link_libraries(XDataFrame PRIVATE jsoncpp_object jsoncpp_static
                                        # ${ARROW_LIBS}
                                        )

configure_file(include/XDataFrameConfig.h.in include/XDataFrameConfig.h)

target_include_directories(XDataFrame PUBLIC "${PROJECT_BINARY_DIR}")   

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Installation


