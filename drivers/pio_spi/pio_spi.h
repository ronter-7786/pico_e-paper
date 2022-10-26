#pragma once

#include <hardware/pio.h>
#include <hardware/dma.h>
#include <hardware/clocks.h>
#include <pico/mutex.h>
#include <pico/sem.h>

#define MAX_SPI_CHANNELS			2

// these are defaults that can be overwritten before init_pio_spi()
#define SPI0_RX_PIN					16					// spi0 rx ( MISO )
#define SPI0_TX_PIN					19					// spi0 tx ( MOSI)
#define SPI0_SCK_PIN				18					// spi0 sclk

#define SPI1_RX_PIN					12					// spi1 rx ( MISO )
#define SPI1_TX_PIN					11					// spi1 tx ( MOSI )
#define SPI1_SCK_PIN				10					// spi1 sclk

#define PICO_NO_PIN					0xFF	

#define	SPI0_MISO_DMA_CHAN			0
#define	SPI0_MOSI_DMA_CHAN			1

#define	SPI1_MISO_DMA_CHAN			2
#define	SPI1_MOSI_DMA_CHAN			3

#define DEFAULT_SPI_BAUD			1000000
#define SPI_BUFFER_SIZE				4096

#define	 PIO_SPI_SCK_CYCLE			4				// pio state machine SPI_CLK has 4 cycles of System SCK 

typedef struct {
    PIO					pio;
    uint				sm;
    uint				offset;
	const pio_program_t	*pPIOprogram;
}pio_spi_inst_t;


typedef struct
{
	pio_spi_inst_t		*spi_HW;
	semaphore_t			doneSemaphore;
	uint8_t				dmaChanNumMISO,
						dmaChanNumMOSI;
	dma_channel_config	dmaChanConfigMosi,
						dmaChanConfigMiso;
	double				spi_baud;			// desired spi sck speed
	uint8_t				gpio_sclk_pin,		// SCK
						gpio_tx_pin,		// MOSI
						gpio_rx_pin,		// MISO
						gpio_cs_pin;		// CS
	uint8_t				chipSelect;			// driver does chip selects, see below **
	uint16_t			rxBufferSize,		// how much data to Rx
						txBufferSize;		// how much data to Tx
	uint8_t				*rxBuffer,			// pointer to Rx buffer
						*txBuffer;			// pointer to Tx buffer
} SPI_CHANNEL;

// ** chipSelect handling
#define  SPI_CHIP_SELECT_NONE		0				// driver does nothing with CS
#define  SPI_CHIP_SELECT_ASSERT		0x01			// driver asserts CS at beginning of transmission, and leaves it
#define  SPI_CHIP_SELECT_DEASSERT	0x02			// driver asserts CS at beginning of transmission, and de-asserts it at end of transmission
#define  SPI_CHIP_SELECT_BOTH		(SPI_CHIP_SELECT_ASSERT | SPI_CHIP_SELECT_DEASSERT )


extern SPI_CHANNEL		*pSpiChannelDescript[MAX_SPI_CHANNELS];

extern bool init_pio_spi(uint8_t _channel_index);
extern void deinit_pio_spi(uint8_t _channel_index);
extern bool start_pio_spi(uint8_t _channel_index );
extern bool isInitialized_pio_spi(uint8_t _channel_index);
