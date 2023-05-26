# -----------------------
# Geometry
# -----------------------

add_library(Geometry 
            Geometry/Coord.h Geometry/Coord.cpp 
            Geometry/Segment.h Geometry/Segment.cpp
            Geometry/Newton.h
            Geometry/Doublons.h)
target_include_directories(Geometry PUBLIC ${CMAKE_CURRENT_LIST_DIR})

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
            Bezier/PointOnCurve.h Bezier/PointOnCurve.cpp
            Bezier/BezierRayIntersection.h Bezier/BezierRayIntersection.cpp
            Bezier/BezierCurveCurveIntersection.h Bezier/BezierCurveCurveIntersection.cpp
            Bezier/BoundingBox.h Bezier/BoundingBox.cpp)

target_include_directories(Bezier PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 
target_link_libraries (Bezier PUBLIC Geometry Eigen3::Eigen)
# target_link_libraries (Bezier PUBLIC Geometry )

# -----------------------
# View
# # -----------------------
# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# find_package(SDL2 REQUIRED)
# find_package(SDL2_gfx REQUIRED)

# add_library(View View/View.h View/View.cpp
#                  View/Cli.h View/Cli.cpp
#                  View/CircleDraw.h View/CircleDraw.cpp
#                  View/CurveDraw.h View/CurveDraw.cpp
#                  View/SegmentDraw.h View/SegmentDraw.cpp
#                  View/Color.h View/Color.cpp
#             )
# target_include_directories(View PUBLIC ${SDL2_INCLUDE_DIRS}) 

# target_link_libraries (View PUBLIC Bezier ${SDL2_LIBRARIES} SDL2_gfx)
# target_include_directories(View PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# -----------------------
# IO
# -----------------------

add_library(Dump IO/Dump.h IO/Dump.cpp)
target_include_directories(Dump PUBLIC ${CMAKE_CURRENT_LIST_DIR}) 
target_link_libraries (Dump PUBLIC Geometry)

# -----------------------
# Exec
# -----------------------

add_executable(BezierMain BezierMain.cpp)
target_compile_definitions(BezierMain PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}../result\"")
target_link_libraries (BezierMain PUBLIC Bezier Dump)

# add_executable(BezierView BezierView.cpp)
# target_compile_definitions(BezierView PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}../result\"")
# target_link_libraries (BezierView PRIVATE Bezier Dump View )
