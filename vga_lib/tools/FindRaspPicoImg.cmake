# Finds (or builds) the RaspPicoImg executable
#
# This will define the following variables
#
#    RaspPicoImg_FOUND
#
# and the following imported targets
#
#     RaspPicoImg
#

if (NOT RaspPicoImg_FOUND)
    # todo we would like to use pckgconfig to look for it first
    # see https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

    include(ExternalProject)

    set(RaspPicoImg_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/RaspPicoImg)
    set(RaspPicoImg_BINARY_DIR ${CMAKE_BINARY_DIR}/RaspPicoImg)

    set(RaspPicoImgBuild_TARGET RaspPicoImgBuild)
    set(RaspPicoImg_TARGET RaspPicoImg)

    if (NOT TARGET ${RaspPicoImgBuild_TARGET})
        pico_message_debug("RaspPicoImg will need to be built")
#        message("Adding external project ${RaspPicoImgBuild_Target} in ${CMAKE_CURRENT_LIST_DIR}}")
        ExternalProject_Add(${RaspPicoImgBuild_TARGET}
                PREFIX RaspPicoImg SOURCE_DIR ${RaspPicoImg_SOURCE_DIR}
                BINARY_DIR ${RaspPicoImg_BINARY_DIR}
                BUILD_ALWAYS 1 # force dependency checking
                INSTALL_COMMAND ""
                )
    endif()

    if (CMAKE_HOST_WIN32)
        set(RaspPicoImg_EXECUTABLE ${RaspPicoImg_BINARY_DIR}/RaspPicoImg.exe)
    else()
        set(RaspPicoImg_EXECUTABLE ${RaspPicoImg_BINARY_DIR}/RaspPicoImg)
    endif()
    if(NOT TARGET ${RaspPicoImg_TARGET})
#        message("Adding executable ${RaspPicoImg_Target} in ${CMAKE_CURRENT_LIST_DIR}")
        add_executable(${RaspPicoImg_TARGET} IMPORTED)
    endif()
    set_property(TARGET ${RaspPicoImg_TARGET} PROPERTY IMPORTED_LOCATION
            ${RaspPicoImg_EXECUTABLE})

#    message("EXE is ${RaspPicoImg_EXECUTABLE}")
    add_dependencies(${RaspPicoImg_TARGET} ${RaspPicoImgBuild_TARGET})
    set(RaspPicoImg_FOUND 1)
endif()
