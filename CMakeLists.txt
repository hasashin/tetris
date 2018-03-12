cmake_minimum_required(VERSION 3.10)
project(tetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(tetris main.cpp event.h controlObjects.h menu.h audio.h gameObjects.h)

set(GLOBAL_LIBRARIES "liballegro.dylib" "liballegro_main.dylib" "liballegro_font.dylib" "liballegro_ttf.dylib" "liballegro_audio.dylib" "liballegro_acodec.dylib")

target_link_libraries(tetris ${GLOBAL_LIBRARIES})
