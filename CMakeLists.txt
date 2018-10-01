cmake_minimum_required(VERSION 3.10)
project(NewtonPolynomial)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DFREEGLUT_STATIC)

include_directories(include third_party/freeglut/include)

link_directories(third_party/freeglut/lib)

add_executable(NewtonPolynomial main.cpp)

set_target_properties(NewtonPolynomial PROPERTIES LINK_FLAGS "-static" )

target_link_libraries(NewtonPolynomial freeglut_static opengl32 glu32 winmm gdi32)