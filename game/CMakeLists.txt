

target_sources(ElgineGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gamemanager.cpp)

target_include_directories(ElgineGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(entities)
