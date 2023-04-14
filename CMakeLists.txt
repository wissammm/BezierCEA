cmake_minimum_required(VERSION 3.0.0)

project(Bezier VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(Coord Coord.h Coord.cpp)

add_library(Color Color.h Color.cpp)

add_library(Cli Cli.h Cli.cpp)

add_library(Bezier Bezier.h Bezier.cpp)
target_link_libraries (Bezier PUBLIC Coord Eigen3::Eigen Color)

add_library(Dump Dump.h Dump.cpp)
target_link_libraries (Dump PUBLIC Bezier)


target_link_libraries (Cli PUBLIC Bezier)

find_package(SDL2 REQUIRED)
# find_package(SDL2_gfx REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_gfx REQUIRED)


add_library(View View.h View.cpp)
target_link_libraries (View PUBLIC Bezier ${SDL2_LIBRARIES})

add_executable(BezierMain BezierMain.cpp)
target_compile_definitions(BezierMain PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}/result\"")
target_link_libraries (BezierMain PRIVATE Bezier Dump)

add_executable(BezierView BezierView.cpp)
target_compile_definitions(BezierView PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}/result\"")
target_link_libraries (BezierView PRIVATE Bezier Dump View )
