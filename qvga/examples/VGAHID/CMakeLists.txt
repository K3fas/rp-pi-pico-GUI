cmake_minimum_required(VERSION 3.13)

add_executable(VGAHID
)

#qvga_generate_img_header(VGAHID ${CMAKE_CURRENT_LIST_DIR}/img/cursor_small.bmp Cursor8Img)

# Example source
target_sources(VGAHID PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/hid_app.cpp
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/msc_app.cpp
        )

target_sources(VGAHID INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/tusb_data.hpp
        )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(VGAHID PUBLIC
        ${CMAKE_CURRENT_LIST_DIR} )

# pull in common dependencies
# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_host
# for TinyUSB device support and tinyusb_board for the additional board support library used
target_link_libraries(VGAHID
    PUBLIC
    qvga_lib
    pico_stdlib
    tinyusb_host
    tinyusb_board
    hardware_adc
    )

# create map/bin/hex file etc.
pico_add_extra_outputs(VGAHID)

pico_enable_stdio_usb(VGAHID 0)
pico_enable_stdio_uart(VGAHID 1)