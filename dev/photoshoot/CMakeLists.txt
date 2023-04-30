cmake_minimum_required(VERSION 3.13)

add_executable(photoshoot)

#qvga_generate_img_header(test ${CMAKE_CURRENT_LIST_DIR}/img/blue.bmp Blue8Img)
#qvga_generate_img_header(test ${CMAKE_CURRENT_LIST_DIR}/img/peter8.bmp Peter8Img)

# Example source
target_sources(photoshoot PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        )


# Make sure TinyUSB can find tusb_config.h
target_include_directories(photoshoot PUBLIC
        ${CMAKE_CURRENT_LIST_DIR} )

# pull in common dependencies
# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_host
# for TinyUSB device support and tinyusb_board for the additional board support library used
target_link_libraries(photoshoot
    PUBLIC
    gui_lib
    rplog_lib
    pico_stdlib
    hardware_adc
    )

# create map/bin/hex file etc.
pico_add_extra_outputs(photoshoot)

pico_enable_stdio_usb(photoshoot 0)
pico_enable_stdio_uart(photoshoot 1)