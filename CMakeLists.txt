cmake_minimum_required(VERSION 3.10)

# name 
project(GLDemo)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/usr/local/include)
include_directories(frameworks/glm)

link_directories(/usr/local/lib)

find_package(OpenGL REQUIRED)

add_executable(BenchmarkTest src/benchmark_test.cpp)
target_link_libraries(BenchmarkTest glew glfw benchmark OpenGL::GL)

add_executable(sdl2_tetris src/tetris/debug_vis.cpp
    src/tetris/state.cpp
    src/tetris/figures.cpp
    src/tetris/utils.cpp)
target_link_libraries(sdl2_tetris glew glfw benchmark OpenGL::GL SDL2)
