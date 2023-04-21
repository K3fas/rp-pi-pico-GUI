add_library(rplog_lib INTERFACE)

target_sources(rplog_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/rp_logger.cpp
        
        )

target_include_directories(rplog_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(rplog_lib INTERFACE  
                        pico_stdlib 
                        FatFs_SPI
                        SDwrapper_lib
                        )
