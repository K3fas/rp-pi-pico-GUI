add_library(vga_lib INTERFACE)

pico_generate_pio_header(vga_lib ${CMAKE_CURRENT_LIST_DIR}/src/vga.pio)

qvga_generate_img_header(vga_lib ${CMAKE_CURRENT_LIST_DIR}/font/font8x8.bmp Font8x8)


target_sources(vga_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/vga.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/canvas.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/mat2d.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/overclock.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/print.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pwmsnd.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/rand.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_layer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_pal.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_screen.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_util.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_vmode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_blitkey.S
        ${CMAKE_CURRENT_LIST_DIR}/src/vga_render.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_atext.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_attrib8.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_color.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_ctext.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_dtext.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_fastsprite.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_ftext.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_graph1.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_graph2.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_graph4.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_graph8.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_graph8mat.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_graph8persp.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_gtext.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_level.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_levelgrad.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_mtext.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_oscil.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_oscline.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_persp.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_persp2.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_plane2.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_progress.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_sprite.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tile.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tile2.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tilepersp.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tilepersp2.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tilepersp3.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tilepersp4.S
        ${CMAKE_CURRENT_LIST_DIR}/render/vga_tilepersp15.S
        ${CMAKE_CURRENT_LIST_DIR}/font/font_boldB_8x16.cpp
        )

target_include_directories(vga_lib INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}/render
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/include/util
        ${CMAKE_CURRENT_LIST_DIR}/include/vga)

target_link_libraries(vga_lib INTERFACE
                        pico_stdlib 
                        pico_multicore 
                        #pico_stdio_usb
                        pico_mem_ops
                        hardware_pwm 
                        hardware_dma 
                        hardware_pio 
                        hardware_adc 
                        hardware_flash 
                        hardware_i2c
                        hardware_interp
                        hardware_rtc
                        hardware_spi
                        boot_picoboot_headers
                        boot_uf2_headers
                        )
