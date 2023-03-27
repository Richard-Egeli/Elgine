cmake_minimum_required(VERSION 3.20)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.1)

add_library(ElgineEngine STATIC)

target_sources(ElgineEngine PRIVATE elgine.cpp)

add_subdirectory(utils)
add_subdirectory(ecs)
add_subdirectory(components)
add_subdirectory(entities)
add_subdirectory(types)
add_subdirectory(systems)
add_subdirectory(lib)


target_include_directories(ElgineEngine 
    PRIVATE
    .
    PUBLIC
    include
)


target_link_libraries(
    ElgineEngine
    ${OPENGL_LIBRARIES} 
    ${SDL2_LIBRARIES}
)
