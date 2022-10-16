# cmake file for pico_e-paper utilities

add_library( graphics  INTERFACE )


target_sources ( graphics  INTERFACE
	pixel_func.c
	font_8x16.c
	font_7seg_24x48.c
 )

target_include_directories(graphics  INTERFACE 
  ${CMAKE_CURRENT_LIST_DIR}
 )

