#include <stdint.h> 
#include "hw_spi.h"


#define HSPI_SDCARD SPI2

// Define spi2 pin label
#define SPISD_SC   GPIO_Pin_12
#define SPISD_SCK  GPIO_Pin_13
#define SPISD_MISO GPIO_Pin_14
#define SPISD_MOSI GPIO_Pin_15
#define SPISD_GPIO_PORT  GPIOB

static inline uint8_t SPI_read_8();
static inline void SPI_write_8(uint8_t data);

// SPI peripheral power enable / disable (default off, init() automatically enables)
// send SPI peripheral to sleep
static inline void SPI_poweroff();
// wake SPI peripheral from sleep
static inline void SPI_poweron();

// ######## internal function declarations
static inline void SPI_wait_TX_complete();
static inline uint8_t SPI_is_RX_empty();
static inline void SPI_wait_RX_available();

void SPI_set_prescaler(uint8_t presc)
{
    HSPI_SDCARD->CTLR1 &= ~SPI_CTLR1_BR;
    HSPI_SDCARD->CTLR1 |= SPI_CTLR1_BR & (presc << 3);
}


void SPI_CS()
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	GPIO_InitStructure.GPIO_Pin = SPISD_SC;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( SPISD_GPIO_PORT, &GPIO_InitStructure );
}

void SPI_init()
{

    GPIO_InitTypeDef GPIO_InitStructure={0};
	SPI_InitTypeDef SPI_InitStructure={0};
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE);


	GPIO_InitStructure.GPIO_Pin = SPISD_SCK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( SPISD_GPIO_PORT, &GPIO_InitStructure );


	GPIO_InitStructure.GPIO_Pin = SPISD_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init( SPISD_GPIO_PORT, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = SPISD_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( SPISD_GPIO_PORT, &GPIO_InitStructure );

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init( SPI2, &SPI_InitStructure );
    SPI_Cmd( SPI2, ENABLE );


}

void SPI_begin_8()
{
    HSPI_SDCARD->CTLR1 &= ~(SPI_CTLR1_DFF); // DFF 16bit data-length enable, writable only when SPE is 0
    HSPI_SDCARD->CTLR1 |= SPI_CTLR1_SPE;
}

void SPI_end()
{
    HSPI_SDCARD->CTLR1 &= ~(SPI_CTLR1_SPE);
}

static inline uint8_t SPI_read_8()
{
    return HSPI_SDCARD->DATAR;
}

static inline void SPI_write_8(uint8_t data)
{
    HSPI_SDCARD->DATAR = data;
}

uint8_t SPI_transfer_8(uint8_t data)
{
    SPI_write_8(data);
    SPI_wait_TX_complete();
    asm volatile("nop");
    SPI_wait_RX_available();
    return SPI_read_8();
}

static inline void SPI_poweroff()
{
    SPI_end();
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, DISABLE ); 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, DISABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, DISABLE);
}
static inline void SPI_poweron()
{
   	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE);
}

// ########  small internal function definitions, static inline
static inline void SPI_wait_TX_complete()
{
    while (!(HSPI_SDCARD->STATR & SPI_STATR_TXE))
    {
    }
}
static inline uint8_t SPI_is_RX_empty()
{
    return HSPI_SDCARD->STATR & SPI_STATR_RXNE;
}
static inline void SPI_wait_RX_available()
{
    while (!(HSPI_SDCARD->STATR & SPI_STATR_RXNE))
    {
    }
}
static inline void SPI_wait_not_busy()
{
    while ((HSPI_SDCARD->STATR & SPI_STATR_BSY) != 0)
    {
    }
}
static inline void SPI_wait_transmit_finished()
{
    SPI_wait_TX_complete();
    SPI_wait_not_busy();
}
