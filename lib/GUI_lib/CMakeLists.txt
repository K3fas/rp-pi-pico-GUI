add_library(GUI_lib INTERFACE)

target_sources(GUI_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/hid_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/RP_GUI.cpp
        )

target_include_directories(GUI_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(GUI_lib INTERFACE qvga_lib pico_stdlib)