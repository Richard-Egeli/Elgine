
target_sources(ElgineEngine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/debug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/time.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/loader.cpp
)

target_include_directories(ElgineEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
