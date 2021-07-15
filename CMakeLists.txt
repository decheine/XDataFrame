cmake_minimum_required(VERSION 3.16)

project(XDataFrameProject VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# CMake helper module from git
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# set(CMAKE_TOOLCHAIN_FILE /home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Locate the ROOT package and include the components the project needs
# MultiProc     ROOT's multi-threading framework
# root-config --libs => -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps 
#                       -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore 
#                       -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint )

# instruct cmake to search for ryml
set(ryml_DIR /home/nick/IRIS-HEP/ryaml/install/lib/cmake/ryml )
find_package(ryml REQUIRED)

set(jsoncpp_DIR ~/IRIS-HEP/vcpkg/packages/jsoncpp_x64-linux/share/jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

# AWS SDK
# set(CMAKE_PREFIX_PATH ~/IRIS-HEP/vcpkg/packages/curl_x64-linux/share/curl)
# set(LD_LIBRARY_PATH /usr/local/lib)
set(AWSSDK_DIR ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/AWSSDK)
set(aws-cpp-sdk-core_DIR ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-core)
set(aws-cpp-sdk-s3_DIR  ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-s3)
set(aws-cpp-sdk-kinesis_DIR  ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-kinesis)
set(aws-cpp-sdk-dynamodb_DIR  ~/IRIS-HEP/vcpkg/packages/aws-sdk-cpp_x64-linux/share/aws-cpp-sdk-dynamodb)
set(aws-c-event-stream_DIR ~/IRIS-HEP/vcpkg/packages/aws-c-event-stream_x64-linux/share/aws-c-event-stream/)
set(aws-checksums_DIR ~/IRIS-HEP/vcpkg/packages/aws-checksums_x64-linux/share/aws-checksums/)
set(aws-c-common_DIR ~/IRIS-HEP/vcpkg/packages/aws-c-common_x64-linux/share/aws-c-common/)
find_package(AWSSDK CONFIG COMPONENTS core dynamodb s3 REQUIRED)

# set(CURL_DIR /usr/bin/curl)
find_package( CURL REQUIRED)


# BOOST
find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework )

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
        ${Boost_INCLUDE_DIR}
        )


# Testing
enable_testing()
add_subdirectory(tests)

message("-- Curl libraries " ${CURL_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LIBRARIES})
message("-- AWSSDK libraries " ${AWSSDK_LINK_LIBRARIES})
message("-- Boost include dir " ${Boost_INCLUDE_DIR})

# Test, basic lib
add_library(Math SHARED src/MathLibrary.cpp include/MathLibrary.h)



# target_link_directories(XDataFrame PUBLIC /usr/lib/x86_64-linux-gnu/curl BEFORE)

# Online there this is the jank solution to the "relocation R_X86_64_PC32 ... shared object; recompile with -fPIC"
# Doesn't work here, causes more issues.
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fPIC")

# root_generate_dictionary(G__XDataFrameLib include/XDataFrame.h LINKDEF include/XDataFrameLinkDef.h)

# add_library(XDataFrameLib SHARED src/XDataFrame.cxx include/XDataFrame.h G__XDataFrame.cxx)
# target_include_directories(XDataFrameLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# target_link_libraries(XDataFrameLib PUBLIC ROOT::Core
#                                         ROOT::RIO
#                                         ROOT::Net
#                                         ROOT::Hist 
#                                         ROOT::Tree 
#                                         ROOT::Thread 
#                                         ROOT::MultiProc
#                                         ROOT::ROOTDataFrame
#                                         ROOT::Gpad
#                                         ROOT::Rint
#                                         ryml::ryml
#                                         CURL::libcurl
#                                         OpenSSL::Crypto
#                                         # ${AWSSDK_LINK_LIBRARIES}
#                                         Math
#                                         ${Boost_LIBRARIES}
# )

# target_link_libraries(XDataFrameLib PRIVATE jsoncpp_object jsoncpp_static
#                                         aws-cpp-sdk-dynamodb
#                                         aws-cpp-sdk-s3
#                                         aws-cpp-sdk-core
#                                         ${CURL_LINK_LIBRARIES}
                                        
#                                         )


# add_library(XDataFrameLib SHARED
#         src/Hasher.cpp
#         src/MCache.cpp
#         src/MathLibrary.cpp
#         src/RDataFrameHandler.cpp
#         src/Request.cpp
#         src/ServiceXHandler.cpp
#         src/User.cpp
#         include/Hasher.h
#         include/MCache.h
#         include/MathLibrary.h
#         include/RDataFrameHandler.h
#         include/Request.h
#         include/ServiceXHandler.h
#         include/User.h
#         include/XDataFrame.h
# )


# target_link_libraries(XDataFrameLib PUBLIC 
#                                 ryml::ryml
#                                 ROOT::Core
#                                 ROOT::RIO
#                                 ROOT::Net
#                                 ROOT::Hist 
#                                 ROOT::Tree 
#                                 ROOT::Thread 
#                                 ROOT::MultiProc
#                                 ROOT::ROOTDataFrame
#                                 ROOT::Gpad
#                                 ROOT::Rint
#                                 CURL::libcurl
#                                 OpenSSL::Crypto
#                                 Math
#                                 ${Boost_LIBRARIES}

# )

# target_link_libraries(XDataFrameLib PRIVATE jsoncpp_object jsoncpp_static
#                                         aws-cpp-sdk-dynamodb
#                                         aws-cpp-sdk-s3
#                                         aws-cpp-sdk-core
#                                         ${CURL_LINK_LIBRARIES}
# )

# Executable part


file(GLOB SOURCES src/*.cpp)
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
                                        CURL::libcurl
                                        OpenSSL::Crypto
                                        # ${AWSSDK_LINK_LIBRARIES}
                                        Math
                                        ${Boost_LIBRARIES}
)

target_link_libraries(XDataFrame PRIVATE jsoncpp_object jsoncpp_static
                                        aws-cpp-sdk-dynamodb
                                        aws-cpp-sdk-s3
                                        aws-cpp-sdk-core
                                        ${CURL_LINK_LIBRARIES}
                                        
                                        )


# add_subdirectory(demo)
add_executable(Demo demo/demo.cxx)


configure_file(include/XDataFrameConfig.h.in include/XDataFrameConfig.h)

target_include_directories(XDataFrame PUBLIC "${PROJECT_BINARY_DIR}" )   
target_include_directories(XDataFrame PRIVATE ${AWSSDK_INCLUDE_DIRS})   

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

