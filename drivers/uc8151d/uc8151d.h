#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/util/queue.h>
#include <pico/unique_id.h>
#include <pico/mutex.h>
#include <pico/sem.h>
#include <pico/bootrom.h>

#include "pixel_func.h"
#include "pio_spi.h"


/*****************************************************
 *
 *  Defines for UC8151D controller chip
 *   on Pimoroni pico inky 2.9" e-ink 296 x 128 Mono
 *
******************************************************/

#define UC8151D_BUSY_PIN				26			// Busy on GPIO 26
#define UC8151D_RESET_PIN				21			// Reset on GPIO 21

#ifndef __NDEBUG
#define UC8151D_SPI_BAUD				1000000		// clock speed of SPI bus
#else
#define UC8151D_SPI_BAUD				10000000	// clock speed of SPI bus
#endif

#define UC8151D_SPI_CHANNEL				0			// display spi channel 0
#define UC8151D_DC_PIN					20			// C/D on GPIO 20
#define UC8151D_CS_PIN					17			// CS on GPIO17
#define UC8151D_BUSY_PIN				26			// BUSY! on GPIO 26

#define UC8151D_SWA_PIN					12			// Button A on GPIO12
#define UC8151D_SWB_PIN					13			// Button B on GPIO13
#define UC8151D_SWC_PIN					14			// Button C on GPIO14

#define UC8151D_LCDWIDTH				296			// 296 x 128 pixel sisplay
#define UC8151D_LCDHEIGHT				128
#define UC8151D_FRAME_BUFFER_SIZE		(( UC8151D_LCDWIDTH / 8 ) * UC8151D_LCDHEIGHT )

#define UC8151D_CMD_PSR					0x00		// Panel Setting
#define UC8151D_CMD_PWR					0x01		// Power Setting
#define UC8151D_CMD_POF					0x02		// Power Off
#define UC8151D_CMD_PFS					0x03		// Power Off Sequence Setting
#define UC8151D_CMD_PON					0x04		// Power On
#define UC8151D_CMD_PMES				0x05		// Power On Measure
#define UC8151D_CMD_BTST				0x06		// Booster Soft Start
#define UC8151D_CMD_DSLP				0x07		// Deep Sleep
#define UC8151D_CMD_DTM1				0x10		// Display Start Transmission 1
#define UC8151D_CMD_DSP					0x11		// Data Stop
#define UC8151D_CMD_DRF					0x12		// Display Refresh
#define UC8151D_CMD_DTM2				0x13		// Display Start Transmission 2
#define UC8151D_CMD_AUTO				0x17		// Auto Sequence
#define UC8151D_CMD_LUT_VCOM			0x20		// LUT VCOM
#define UC8151D_CMD_LUT_WW				0x21		// LUT WW
#define UC8151D_CMD_LUT_BW				0x22		// LUT BW
#define UC8151D_CMD_LUT_WB				0x23		// LUT WB
#define UC8151D_CMD_LUT_BB				0x24		// LUT BB
#define UC8151D_CMD_LUTOPT				0x2A		// LUT Option
#define UC8151D_CMD_PLL					0x30		// PLL Control
#define UC8151D_CMD_TSC					0x40		// Temperature Sensor Calibration
#define UC8151D_CMD_TSE					0x41		// Temperature Sensor Calibration
#define UC8151D_CMD_TSW					0x42		// Temperature Sensor Write
#define UC8151D_CMD_TSR					0x43		// Temperature Sensor Read
#define UC8151D_CMD_PBC					0x44		// Panel Break Check
#define UC8151D_CMD_CDI					0x50		// VCOM & Data Interval Setting`
#define UC8151D_CMD_LPD					0x51		// Lower Power Detection
#define UC8151D_CMD_TCON				0x60		// TCON Setting
#define UC8151D_CMD_TRES				0x61		// Resolution Setting
#define UC8151D_CMD_GSST				0x65		// Gate/Source Start Setting
#define UC8151D_CMD_REV					0x70		// Revision
#define UC8151D_CMD_FLG					0x71		// Get Status
#define UC8151D_CMD_AMV					0x80		// Auto Measurement VCOM
#define UC8151D_CMD_VV					0x81		// Read VCOM value
#define UC8151D_CMD_VDCS				0x82		// VCOM_DC Setting
#define UC8151D_CMD_PTL					0x90		// Partial Window
#define UC8151D_CMD_PTIN				0x91		// Partial In
#define UC8151D_CMD_PTOUT				0x92		// Partial Out
#define UC8151D_CMD_PGM					0xA0		// Program Mode
#define UC8151D_CMD_APG					0xA1		// Active Programming
#define UC8151D_CMD_ROTP				0xA2		// Read OTP
#define UC8151D_CMD_CCSET				0xE0		// Cascade Setting
#define UC8151D_CMD_PWS					0xE3		// Power Saving
#define UC8151D_CMD_LVSEL				0xE4		// LVD Voltage Select
#define UC8151D_CMD_TSSET				0xE5		// Force Temperature

