target_sources(ElgineEngine PRIVATE 
    imgui.cpp 
    imgui_impl_opengl3.cpp 
    imgui_impl_sdl2.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

target_include_directories(ElgineEngine PRIVATE .)
