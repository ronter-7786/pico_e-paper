# pico_e-paper
This is a project to build examples for e-paper displays on the Raspberry Pi pico.
Currently, the Pimoroni pico inky 2.9" E-Ink and WaveShare pico e-paper 2.66" displays are supported.

## Configuration
In the CMakeLists.txt files for the drivers and examples are target_compile_definitions to select build options

### drivers/uc8151d
LUT_SPEED for UC8151D
- 0 = slow..		4500 mS   very "blinky" during refresh
- 1 = medium..	    2000 mS		"
- 2 = fast..	 	800 mS		"
- 3 = turbo..	    250 mS   not as blinky, but leaves ghosts
- 4 = turbo + ..	500 ms	 twice as long as turbo, with double pass refresh

target_compile_definitions(uc8151d INTERFACE LUT_SPEED_UC8151D=3 )

### drivers/epd266
 LUT SPEED for EPD266
- 0 = slow..		4500 mS   very "blinky" during refresh
- 1 = fast..		 880 mS	  fast but possibly ghosty	
- 2 = fast+..		1760 mS	  twice as long as fast, but with double pass refresh

target_compile_definitions(epd266 INTERFACE LUT_SPEED_EPD266=1 )

### examples/pico_bike
Select the demo mode...

target_compile_definitions(pico_bike PRIVATE DEMO_MODE )

Define the wheel diameter in mm...

target_compile_definitions(pico_bike PRIVATE WHEEL_DIAMETER_MM=700 )

## Examples
The first example is a bike computer, pico-bike. It displays the speed, elapsed time, and distance travelled.
Currently it's just a framework with no real sensor for bike movement, just a simulation that varies speed over a 1 hour trip.
The program uses core 1 to refresh the display, while core 0 does the computation for speed via ( simulated ) wheel revolutions, and manages the display menus.

### Making it real 
By adding a Hall-Effect transistor sensor, and compiling without the target_compile_definitions(pico_bike PRIVATE DEMO_MODE ), the pico_bike demo can be used in the 'real world'.  

The Hall Effect transistor is mounted to the frame with a piece of metal pipe strapping in red shrink tubing. I attached a magnet to a reflector on the spokes, and positioned the sensor to detect it.
![Mounting the sensor](/assets/images/HallEffectSensor.jpg)

I attached large pins to the pico, 
![Pico with large pins](/assets/images/PicoPins.jpg)

and made a small board to insert the pico + display. The board is zip-tied to the handle bars...
![Mounting the carrier board](/assets/images/CarrierBoard.jpg)

I'm powering it with a 9V battery and a switching supply. It was the only battery holder I had at the time, but did test it with 4 AA NiMh batteries.
![Power supply](/assets/images/PowerSupply.jpg)

After a test run, here's what the display shows...
![Pico Display](/assets/images/PicoDisplay.jpg)


