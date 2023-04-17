cmake_minimum_required(VERSION 3.13)

add_executable(RpKit)

#qvga_generate_img_header(VGAHID ${CMAKE_CURRENT_LIST_DIR}/img/cursor_small.bmp Cursor8Img)

pico_generate_pio_header(RpKit ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio)

# Example source
target_sources(RpKit PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/hw_config.c
        )


# Make sure TinyUSB can find tusb_config.h
target_include_directories(RpKit PUBLIC
        ${CMAKE_CURRENT_LIST_DIR} )

# pull in common dependencies
# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_host
# for TinyUSB device support and tinyusb_board for the additional board support library used
target_link_libraries(RpKit
    PUBLIC
    GUI_lib
    pico_stdlib
    pico_multicore
    hardware_adc
    hardware_pio
    rplog_lib
    )

# create map/bin/hex file etc.
pico_add_extra_outputs(RpKit)

pico_enable_stdio_usb(RpKit 0)
pico_enable_stdio_uart(RpKit 1)