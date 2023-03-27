target_sources(ElgineEngine PRIVATE stb_image.cpp)

add_subdirectory(imgui)
add_subdirectory(glm)

target_include_directories(ElgineEngine PUBLIC .)
