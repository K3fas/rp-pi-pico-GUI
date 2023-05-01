add_library(gui_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include/rpgui.hpp)

set(use_picoqvga false)

target_sources(gui_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/util/hid_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/util/Timers.cpp
        ${CMAKE_CURRENT_LIST_DIR}/util/IVGA.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/rp_core.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/Element.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/VisualElement.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/View.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/Clickable.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Sprite.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Button.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/CheckBox.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Circle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Entry.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Label.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Line.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Polyline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/ProgressBar.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/RadioButton.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Rectangle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Slider.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Stepper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Switch.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Cursor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/layouts/AbsoluteLayout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/layouts/StackLayout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/layouts/Layout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/events/Dispatcher.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/events/MouseDispatcher.cpp
        )

target_include_directories(gui_lib INTERFACE
${CMAKE_CURRENT_LIST_DIR}/include
${CMAKE_CURRENT_LIST_DIR}/include/common
${CMAKE_CURRENT_LIST_DIR}/include/elements
${CMAKE_CURRENT_LIST_DIR}/include/events
${CMAKE_CURRENT_LIST_DIR}/include/layouts
${CMAKE_CURRENT_LIST_DIR}/include/pages
${CMAKE_CURRENT_LIST_DIR}/util
${CMAKE_CURRENT_LIST_DIR}/config
                )

target_link_libraries(gui_lib INTERFACE 
                        pico_stdlib
                        rplog_lib 
                        tinyusb_host
                        tinyusb_board
                        )

if(use_picoqvga)
        target_link_libraries(gui_lib INTERFACE
        qvga_lib)
else()
        target_compile_definitions(gui_lib INTERFACE PICOVGA)
        target_link_libraries(gui_lib INTERFACE
                                vga_lib)
endif()