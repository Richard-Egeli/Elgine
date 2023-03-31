target_sources(ElgineEngine PRIVATE stb/stb_image.cpp)

add_subdirectory(glm)
add_subdirectory(imgui)
# add_subdirectory(assimp)

target_include_directories(ElgineEngine PUBLIC .
    stb
    # assimp/include
    glm
)

# target_include_directories(ElgineEngine PRIVATE
#     assimp/include/assimp
# )
