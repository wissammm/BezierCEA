

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
add_executable( runUnitTestsRayIntersection testRayIntersection.cpp  )

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTestsRayIntersection GTest::gtest GTest::gtest_main Bezier Geometry)
add_test( runUnitTestsRayIntersection runUnitTestsRayIntersection )

add_executable( runUnitTestsRootsHull testRootsAndHull.cpp  )