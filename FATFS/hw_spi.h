#ifndef HW_SPI_H
#define HW_SPI_H
#include "debug.h"
#include "ch32v20x_spi.h"

void SPI_init();
void SPI_begin_8();
void SPI_end();
void SPI_CS();
uint8_t SPI_transfer_8(uint8_t data);
void SPI_set_prescaler(uint8_t presc);

#endif
