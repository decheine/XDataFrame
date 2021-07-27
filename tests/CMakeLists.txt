message("-- Tests CMakeLists.txt")

include(/home/nick/IRIS-HEP/vcpkg/scripts/buildsystems/vcpkg.cmake)

# find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${TEST_SOURCE_DIR}/src
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test basicTest.cpp)

message("linking test boost libraries")
target_link_libraries ( Test
                            # Boost::system
                            # Boost::filesystem
                            # Boost::unit_test_framework
                       )


add_test(NAME MyTest COMMAND Test)

message("CMake Tests")
