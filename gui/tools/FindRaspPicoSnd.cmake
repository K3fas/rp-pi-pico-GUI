# Finds (or builds) the RaspPicoSnd executable
#
# This will define the following variables
#
#    RaspPicoSnd_FOUND
#
# and the following imported targets
#
#     RaspPicoSnd
#

if (NOT RaspPicoSnd_FOUND)
    # todo we would like to use pckgconfig to look for it first
    # see https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

    include(ExternalProject)

    set(RaspPicoSnd_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/RaspPicoSnd)
    set(RaspPicoSnd_BINARY_DIR ${CMAKE_BINARY_DIR}/RaspPicoSnd)

    set(RaspPicoSndBuild_TARGET RaspPicoSndBuild)
    set(RaspPicoSnd_TARGET RaspPicoSnd)

    if (NOT TARGET ${RaspPicoSndBuild_TARGET})
        pico_message_debug("RaspPicoSnd will need to be built")
#        message("Adding external project ${RaspPicoSndBuild_Target} in ${CMAKE_CURRENT_LIST_DIR}}")
        ExternalProject_Add(${RaspPicoSndBuild_TARGET}
                PREFIX RaspPicoSnd SOURCE_DIR ${RaspPicoSnd_SOURCE_DIR}
                BINARY_DIR ${RaspPicoSnd_BINARY_DIR}
                BUILD_ALWAYS 1 # force dependency checking
                INSTALL_COMMAND ""
                )
    endif()

    if (CMAKE_HOST_WIN32)
        set(RaspPicoSnd_EXECUTABLE ${RaspPicoSnd_BINARY_DIR}/RaspPicoSnd.exe)
    else()
        set(RaspPicoSnd_EXECUTABLE ${RaspPicoSnd_BINARY_DIR}/RaspPicoSnd)
    endif()
    if(NOT TARGET ${RaspPicoSnd_TARGET})
#        message("Adding executable ${RaspPicoSnd_Target} in ${CMAKE_CURRENT_LIST_DIR}")
        add_executable(${RaspPicoSnd_TARGET} IMPORTED)
    endif()
    set_property(TARGET ${RaspPicoSnd_TARGET} PROPERTY IMPORTED_LOCATION
            ${RaspPicoSnd_EXECUTABLE})

#    message("EXE is ${RaspPicoSnd_EXECUTABLE}")
    add_dependencies(${RaspPicoSnd_TARGET} ${RaspPicoSndBuild_TARGET})
    set(RaspPicoSnd_FOUND 1)
endif()
