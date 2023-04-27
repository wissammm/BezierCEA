

project(basic_test)

################################
# GTest
################################

enable_testing()
include_directories(../src/${CMAKE_CURRENT_LIST_DIR} ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests testRayIntersection.cpp )
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main Bezier Geometry)
add_test( runUnitTests runUnitTests )