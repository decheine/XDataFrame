cmake_minimum_required(VERSION 3.10)

project(XDataFrame VERSION 1.0)

add_executable(XDataFrame xdataframe.cxx)

configure_file(XDataFrameConfig.h.in XDataFrameConfig.h)

target_include_directories(XDataFrame PUBLIC "${PROJECT_BINARY_DIR}")   

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)