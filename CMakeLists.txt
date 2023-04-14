cmake_minimum_required(VERSION 3.0.0)

project(Bezier VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(Coord src/Coord.h src/Coord.cpp)

add_library(Color src/Color.h src/Color.cpp)

add_library(Cli src/Cli.h src/Cli.cpp)

add_library(Bezier src/Bezier.h src/Bezier.cpp)
target_link_libraries (Bezier PUBLIC Coord Eigen3::Eigen Color)

add_library(Dump src/Dump.h src/Dump.cpp)
target_link_libraries (Dump PUBLIC Bezier)


target_link_libraries (Cli PUBLIC Bezier)

find_package(SDL2 REQUIRED)
# find_package(SDL2_gfx REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_gfx REQUIRED)


add_library(View src/View.h src/View.cpp)
target_link_libraries (View PUBLIC Bezier ${SDL2_LIBRARIES})

add_executable(BezierMain BezierMain.cpp)
target_compile_definitions(BezierMain PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}/result\"")
target_link_libraries (BezierMain PRIVATE Bezier Dump)

add_executable(BezierView BezierView.cpp)
target_compile_definitions(BezierView PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}/result\"")
target_link_libraries (BezierView PRIVATE Bezier Dump View )
