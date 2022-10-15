# cmake file for pico_e-paper driver pio_spi

add_library( pio_spi  INTERFACE )

set( pico_generate_pio_header_OUTPUT_DIR "${CMAKE_CURRENT_LIST_DIR}" )
pico_generate_pio_header(pio_spi ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

target_sources ( pio_spi  INTERFACE
	pio_spi.c
 )

target_include_directories(pio_spi  INTERFACE 
  ${CMAKE_CURRENT_LIST_DIR}
 )
