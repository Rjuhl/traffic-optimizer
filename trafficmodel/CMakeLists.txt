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
add_subdirectory(model)
add_subdirectory(modelGUI)
add_subdirectory(__tests__)

add_executable(traffic_model src/main.cpp)
target_link_libraries(traffic_model PRIVATE model modelGUI)

target_include_directories(
    traffic_model
    PUBLIC
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/model/external
    ${CMAKE_SOURCE_DIR}/model/enums
    ${CMAKE_SOURCE_DIR}/model/components
    ${CMAKE_SOURCE_DIR}/model/utils
    ${CMAKE_SOURCE_DIR}/modelGUI
)