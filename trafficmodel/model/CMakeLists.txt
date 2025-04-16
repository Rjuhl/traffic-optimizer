set(THIS model)

file(GLOB_RECURSE SOURCES "./**/*.cpp" "./**/*.h" "./*.cpp" "./*.h")

add_library(
    ${THIS}
    ${SOURCES}
)

target_include_directories(
    ${THIS}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/model/enums
    ${CMAKE_SOURCE_DIR}/model/components
    ${CMAKE_SOURCE_DIR}/model/components/dataSchema
    ${CMAKE_SOURCE_DIR}/model/components/interfaces
    ${CMAKE_SOURCE_DIR}/model/components/defaults
    ${CMAKE_SOURCE_DIR}/model/utils
)


