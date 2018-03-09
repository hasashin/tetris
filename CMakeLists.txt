cmake_minimum_required(VERSION 3.10)
project(tetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(tetris main.cpp loop.h objects.h)

set(GLOBAL_LIBRARIES "liballegro.dylib" "liballegro_main.dylib" "liballegro_font.dylib" "liballegro_ttf.dylib")

target_link_libraries(tetris ${GLOBAL_LIBRARIES})
