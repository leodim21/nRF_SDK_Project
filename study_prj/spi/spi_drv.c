
#include "spi_drv.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>

#define SPI_NODE	DT_NODELABEL(spi1)
const struct device *const dev = DEVICE_DT_GET(SPI_NODE);

static struct local_s
{
    uint8_t tx_buf[32];
    uint8_t rx_buf[32];
}local;

/**
  **************************************************************************************************
  * @brief      ...
  **************************************************************************************************
**/
void spi_drv_init( void )
{
	if (!device_is_ready(dev)) {
		printk("%s: device not ready.\n", dev->name);
		return;
	}
}

/**
  **************************************************************************************************
  * @brief      ...
  **************************************************************************************************
**/
void spi_drv_write( uint8_t * buf, uint8_t len )
{
	struct spi_config config;
	struct spi_cs_control cs_ctrl = (struct spi_cs_control){
		.gpio = NULL,
		.delay = 0u,
	};

	config.frequency = 8000000;
	config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8);
	config.slave = 0;
	config.cs = &cs_ctrl;
    
    memcpy(local.tx_buf, buf, len);

	struct spi_buf tx_buf[1] = {
		{.buf = local.tx_buf, .len = len},
	};
	struct spi_buf rx_buf[1] = {
		{.buf = local.rx_buf, .len = len},
	};

	struct spi_buf_set tx_set = { .buffers = tx_buf, .count = 1 };
	struct spi_buf_set rx_set = { .buffers = rx_buf, .count = 1 };

	int ret = spi_transceive(dev, &config, &tx_set, &rx_set);
}

/**
  **************************************************************************************************
  * @brief      ...
  **************************************************************************************************
**/
void spi_drv_read(  uint8_t * buf, uint8_t len  )
{
	struct spi_config config;
	struct spi_cs_control cs_ctrl = (struct spi_cs_control){
		.gpio = NULL,
		.delay = 0u,
	};

	config.frequency = 8000000;
	config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8);
	config.slave = 0;
	config.cs = &cs_ctrl;

	struct spi_buf tx_buf[1] = {
		{.buf = local.tx_buf, .len = len},
	};
	struct spi_buf rx_buf[1] = {
		{.buf = buf, .len = len},
	};

	struct spi_buf_set tx_set = { .buffers = tx_buf, .count = 1 };
	struct spi_buf_set rx_set = { .buffers = rx_buf, .count = 1 };

	int ret = spi_transceive(dev, &config, &tx_set, &rx_set);
}

