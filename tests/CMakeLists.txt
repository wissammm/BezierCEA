

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
add_executable( runTests testRayIntersection.cpp testRootsAndHull.cpp testGeometry.cpp )
target_link_libraries(runTests GTest::gtest GTest::gtest_main Bezier Geometry)
add_test( runTests runTests )