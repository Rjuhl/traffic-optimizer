set(THIS traffictests)
set(
    Sources
    basictest.cpp
    astartest.cpp
    roadtest.cpp
    vehicletest.cpp
    intersectiontest.cpp
    helpers.cpp
    helpers.h
    testClasses/simpleAcyclicGraph.cpp
    testClasses/simpleAcyclicGraph.h
    testClasses/simpleCyclicGraph.cpp
    testClasses/simpleCyclicGraph.h    
)

add_executable(${THIS} ${Sources})
target_link_libraries(
    ${THIS} 
    PRIVATE 
    gtest 
    gtest_main
    model
)

target_include_directories(
    ${THIS} 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/__tests__
    ${CMAKE_SOURCE_DIR}/__tests__/testClasses
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/model/external
    ${CMAKE_SOURCE_DIR}/model/enums
    ${CMAKE_SOURCE_DIR}/model/model
    ${CMAKE_SOURCE_DIR}/model/utils
)

include(GoogleTest)
gtest_discover_tests(${THIS})
