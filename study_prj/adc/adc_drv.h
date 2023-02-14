#ifndef __ADC_DRV_H__
#define __ADC_DRV_H__

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

void     adc_drv_init( void );
uint16_t adc_drv_read( void );

#endif