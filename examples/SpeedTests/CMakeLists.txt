cmake_minimum_required(VERSION 3.13)

add_executable(speedTests)

#qvga_generate_img_header(VGAHID ${CMAKE_CURRENT_LIST_DIR}/img/cursor_small.bmp Cursor8Img)

# Example source
target_sources(speedTests PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SpeedTest.cpp
        )


# Make sure TinyUSB can find tusb_config.h
target_include_directories(speedTests PUBLIC
        ${CMAKE_CURRENT_LIST_DIR} )

# pull in common dependencies
# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_host
# for TinyUSB device support and tinyusb_board for the additional board support library used
target_link_libraries(speedTests
    PUBLIC
    gui_lib
    rplog_lib
    pico_stdlib
    hardware_adc
    )

# create map/bin/hex file etc.
pico_add_extra_outputs(speedTests)

pico_enable_stdio_usb(speedTests 0)
pico_enable_stdio_uart(speedTests 1)