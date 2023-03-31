cmake_minimum_required(VERSION 3.20)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Assimp REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.1)

add_library(ElgineEngine STATIC)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(include/elgine)

target_include_directories(ElgineEngine 
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


target_link_libraries(
    ElgineEngine
    ${OPENGL_LIBRARIES} 
    ${SDL2_LIBRARIES}
    ${ASSIMP_LIBRARIES}
)
