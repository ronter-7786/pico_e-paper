# cmake file for pico_e-paper driver epd266

add_library( epd266  INTERFACE )

target_sources ( epd266  INTERFACE
	epd266.c
 )

##############################################
#
#  compile options
#
###############################################

# LUT SPEED for EPD266
# 0 = slow..				4500 mS   very "blinky" during refresh
# 1 = fast..				 880 mS	  fast, but possible ghosts	
# 2 = fast with whitewash	1600 mS	  twice as long as fast, but with a pre-whitewash

target_compile_definitions(epd266 INTERFACE LUT_SPEED_EPD266=1 )

target_include_directories(epd266  INTERFACE 
	./
 )

