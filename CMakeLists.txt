cmake_minimum_required(VERSION 3.16)

project(XDataFrame VERSION 1.0)

include(GNUInstallDirs)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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

# JSONCPP
FetchContent_Declare(jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG master     # or a particular branch, tag or commit
    GIT_SHALLOW FALSE  # ensure submodules are checked out
)
FetchContent_MakeAvailable(jsoncpp)

find_package(OpenSSL REQUIRED)
find_package( CURL REQUIRED )

set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")


message("- Fetching aws-sdk-cpp. This could take a few minutes...")

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

target_include_directories(XDataFrameLib PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

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
                                        jsoncpp_object jsoncpp_static
                                        aws-cpp-sdk-s3
                                        aws-cpp-sdk-core
                                        ryml
                                        ${CURL_LINK_LIBRARIES}     

)

# target_link_libraries(XDataFrameLib PRIVATE jsoncpp_object jsoncpp_static
#                                         aws-cpp-sdk-s3
#                                         aws-cpp-sdk-core
#                                         ryml
#                                         ${CURL_LINK_LIBRARIES}                                              
# )


install(
    TARGETS XDataFrameLib
    EXPORT XDataFrameLibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install( FILES  include/XDataFrame.h
                include/Hasher.h
                include/MCache.h
                include/RDataFrameHandler.h
                include/Request.h
                include/ServiceXHandler.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#############
# Executable

add_subdirectory(demo)

# Add compile flags
SET(GCC_COVERAGE_COMPILE_FLAGS "-DBOOST_NO_CXX11_SCOPED_ENUMS")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Installation

message("-- configuring installation")

install(
    EXPORT XDataFrameLibTargets
    FILE XDataFrameLibTargets.cmake # maybe not needed
    NAMESPACE XDataFrame::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XDataFrame
    
)

# include(CMakePackageConfigHelpers)
# configure_package_config_file(
#     "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/XDataFrameConfig.cmake"
#     INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XDataFrame
#     PATH_VARS
#         CMAKE_INSTALL_LIBDIR
# )

# write_basic_package_version_file(
#     ${CMAKE_CURRENT_BINARY_DIR}/XDataFrameConfigVersion.cmake
#     VERSION 1.1.0
#     COMPATIBILITY SameMajorVersion
# )

# Install Config and ConfigVersion files
# install(
#     FILES   "${CMAKE_CURRENT_BINARY_DIR}/XDataFrameConfig.cmake"
#             # "${CMAKE_CURRENT_BINARY_DIR}/XDataFrameConfigVersion.cmake"
#     DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/XDataFrame"
# )

