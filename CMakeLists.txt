# cmake file for top level pico_e-paper demos
cmake_minimum_required(VERSION 3.16)

set(CMAKE_VERBOSE_MAKEFILE ON)

include ($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_e-paper C CXX ASM)

include(PicoSDKConfig.cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

function(add_resource target file)
  get_filename_component(NAME ${ARGV1} NAME_WE)
  set(FILENAME ${ARGV1})

  add_custom_command(
    OUTPUT ${NAME}.o

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
            ${CMAKE_CURRENT_BINARY_DIR}

    COMMAND arm-none-eabi-ld -r -b binary -o ${NAME}.o ${FILENAME}
    DEPENDS ${FILENAME}
  )

  target_sources(${ARGV0} PRIVATE ${NAME}.o)
endfunction(add_resource)

add_subdirectory(drivers)
add_subdirectory(graphics)
add_subdirectory(examples)

