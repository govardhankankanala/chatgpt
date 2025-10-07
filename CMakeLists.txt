cmake_minimum_required(VERSION 3.14)
project(dropcopy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(dropcopy
  src/dropcopy/parser.cpp
  src/dropcopy/config.cpp
)
target_include_directories(dropcopy PUBLIC include)

add_executable(dropcopy_demo src/main.cpp)
target_link_libraries(dropcopy_demo PRIVATE dropcopy)

enable_testing()
add_executable(test_parser tests/test_parser.cpp)
target_link_libraries(test_parser PRIVATE dropcopy)
add_test(NAME test_parser COMMAND test_parser)