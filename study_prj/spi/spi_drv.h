#ifndef __SPI_DRV_H__
#define __SPI_DRV_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void spi_drv_init( void );
void spi_drv_write( uint8_t * buf, uint8_t len );
void spi_drv_read( uint8_t * buf, uint8_t len );

#endif