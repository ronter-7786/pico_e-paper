# cmake file for pico_e-paper utilities

add_library( utilities  INTERFACE )


target_sources ( utilities  INTERFACE
	pixel_func.c
	font_8x16.c
 )

target_include_directories(utilities  INTERFACE 
  ${CMAKE_CURRENT_LIST_DIR}
 )

