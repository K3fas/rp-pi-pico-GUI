add_library(GUI_lib INTERFACE)

target_sources(GUI_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/hid_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/RP_GUI.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/rp_core.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/Base.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/View.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/Clickable.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/Button.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/elements/CheckBox.cpp
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
        ${CMAKE_CURRENT_LIST_DIR}/src/layouts/AbsoluteLayout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/layouts/StackLayout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/layouts/Layout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/events/Dispatcher.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/events/MouseEvent.cpp
        )

target_include_directories(GUI_lib INTERFACE
${CMAKE_CURRENT_LIST_DIR}/include
${CMAKE_CURRENT_LIST_DIR}/include/common
${CMAKE_CURRENT_LIST_DIR}/include/elements
${CMAKE_CURRENT_LIST_DIR}/include/events
${CMAKE_CURRENT_LIST_DIR}/include/layouts
${CMAKE_CURRENT_LIST_DIR}/include/pages
                )

target_link_libraries(GUI_lib INTERFACE 
                        qvga_lib
                        #vga_lib 
                        pico_stdlib 
                        tinyusb_host
                        tinyusb_board
                        )