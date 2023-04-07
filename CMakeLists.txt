cmake_minimum_required(VERSION 3.0.0)

project(Bezier VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_executable(Bezier main.cpp Coord.h Coord.cpp View.h View.cpp)
target_compile_definitions(Bezier PRIVATE "RESULT_DIR=\"${CMAKE_CURRENT_LIST_DIR}/result\"")

target_include_directories(${PROJECT_NAME} PRIVATE include)

# target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
# target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(Bezier ${SDL2_LIBRARIES})
