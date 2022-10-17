#include "pio_spi.h"

#include "spi.pio.h"

///////////////////
// Local variables
///////////////////

static pio_spi_inst_t	pio_spi_0 =
{
	.pio = pio0,
	.sm = 0,
	.pPIOprogram =  &spi_chan0_program
};

static pio_spi_inst_t	pio_spi_1 =
{
	.pio = pio0,
	.sm = 1,
	.pPIOprogram =  &spi_chan1_program
};


// PIO-SPI channel 0 uses pio 0 sm 0  dma channels 0 & 1

static SPI_CHANNEL	spi0Channel =
{
	.spi_HW = &pio_spi_0,
	.dmaChanNumMISO = SPI0_MISO_DMA_CHAN,
	.dmaChanNumMOSI = SPI0_MOSI_DMA_CHAN,
	.spi_baud = DEFAULT_SPI_BAUD,
	.gpio_sclk_pin = SPI0_SCK_PIN,
	.gpio_tx_pin = SPI0_TX_PIN,
	.gpio_rx_pin = SPI0_RX_PIN,
	.gpio_cs_pin = PICO_NO_PIN,
	.gpio_dc_pin = PICO_NO_PIN,
};

// PIO-SPI channel 1 uses pio 0 sm 1  dma channels 2 & 3

static SPI_CHANNEL	spi1Channel =
{
	.spi_HW = &pio_spi_1,
	.dmaChanNumMISO = SPI1_MISO_DMA_CHAN,
	.dmaChanNumMOSI = SPI1_MOSI_DMA_CHAN,
	.spi_baud = DEFAULT_SPI_BAUD,
	.gpio_sclk_pin = SPI1_SCK_PIN,
	.gpio_tx_pin = SPI1_TX_PIN,
	.gpio_rx_pin = SPI1_RX_PIN,
	.gpio_cs_pin = PICO_NO_PIN,
};

// indicates whether or not a pio-spi channel has been initialized
static bool			pioSpiInitialized[MAX_SPI_CHANNELS];



///////////////////
// Global variables
///////////////////

SPI_CHANNEL			*pSpiChannelDescript[MAX_SPI_CHANNELS] = { &spi0Channel, &spi1Channel };		// global pointers to pio-spi channels

/////////////////////////////
// Local function prototypes
/////////////////////////////

static void  __no_inline_not_in_flash_func(dma_isr0)(void);		// PIO-SPI uses DMA IRQ 0


///////////////////
// Initialize SPI 
///////////////////

