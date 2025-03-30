set(THIS traffictests)
set(
    Sources
    basictest.cpp
    astartest.cpp
    helpers.cpp
    helpers.h
)

add_executable(${THIS} ${Sources})
target_link_libraries(
    ${THIS} 
    PRIVATE 
    gtest 
    gtest_main
    trafficlib
)

target_include_directories(
    ${THIS} 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/__tests__
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/external
    ${CMAKE_SOURCE_DIR}/lib/enums
    ${CMAKE_SOURCE_DIR}/lib/model
    ${CMAKE_SOURCE_DIR}/lib/utils
    ${CMAKE_SOURCE_DIR}/lib/view
)

include(GoogleTest)
gtest_discover_tests(${THIS})
