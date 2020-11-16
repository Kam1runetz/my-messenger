cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
        SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(messenger)
string(APPEND CMAKE_CXX_FLAGS "-lpthread -pedantic -Wall -Wextra")

hunter_add_package(GTest)
hunter_add_package(Boost COMPONENTS system log)

find_package(GTest CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED system log)

add_library(messenger_client STATIC
        common/myprotocol.hpp
        common/myprotocoldefs.hpp
        client/include/Client.hpp
        client/sources/Client.cpp)

add_library(messenger_server STATIC
        common/myprotocol.hpp
        common/myprotocoldefs.hpp
        server/ConnectionServer/include/Server.hpp
        server/ConnectionServer/sources/Server.cpp
        server/RequestHandling/include/IRequestHandler.hpp
        server/RequestHandling/include/PlainRequestHandler.hpp
        server/RequestHandling/sources/PlainRequestHandler.cpp
        server/ConnectionServer/include/Connection.hpp
        server/ConnectionServer/sources/Connection.cpp
        server/ConnectionServer/include/ConnectionManager.hpp
        server/ConnectionServer/sources/ConnectionManager.cpp
        )

add_executable(tests
        tests/test.cpp)


target_include_directories(messenger_client PUBLIC client/include ${Boost_INCLUDE_DIRS} common)
target_include_directories(messenger_server PUBLIC server/ConnectionServer/include
        server/RequestHandling/include ${Boost_INCLUDE_DIRS} common)

target_include_directories(tests PUBLIC
        server/ConnectionServer/include
        server/RequestHandling/include
        client/include
        common/)

target_link_libraries(messenger_server ${Boost_LIBRARIES})
target_link_libraries(tests GTest::main messenger_server messenger_client)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if (BUILD_COVERAGE)
    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    find_package(codecov)
    add_coverage(messenger_server)
    add_coverage(messenger_client)
    add_coverage(tests)
    list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
    coverage_evaluate()
endif ()
