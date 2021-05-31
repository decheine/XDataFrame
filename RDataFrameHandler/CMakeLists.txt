cmake_minimum_required(VERSION 3.4...3.20)

project(RDataFrameHandler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

find_package(ROOT 6.20 CONFIG REQUIRED)
# If you want to support <6.20, add this line:
# include("${ROOT_DIR}/modules/RootNewMacros.cmake")
# However, it was moved and included by default in 6.201

root_generate_dictionary(G__RDataFrameHandler RDataFrameHandler.h LINKDEF DictLinkDef.h)

add_library(RDataFrameHandler SHARED RDataFrameHandler.cxx RDataFrameHandler.h G__RDataFrameHandler.cxx)
target_include_directories(RDataFrameHandler PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(RDataFrameHandler PUBLIC ROOT::Core ROOT::Tree ROOT::Physics)

## Alternative to add the dictionary to an existing target:
# add_library(RDataFrameHandler SHARED RDataFrameHandler.cxx RDataFrameHandler.h)
# target_include_directories(RDataFrameHandler PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# target_link_libraries(RDataFrameHandler PUBLIC ROOT::Core)
# root_generate_dictionary(G__RDataFrameHandler RDataFrameHandler.h MODULE RDataFrameHandler LINKDEF DictLinkDef.h)