# cmake file for pico_e-paper driver uc8151d

add_library( uc8151d  INTERFACE )

target_sources ( uc8151d  INTERFACE
	uc8151d.c
 )

##############################################
#
#  compile options
#
###############################################

# LUT SPEED for UC8151D
# 0 = slow..	4500 mS   very "blinky" during refresh
# 1 = medium..	2000 mS		"
# 2 = fast..	 800 mS		"
# 3 = turbo..	 250 mS   not as blinky, but leaves ghosts ( mitigated by whitewash before refresh )

target_compile_definitions(uc8151d INTERFACE LUT_SPEED_UC8151D=3 )

###############################################


target_include_directories(uc8151d  INTERFACE 
	./
 )

