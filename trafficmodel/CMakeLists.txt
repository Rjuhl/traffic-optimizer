cmake_minimum_required(VERSION 3.15)
project(traffic_model VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)


add_executable(
    traffic_model 
    dependencies/config.h 
    src/main.cpp
    src/glad.c

)

target_include_directories(
    traffic_model 
    PRIVATE
    dependencies 
)

target_link_libraries(traffic_model glfw glm::glm OpenGL::GL)