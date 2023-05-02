

project(basic_test)

################################
# GTest
################################

enable_testing()
find_package(GTest REQUIRED)

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests testRayIntersection.cpp )
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests GTest::gtest GTest::gtest_main Bezier Geometry)
add_test( runUnitTests runUnitTests )