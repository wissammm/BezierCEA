cmake_minimum_required(VERSION 3.0.0)

# -----------------------
# Geometry
# -----------------------

add_library(Geometry 
            Geometry/Coord.h Geometry/Coord.cpp 
            Geometry/Segment.h Geometry/Segment.cpp)

# -----------------------
# Bezier
# -----------------------

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(Bezier 
            Bezier/Bezier.h Bezier/Bezier.cpp
            Bezier/BezierDecompose.h Bezier/BezierDecompose.cpp
            Bezier/BezierNormal.h Bezier/BezierNormal.cpp
            Bezier/BezierDerivate.h Bezier/BezierDerivate.cpp
            Bezier/BezierElevate.h Bezier/BezierElevate.cpp
            Bezier/BezierEvaluate.h Bezier/BezierEvaluate.cpp
            Bezier/BezierRayIntersection.h Bezier/BezierRayIntersection.cpp)

target_link_libraries (Bezier PUBLIC Geometry Eigen3::Eigen)
target_include_directories(Bezier PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 

# -----------------------
# View
# -----------------------

include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_library(View View/View.h View/View.cpp
                 View/Cli.h View/Cli.cpp
                 View/CircleDraw.h View/CircleDraw.cpp
                 View/CurveDraw.h View/CurveDraw.cpp
                 View/SegmentDraw.h View/SegmentDraw.cpp
                 View/Color.h View/Color.cpp
            )
target_link_libraries (View PUBLIC Bezier ${SDL2_LIBRARIES} SDL2_gfx)
target_include_directories(View PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 

# -----------------------
# IO
# -----------------------

add_library(Dump IO/Dump.h IO/Dump.cpp)
target_link_libraries (Dump PUBLIC Bezier)
target_include_directories(Bezier PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 

# -----------------------
# Exec
# -----------------------

add_executable(BezierMain BezierMain.cpp)
target_compile_definitions(BezierMain PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}../result\"")
target_link_libraries (BezierMain PRIVATE Bezier Dump)
target_include_directories(BezierMain PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 

add_executable(BezierView BezierView.cpp)
target_compile_definitions(BezierView PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}../result\"")
target_link_libraries (BezierView PRIVATE Bezier Dump View )
target_include_directories(BezierView PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 
