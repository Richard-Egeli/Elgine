

target_sources(ElgineEngine PRIVATE elgine.cpp default-shader.cpp)

target_include_directories(ElgineEngine PRIVATE .)

add_subdirectory(utils)
add_subdirectory(components)
add_subdirectory(entities)
add_subdirectory(types)
add_subdirectory(systems)
add_subdirectory(input)
add_subdirectory(camera)
add_subdirectory(ecs)
