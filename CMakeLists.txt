cmake_minimum_required(VERSION 3.10)

project(XDataFrame VERSION 1.0)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Locate the ROOT package and include the components the project needs
# MultiProc     ROOT's multi-threading framework
find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame  )


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Generate dictionaries
# ROOT_GENERATE_DICTIONARY(G__Event Event.h LINKDEF EventLinkDef.h)











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
)

configure_file(include/XDataFrameConfig.h.in include/XDataFrameConfig.h)

target_include_directories(XDataFrame PUBLIC "${PROJECT_BINARY_DIR}")   

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Installation


