cmake_minimum_required(VERSION 3.10)
project(LagrangePolynomial)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DFREEGLUT_STATIC)

include_directories(include third_party/freeglut/include)

link_directories(third_party/freeglut/lib)

add_executable(LagrangePolynomial main.cpp LagrangePolynomial.cpp)

set_target_properties(LagrangePolynomial PROPERTIES LINK_FLAGS "-static" )

target_link_libraries(LagrangePolynomial freeglut_static opengl32 glu32 winmm gdi32)