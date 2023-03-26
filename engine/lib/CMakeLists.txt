target_sources(ElgineEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp)

add_subdirectory(glm)

target_include_directories(ElgineEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
