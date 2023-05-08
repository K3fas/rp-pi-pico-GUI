cmake_minimum_required(VERSION 3.13)

add_executable(KitControl)

pico_generate_pio_header(KitControl ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio)

# Example source
target_sources(KitControl PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        )


# Make sure TinyUSB can find tusb_config.h
target_include_directories(KitControl PUBLIC
        ${CMAKE_CURRENT_LIST_DIR} )

# pull in common dependencies
# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_host
# for TinyUSB device support and tinyusb_board for the additional board support library used
target_link_libraries(KitControl
    PUBLIC
    gui_lib
    rplog_lib
    pico_stdlib
    hardware_adc
    )

# create map/bin/hex file etc.
pico_add_extra_outputs(KitControl)

pico_enable_stdio_usb(KitControl 0)
pico_enable_stdio_uart(KitControl 1)