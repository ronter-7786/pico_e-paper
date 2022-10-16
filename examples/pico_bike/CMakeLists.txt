# cmake file for pico_e-paper example  pico_bike

add_executable(pico_bike ../../utilities/font_7seg_24x48.c)

target_sources ( pico_bike PRIVATE
  pico_bike.c
)

# Pull in libraries that we need
target_link_libraries( pico_bike PRIVATE
        pico_multicore
        pico_stdlib 
		pico_unique_id
		hardware_pio
		hardware_rtc
		hardware_dma
		pio_spi
		uc8151d
		utilities
 )

 target_include_directories(pico_bike  PRIVATE 
   ${CMAKE_CURRENT_LIST_DIR}
   ${CMAKE_CURRENT_BIN_DIR}
 )


# create map/bin/hex file etc.
pico_add_extra_outputs(pico_bike)

