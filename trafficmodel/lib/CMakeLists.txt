set(THIS trafficlib)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "./**/*.cpp" "./**/*.h" "./*.cpp" "./*.h")

add_library(
    ${THIS}
    glad.c
    ${SOURCES}
)

target_include_directories(
    ${THIS}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/external
    ${CMAKE_SOURCE_DIR}/lib/enums
    ${CMAKE_SOURCE_DIR}/lib/model
    ${CMAKE_SOURCE_DIR}/lib/utils
    ${CMAKE_SOURCE_DIR}/lib/view
)

target_link_libraries(
    ${THIS}
    PUBLIC
    glfw 
    glm::glm 
    OpenGL::GL
)

