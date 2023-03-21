cmake_minimum_required(VERSION 3.10)
project(Elgine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.1)

add_subdirectory(engine)

add_executable(Elgine main.cpp)

target_link_libraries(Elgine 
    ElgineEngine 
    ${OPENGL_LIBRARIES} 
    ${SDL2_LIBRARIES}
)

