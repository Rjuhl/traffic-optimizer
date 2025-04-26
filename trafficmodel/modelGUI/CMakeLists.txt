set(THIS modelGUI)

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
    ${CMAKE_SOURCE_DIR}/modelGUI
    ${CMAKE_SOURCE_DIR}/modelGUI/utils
    ${CMAKE_SOURCE_DIR}/modelGUI/external
    ${CMAKE_SOURCE_DIR}/modelGUI/components
    ${CMAKE_SOURCE_DIR}/modelGUI/constants
    ${CMAKE_SOURCE_DIR}/modelGUI/controller
    ${CMAKE_SOURCE_DIR}/modelGUI/factories
    ${CMAKE_SOURCE_DIR}/modelGUI/factories/shapes
    ${CMAKE_SOURCE_DIR}/modelGUI/shaders
    ${CMAKE_SOURCE_DIR}/modelGUI/system
)

target_link_libraries(
    ${THIS}
    PUBLIC
    glfw 
    glm::glm 
    OpenGL::GL
    model
)

