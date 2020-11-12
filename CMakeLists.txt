cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
        SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(crypto_messenger)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(crypto_messenger STATIC
        client/include/include.hpp
        client/sources/source.cpp)
add_executable(tests
        tests/test.cpp)
add_executable(crypto_messenger_server
        server/include/include.hpp
        server/sources/source.cpp)

target_include_directories(crypto_messenger PUBLIC client/include)
target_include_directories(crypto_messenger_server PUBLIC server/include)
target_include_directories(tests PUBLIC client/include)
target_link_libraries(tests GTest::main crypto_messenger)

enable_testing()
add_test(NAME unit_tests COMMAND tests)