bool init_pio_spi(uint8_t _channel_index )
{
	SPI_CHANNEL			*_channel_desc = pSpiChannelDescript[_channel_index];
	pio_spi_inst_t		*_pio_spi = _channel_desc->spi_HW;

	uint32_t			sysClock = clock_get_hz(clk_sys);
	double				fBaud;
		
	
	if(_channel_desc == NULL) return false;
	if( pioSpiInitialized[_channel_index] ) return true;		// already initialized

	// create a semaphore to indicate when transfers are done
	sem_init ( &_channel_desc->doneSemaphore, 0, 1 );			// create binary semaphore

	fBaud = sysClock;
	fBaud = fBaud / (_channel_desc->spi_baud * PIO_SPI_SCK_CYCLE );

    _pio_spi->offset = pio_add_program(_pio_spi->pio, _pio_spi->pPIOprogram);

	pio_spi_init ( _pio_spi->pio, _pio_spi->sm, _pio_spi->offset,
                8,					// 8 bits per SPI frame
                fBaud,				// pio clock
                false,				// CPHA = 0
                false,				// CPOL = 0
                _channel_desc->gpio_sclk_pin, 
                _channel_desc->gpio_tx_pin,   
                _channel_desc->gpio_rx_pin  );


	// set up DMA
	_channel_desc->dmaChanConfigMosi = dma_channel_get_default_config(_channel_desc->dmaChanNumMOSI);
	channel_config_set_transfer_data_size(&_channel_desc->dmaChanConfigMosi,DMA_SIZE_8);
	channel_config_set_read_increment(&_channel_desc->dmaChanConfigMosi,true);
	channel_config_set_write_increment(&_channel_desc->dmaChanConfigMosi,false);
	channel_config_set_dreq(&_channel_desc->dmaChanConfigMosi, pio_get_dreq( _channel_desc->spi_HW->pio, _channel_desc->spi_HW->sm, true) );

	_channel_desc->dmaChanConfigMiso = dma_channel_get_default_config(_channel_desc->dmaChanNumMISO);
	channel_config_set_transfer_data_size(&_channel_desc->dmaChanConfigMiso,DMA_SIZE_8);
	channel_config_set_read_increment(&_channel_desc->dmaChanConfigMiso,false);
	channel_config_set_write_increment(&_channel_desc->dmaChanConfigMiso,true);
	channel_config_set_dreq(&_channel_desc->dmaChanConfigMiso, pio_get_dreq(_channel_desc->spi_HW->pio, _channel_desc->spi_HW->sm, false) );

	irq_add_shared_handler(DMA_IRQ_0, dma_isr0, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
	//irq_set_exclusive_handler(DMA_IRQ_0, dma_isr0);

    // start the PIO
	pio_sm_set_enabled(_pio_spi->pio, _pio_spi->sm, true);

	pioSpiInitialized[_channel_index] = true;				// mark this spi as initialized
	return true;
}

//////////////////////
// De-Initialize SPI 
//////////////////////

void deinit_pio_spi(uint8_t _channel_index)
{
	SPI_CHANNEL			*_channel_desc = pSpiChannelDescript[_channel_index];
	pio_spi_inst_t		*_pio_spi = _channel_desc->spi_HW;


	if ( !pioSpiInitialized[_channel_index] ) return;

    // stop the PIO
	pio_sm_set_enabled(_pio_spi->pio, _pio_spi->sm, false);
	pio_remove_program( _pio_spi->pio, _pio_spi->pPIOprogram, _pio_spi->offset );

	// remove the DMA irq
	irq_remove_handler( DMA_IRQ_0, dma_isr0 );

	pioSpiInitialized[_channel_index] = false;				// mark this spi not initialized

	// make all the pins rp2040 spi
	gpio_set_function(_channel_desc->gpio_sclk_pin,GPIO_FUNC_SPI);
	gpio_set_function(_channel_desc->gpio_tx_pin,GPIO_FUNC_SPI);
	gpio_set_function(_channel_desc->gpio_rx_pin,GPIO_FUNC_SPI);

}

//////////////////////////////
// Is SPI Channel Initialized
//////////////////////////////

bool isInitialized_pio_spi(uint8_t _channel_index)
{
	return pioSpiInitialized[_channel_index];
}


//////////////////////////////////////////
// Start SPI transfer
//////////////////////////////////////////

bool start_pio_spi(uint8_t _channel_index )
{
	SPI_CHANNEL			*_channel_desc = pSpiChannelDescript[_channel_index];
	pio_spi_inst_t		*_pio_spi = _channel_desc->spi_HW;
    io_rw_8				*txfifo = (io_rw_8 *) &_pio_spi->pio->txf[_pio_spi->sm];
    io_rw_8				*rxfifo = (io_rw_8 *) &_pio_spi->pio->rxf[_pio_spi->sm];
	volatile uint8_t	_i;
	
	// calculate the pio clock based on desired spiclk speed
	uint32_t sysClock = clock_get_hz(clk_sys);
	double	fBaud = sysClock;
	fBaud = fBaud / (_channel_desc->spi_baud * PIO_SPI_SCK_CYCLE);

	// set the clkdiv & restart it
	pio_sm_set_clkdiv(_pio_spi->pio, _pio_spi->sm, fBaud);
	pio_sm_clkdiv_restart(_pio_spi->pio, _pio_spi->sm);

	// configure the dma
	dma_channel_configure( _channel_desc->dmaChanNumMOSI, &_channel_desc->dmaChanConfigMosi, txfifo, (void *)_channel_desc->txBuffer, _channel_desc->rxBufferSize, false );
	dma_channel_configure( _channel_desc->dmaChanNumMISO, &_channel_desc->dmaChanConfigMiso, (void *)_channel_desc->rxBuffer, rxfifo,  _channel_desc->rxBufferSize, false );
	dma_channel_set_irq0_enabled( _channel_desc->dmaChanNumMISO, true);
	//irq_set_exclusive_handler(DMA_IRQ_0, dma_isr0);
    irq_set_enabled(DMA_IRQ_0, true);

	// see if we should assert CS before transfer
	if ( _channel_desc->chipSelect & SPI_CHIP_SELECT_ASSERT )  
	{
		gpio_put(_channel_desc->gpio_cs_pin,false);		// activate CS
		sleep_us(4ULL);		// delay tiny amount
	}

	sem_reset( &_channel_desc->doneSemaphore, 0);  // clear 'done' semaphore

	// start the DMA
	dma_start_channel_mask( ( 1 <<_channel_desc->dmaChanNumMOSI ) | ( 1 <<_channel_desc->dmaChanNumMISO ));

	// return when done
	return ( sem_acquire_timeout_ms( &_channel_desc->doneSemaphore, 100));
}


///////////////////////
// DMA 0 Interrupt
///////////////////////

static void  __no_inline_not_in_flash_func(dma_isr0)(void)
{
	io_rw_32			_ints0 = dma_hw->ints0;
	SPI_CHANNEL			*_channel_desc = pSpiChannelDescript[ ( _ints0 & (1 << pSpiChannelDescript[0]->dmaChanNumMISO) ) ? 0 : 1 ];

	// use MISO b/c we will always receive at least as many bytes as transmitted
	hw_set_bits( &dma_hw->ints0, (1 << _channel_desc->dmaChanNumMISO) );		// clear the dma int
	hw_clear_bits( &dma_hw->inte0, (1 <<_channel_desc->dmaChanNumMISO));		// disable further dma int for this chan

	// see if we should de-assert CS when transfer is complete
	if ( _channel_desc->chipSelect & SPI_CHIP_SELECT_DEASSERT )  gpio_put(_channel_desc->gpio_cs_pin,true );		// deactivate CS

	// let someone know we're done
	sem_release(  &_channel_desc->doneSemaphore );								// set 'done' semaphore
}

