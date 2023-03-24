find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

target_sources(ElgineEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/elgine.cpp)


add_subdirectory(utils)
add_subdirectory(ecs)
add_subdirectory(components)
add_subdirectory(entities)

target_include_directories(ElgineEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

