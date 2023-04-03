cmake_minimum_required(VERSION 3.20)
project(Elgine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.1)

set(CMAKE_CXX_FLAGS "")

add_library(ElgineGame STATIC)

# add_subdirectory(shaders)
add_subdirectory(engine)
add_subdirectory(game)

target_link_libraries(ElgineGame ElgineEngine)

add_executable(Elgine main.cpp)

target_link_libraries(Elgine PUBLIC
    ElgineGame

    ${OPENGL_LIBRARIES} 
    ${SDL2_LIBRARIES}
    ElgineEngine
)

