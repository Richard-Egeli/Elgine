target_sources(ElgineEngine PRIVATE stb/stb_image.cpp)

add_subdirectory(glm)
add_subdirectory(imgui)

target_include_directories(ElgineEngine PUBLIC .
    stb
    assimp/include
    glm
)
