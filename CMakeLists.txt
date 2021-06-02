cmake_minimum_required(VERSION 3.10)

project(XDataFrame VERSION 1.0)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Locate the ROOT package and include the components the project needs
# MultiProc     ROOT's multi-threading framework
# root-config --libs => -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps 
#                       -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore 
#                       -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Generate dictionaries for ROOT
# ROOT_GENERATE_DICTIONARY(G__XDataFrame XDataFrame.h LINKDEF XDataFrameLinkDef.h)



# Adding project subdirectories for different functional parts/modules
# RDataFrame
add_subdirectory(RDataFrameHandler)
# ServiceX TODO: create the CMakeLists and such for that module
# add_subdirectory(ServiceXHandler)



# Adding local libraries ?
# add_library(RDataFrameHandler G__RDataFrameHandler)



# Executable
add_executable(XDataFrame exe/XDataFrame.cxx)


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
)

configure_file(include/XDataFrameConfig.h.in include/XDataFrameConfig.h)

target_include_directories(XDataFrame PUBLIC "${PROJECT_BINARY_DIR}")   

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Installation


