#pragma once

////////////////////////////////////////////////////////////////////////////////////
//		Software version

#define  VERSION_MAJOR	00
#define  VERSION_MINOR  01

//
///////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include <pico/multicore.h>
#include <pico/util/queue.h>
#include <pico/unique_id.h>
#include <pico/mutex.h>
#include <pico/sem.h>
#include <pico/bootrom.h>
#include <pico/stdlib.h>

#include <hardware/irq.h>
#include <hardware/watchdog.h>
#include <hardware/resets.h>
#include <hardware/rtc.h>
#include <hardware/adc.h>
#include <hardware/clocks.h>
#include <hardware/structs/clocks.h>
#include <hardware/flash.h>

#include "pio_spi.h"
#include "uc8151d.h"
#include "epd266.h"
#include "pixel_func.h"

/////////////////////////////////
// defines for  gpio pin numbers 
/////////////////////////////////

#define PICO_LED_PIN			25					// this turns LED on/off

#define WHEEL_REV_PIN			27					// trigger for wheel revolution

#define PICO_FLASH_SIZE			PICO_FLASH_SIZE_BYTES		// 2 MB Flash
#define PICO_FLASH_START		XIP_BASE					// 0x10000000


// global functions
extern void gpioIrqCallback(uint _gpioNum, uint32_t _events);
extern void __no_inline_not_in_flash_func(wait_for_reboot)(void);
extern void	reboot_to_usb(void);