enum PSR_FLAGS {
      RES_96x230   = 0b00000000,
      RES_96x252   = 0b01000000,
      RES_128x296  = 0b10000000,
      RES_160x296  = 0b11000000,

      LUT_OTP      = 0b00000000,
      LUT_REG      = 0b00100000,

      FORMAT_BWR   = 0b00000000,
      FORMAT_BW    = 0b00010000,

      SCAN_DOWN    = 0b00000000,
      SCAN_UP      = 0b00001000,

      SHIFT_LEFT   = 0b00000000,
      SHIFT_RIGHT  = 0b00000100,

      BOOSTER_OFF  = 0b00000000,
      BOOSTER_ON   = 0b00000010,

      RESET_SOFT   = 0b00000000,
      RESET_NONE   = 0b00000001
    };

enum PWR_FLAGS_1 {
      VDS_EXTERNAL = 0b00000000,
      VDS_INTERNAL = 0b00000010,

      VDG_EXTERNAL = 0b00000000,
      VDG_INTERNAL = 0b00000001
    };

enum PWR_FLAGS_2 {
      VCOM_VD      = 0b00000000,
      VCOM_VG      = 0b00000100,

      VGHL_16V     = 0b00000000,
      VGHL_15V     = 0b00000001,
      VGHL_14V     = 0b00000010,
      VGHL_13V     = 0b00000011
    };

enum BOOSTER_FLAGS {
      START_10MS = 0b00000000,
      START_20MS = 0b01000000,
      START_30MS = 0b10000000,
      START_40MS = 0b11000000,

      STRENGTH_1 = 0b00000000,
      STRENGTH_2 = 0b00001000,
      STRENGTH_3 = 0b00010000,
      STRENGTH_4 = 0b00011000,
      STRENGTH_5 = 0b00100000,
      STRENGTH_6 = 0b00101000,
      STRENGTH_7 = 0b00110000,
      STRENGTH_8 = 0b00111000,

      OFF_0_27US = 0b00000000,
      OFF_0_34US = 0b00000001,
      OFF_0_40US = 0b00000010,
      OFF_0_54US = 0b00000011,
      OFF_0_80US = 0b00000100,
      OFF_1_54US = 0b00000101,
      OFF_3_34US = 0b00000110,
      OFF_6_58US = 0b00000111
    };

enum PFS_FLAGS {
      FRAMES_1   = 0b00000000,
      FRAMES_2   = 0b00010000,
      FRAMES_3   = 0b00100000,
      FRAMES_4   = 0b00110000
    };

enum TSE_FLAGS {
      TEMP_INTERNAL = 0b00000000,
      TEMP_EXTERNAL = 0b10000000,

      OFFSET_0      = 0b00000000,
      OFFSET_1      = 0b00000001,
      OFFSET_2      = 0b00000010,
      OFFSET_3      = 0b00000011,
      OFFSET_4      = 0b00000100,
      OFFSET_5      = 0b00000101,
      OFFSET_6      = 0b00000110,
      OFFSET_7      = 0b00000111,

      OFFSET_MIN_8  = 0b00001000,
      OFFSET_MIN_7  = 0b00001001,
      OFFSET_MIN_6  = 0b00001010,
      OFFSET_MIN_5  = 0b00001011,
      OFFSET_MIN_4  = 0b00001100,
      OFFSET_MIN_3  = 0b00001101,
      OFFSET_MIN_2  = 0b00001110,
      OFFSET_MIN_1  = 0b00001111
    };

enum PLL_FLAGS {
      // other frequency options exist but there doesn't seem to be much
      // point in including them - this is a fair range of options...
      HZ_29      = 0b00111111,
      HZ_33      = 0b00111110,
      HZ_40      = 0b00111101,
      HZ_50      = 0b00111100,
      HZ_67      = 0b00111011,
      HZ_100     = 0b00111010,
      HZ_200     = 0b00111001
    };



typedef struct
{
	uint8_t			UC8151DCmd_code_data;
	uint8_t			UC8151DArgs;
	uint8_t			UC8151DCmd_value;
	bool			UC8151DBusyWait;
	bool			UC8151DHoldCS;
	uint16_t		UC8151DCmd_delay;
	uint8_t			*UC8151DArray;
}UC8151D_CMD;

#define UC8151DCMD		0
#define UC8151DDATA		1
#define UC8151DARRAY	2
#define UC8151DHOLD_CS	0x10
#define UC8151DDONE		0xFF

extern DISPLAY_PARAMS	UC8151DDisplayParams;
extern FONT_DESC	font_8x16_desc;



