# cmake file for pico_e-paper example  pico_bike

add_executable(pico_bike )

target_sources ( pico_bike PRIVATE
  pico_bike.c
)

target_compile_definitions(pico_bike PRIVATE DEMO_MODE )
target_compile_definitions(pico_bike PRIVATE WHEEL_DIAMETER_MM=700.0 )

# select the display type
# 1 = INKY			for Pimoroni pico inky
# 2 = EPAPER_266	for WaveShare pico e-paper 2.66"
target_compile_definitions(pico_bike PRIVATE DISPLAY_TYPE=1 )


# Pull in libraries that we need
target_link_libraries( pico_bike PRIVATE
        pico_multicore
        pico_stdlib 
		pico_unique_id
		hardware_pio
		hardware_rtc
		hardware_dma
		hardware_adc
		pio_spi
		uc8151d
		epd266
		graphics
 )

 target_include_directories(pico_bike  PRIVATE 
   ${CMAKE_CURRENT_LIST_DIR}
   ${CMAKE_CURRENT_BIN_DIR}
 )


# create map/bin/hex file etc.
pico_add_extra_outputs(pico_bike)

