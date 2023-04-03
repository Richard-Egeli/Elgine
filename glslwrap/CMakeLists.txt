cmake_minimum_required(VERSION 3.20)

project(GLSL_WRAPPER)

# add_library(GLSL_WRAP STATIC)
#
# add_subdirectory(include/glslwrap)
# add_subdirectory(src)

# target_include_directories(GLSL_WRAP PUBLIC include)

add_executable(GLSL_TEST main.cpp include/glslwrap/definitions.hpp)
#
# target_link_libraries(GLSL_TEST)
