cmake_minimum_required(VERSION 3.15)
project(traffic_model VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CTEST_OUTPUT_ON_FAILURE TRUE)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CXX Flags: ${CMAKE_CXX_FLAGS}")

enable_testing()

add_subdirectory(dependencies/googletest)
add_subdirectory(lib)
add_subdirectory(__tests__)

add_executable(traffic_model src/main.cpp)
target_link_libraries(traffic_model PRIVATE trafficlib)

target_include_directories(
    traffic_model
    PUBLIC
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/external
    ${CMAKE_SOURCE_DIR}/lib/enums
    ${CMAKE_SOURCE_DIR}/lib/model
    ${CMAKE_SOURCE_DIR}/lib/utils
    ${CMAKE_SOURCE_DIR}/lib/view
)