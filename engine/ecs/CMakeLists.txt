# target_sources(ElgineEngine PRIVATE 
    # ${CMAKE_CURRENT_SOURCE_DIR}/ecs.cpp
# )

add_subdirectory(components)

target_include_directories(ElgineEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
