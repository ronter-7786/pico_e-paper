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

# LUT SPEED for EPD 2.66
# 0 = slow..	4500 mS   very "blinky" during refresh
# 1 = medium..	2000 mS		"
# 2 = fast..	 800 mS		"
# 3 = turbo..	 250 mS   not as blinky, but leaves ghosts ( mitigated by whitewash before refresh )

target_compile_definitions(epd266 INTERFACE LUT_SPEED=3 )

###############################################


target_include_directories(epd266  INTERFACE 
	./
 )

