cmake_minimum_required(VERSION 3.16)

project(XDataFrameProject VERSION 1.0)

# specify the C++ standard
# TODO: How much of this is specified by ROOT when building this library?
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Set your machines "triplet". On a 64 bit Windows machine, change to "x64-windows"
set(TRIPLET x64-linux)

# set(CMAKE_TOOLCHAIN_FILE /home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)
# include(/home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Locate packages

find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint )

find_package(Boost REQUIRED COMPONENTS system filesystem )



include(FetchContent)

# RYML
FetchContent_Declare(ryml
    GIT_REPOSITORY https://github.com/biojppm/rapidyaml.git
    GIT_TAG master     # or a particular branch, tag or commit
    GIT_SHALLOW FALSE  # ensure submodules are checked out
)
FetchContent_MakeAvailable(ryml)

# set(ryml_DIR ~/IRIS-HEP/vcpkg/packages/ryml_x64-linux/share/ryml)
# find_package(ryml CONFIG REQUIRED)

# JSONCPP
FetchContent_Declare(jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG master     # or a particular branch, tag or commit
    GIT_SHALLOW FALSE  # ensure submodules are checked out
)
FetchContent_MakeAvailable(jsoncpp)

# set(jsoncpp_DIR ~/IRIS-HEP/vcpkg/packages/jsoncpp_x64-linux/share/jsoncpp)
# find_package(jsoncpp CONFIG REQUIRED)

find_package(OpenSSL REQUIRED)

find_package( CURL REQUIRED )

set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")


message("- Fetching aws-sdk-cpp")

FetchContent_Declare(aws-sdk-cpp
        GIT_REPOSITORY  https://github.com/aws/aws-sdk-cpp
        GIT_SHALLOW     FALSE
)

set(BUILD_ONLY "s3")

FetchContent_MakeAvailable(aws-sdk-cpp)

message("- Done fetching AWSSDK ")



# Testing
enable_testing()
add_subdirectory(tests)

message("-- Curl include " ${CURL_LINK_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LINK_LIBRARIES})
message("-- Boost libraries: " ${Boost_LIBRARIES})

message("-- Boost include dir " ${Boost_INCLUDE_DIR})

message("- include dir ")

# Handling vcpkg includes

# Must handle TRIPLET, depending on platform, like x64-linux or x64-windows

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
        # ${VCPKG_LOCATION}/installed/${TRIPLET}/include
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
                                                # ${VCPKG_LOCATION}/installed/${TRIPLET}/include
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
                                        ryml
                                        ${CURL_LINK_LIBRARIES}                                              
)


#############
# Executable

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

