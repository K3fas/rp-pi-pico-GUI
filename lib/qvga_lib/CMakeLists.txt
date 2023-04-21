add_library(qvga_lib INTERFACE)

pico_generate_pio_header(qvga_lib ${CMAKE_CURRENT_LIST_DIR}/src/qvga.pio)

qvga_generate_img_header(qvga_lib ${CMAKE_CURRENT_LIST_DIR}/img/font8x8.bmp Font8x8)

target_sources(qvga_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/draw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/mat2d.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pwmsnd.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/qvga.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/rand.cpp
        )

target_include_directories(qvga_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(qvga_lib INTERFACE
                pico_stdlib 
                pico_multicore
                hardware_pwm
                hardware_dma
                hardware_pio)
