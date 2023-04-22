add_library(SDwrapper_lib INTERFACE)

add_subdirectory(FatFs_SPI)

target_sources(rplog_lib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/SDWrapper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/hw_config.c
        
        )

target_include_directories(SDwrapper_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(SDwrapper_lib INTERFACE  
                        pico_stdlib 
                        FatFs_SPI
                        )
