# pico_e-paper
This is a project to build a 'proof of concept' example for e-paper displays on the Raspberry Pi pico.

Currently only the Pimoroni pico inky 2.9" E-Ink, and WaveShare pico e-paper 2.66" displays are supported.
Both of these displays are pre-mounted on modules that you just plug a pico into; all you need to provide is power via usb.

E-paper displays are by far the most visible displays in direct sunlight that I have ever tried; the contrast can be very sharp. As a bonus, it also can be very low power. Once it is refreshed, it retains the image for a very long time, even after it's powered off. To me it seems ideal for an outdoor mobile battery operated display - like a bike 'computer'. 

On the downside, display refresh is a nightmare. A "full refresh" can take over 4 seconds during which the display annoyingly flashes on and off. Fortunately, both of the displays I'm using have a "partial refresh" feature that also refreshes the entire screen, but in less than 1 second, and as fast as 250 milliseconds. The problem now is that a partial refresh leaves behind a shadow, or ghost of the previous display. If you do multiple partial refreshes of the same image, then the ghosts fade, and contast gets sharper. This is demonstrated by a timer display that's updated every second. Over time, the hours and minutes are sharp but the least significant seconds digit is haunted.

There are some otions in this software to control the use of partial refresh. They're called LUTs; which I figure means Look Up Table? The use of these LUTs determine the speed of the refresh; I have no idea how or why that works. The available LUTs are unique with each display driver. The Pimoroni is faster, but has a slight flicker during partial refresh. The Waveshare is slower, but doesn't flicker.

I read that it was O.K. to use the partial refresh cycles, but periodically a full refresh should be done. On a mobile app, that could be at power up.

## Disclaimer
I've never written any software specifically for e-paper displays before buying these samples; however I have implemented other types of SPI/I2C displays for the pico. I made this sample program just to try them out. So, I'm not an expert. For all I know, using these displays meant for grocery shelf tags in this way may shorten their lifespan. Therefore, use the software here as you will, keeping this caveat in mind.


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
- 2 = fast+..		1760 mS	  twice as long as fast, with double pass refresh

target_compile_definitions(epd266 INTERFACE LUT_SPEED_EPD266=1 )

### examples/pico_bike
Select the demo mode...

target_compile_definitions(pico_bike PRIVATE DEMO_MODE )

Define the wheel diameter in mm...

target_compile_definitions(pico_bike PRIVATE WHEEL_DIAMETER_MM=700 )

## Examples
The first example is a bike computer, pico-bike. It displays the speed, elapsed time, and distance travelled.
It has a built-in demo mode that simulates wheel rotation - varying its speed over a 1 hour trip.

The program uses core 1 to refresh the display, while core 0 does the computation for speed via wheel revolutions, and manages the display menus. Inter-core synchronization uses the pico SDK semaphore and mutex features.

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


