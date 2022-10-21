# pico_e-paper
This is a project to build examples for e-paper displays on the Raspberry Pi pico.
Currently, the Pimoroni pico-inky and waveShare pico e-paper 2.66 displays are supported.

## Configuration
In the CMakeLists.txt files for the drivers and examples are target_compile_definitions to select build options

### drivers/uc8151d
LUT SPEED for UC8151D
-0 = slow..		4500 mS   very "blinky" during refresh
-1 = medium..	2000 mS		"
-2 = fast..	 	800 mS		"
-3 = turbo..	 250 mS   not as blinky, but leaves ghosts ( mitigated by whitewash before refresh )
target_compile_definitions(uc8151d INTERFACE LUT_SPEED=3 )

### drivers/uc8151d
LUT SPEED for EPD266
-0 = slow..		4000 mS   very "blinky" during refresh
-1 = fast..		???
target_compile_definitions(epd266 INTERFACE LUT_SPEED=1 )

### examples/pico_bike
Select the demo mode...
target_compile_definitions(pico_bike PRIVATE DEMO_MODE )

Define the wheel circumference in mm...
target_compile_definitions(pico_bike PRIVATE WHEEL_CIRCUMFERENCE_MM=700 )

## Examples
The first example is a bike computer, pico-bike. It displays the speed, elapsed time, and distance travelled.
Currently it's just a framework with no real sensor for bike movement, just a simulation that varies speed over a 1 hour trip.

