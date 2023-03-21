find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})


add_library(ElgineEngine STATIC
    elgine.cpp
)

add_subdirectory(utils)
add_subdirectory(ecs)

target_include_directories(ElgineEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ElgineEngine ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
