function(qvga_generate_img_header TARGET BMP var_name)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
    # todo CMAKE_CURRENT_FUNCTION_LIST_DIR ... what version?
    #find_package(RaspPicoImg REQUIRED)

    cmake_parse_arguments(qvga_generate_img_header "" "OUTPUT_DIR" "" ${ARGN} )

    if (qvga_generate_img_header_OUTPUT_DIR)
        get_filename_component(HEADER_DIR ${qvga_generate_img_header_OUTPUT_DIR} ABSOLUTE)
    else()
        set(HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
    get_filename_component(BMP_NAME ${BMP} NAME)
    set(HEADER "${HEADER_DIR}/${BMP_NAME}.h")
    #message("Will generate ${HEADER}")
    get_filename_component(HEADER_GEN_TARGET ${BMP} NAME_WE)
    set(HEADER_GEN_TARGET "${TARGET}_${HEADER_GEN_TARGET}_bmp_h")
    
    get_filename_component(BMP_NAME_WE ${BMP} NAME_WE)
    
    #set(ARRAY_NAME "${BMP_NAME_WE}Img")
    set(ARRAY_NAME "${var_name}")

    add_custom_target(${HEADER_GEN_TARGET} DEPENDS ${HEADER})

    add_custom_command(OUTPUT ${HEADER}
            DEPENDS ${BMP}
            COMMAND RaspPicoImg ${BMP} ${HEADER} ${ARRAY_NAME}
            )
    add_dependencies(${TARGET} ${HEADER_GEN_TARGET})
    get_target_property(target_type ${TARGET} TYPE)
    if ("INTERFACE_LIBRARY" STREQUAL "${target_type}")
        target_include_directories(${TARGET} INTERFACE ${HEADER_DIR})
    else()
        target_include_directories(${TARGET} PUBLIC ${HEADER_DIR})
    endif()
endfunction()

function(qvga_generate_snd_header TARGET WAV var_name)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
    # todo CMAKE_CURRENT_FUNCTION_LIST_DIR ... what version?
    #find_package(RaspPicoSnd REQUIRED)

    cmake_parse_arguments(qvga_generate_snd_header "" "OUTPUT_DIR" "" ${ARGN} )

    if (qvga_generate_snd_header_OUTPUT_DIR)
        get_filename_component(HEADER_DIR ${qvga_generate_snd_header_OUTPUT_DIR} ABSOLUTE)
    else()
        set(HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
    get_filename_component(WAV_NAME ${WAV} NAME)
    set(HEADER "${HEADER_DIR}/${WAV_NAME}.h")
    #message("Will generate ${HEADER}")
    get_filename_component(HEADER_GEN_TARGET ${WAV} NAME_WE)
    set(HEADER_GEN_TARGET "${TARGET}_${HEADER_GEN_TARGET}_wav_h")
    
    get_filename_component(WAV_NAME_WE ${WAV} NAME_WE)
    
    #set(ARRAY_NAME "${WAV_NAME_WE}Snd")
    set(ARRAY_NAME "${var_name}")

    add_custom_target(${HEADER_GEN_TARGET} DEPENDS ${HEADER})

    add_custom_command(OUTPUT ${HEADER}
            DEPENDS ${WAV}
            COMMAND RaspPicoSnd ${WAV} ${HEADER} ${ARRAY_NAME}
            )
    add_dependencies(${TARGET} ${HEADER_GEN_TARGET})
    get_target_property(target_type ${TARGET} TYPE)
    if ("INTERFACE_LIBRARY" STREQUAL "${target_type}")
        target_include_directories(${TARGET} INTERFACE ${HEADER_DIR})
    else()
        target_include_directories(${TARGET} PUBLIC ${HEADER_DIR})
    endif()
endfunction()
