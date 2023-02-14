
#include "adc_drv.h"
#include <zephyr/drivers/adc.h>

#define ADC_NODE            DT_NODELABEL(adc)
#define ADC_RESOLUTION      10
#define ADC_CHANEL          0
#define ADC_PORT            SAADC_CH_PSELN_PSELN_AnalogInput0
#define ADC_REFERENCE       ADC_REF_INTERNAL
#define ADC_GAIN            ADC_GAIN_1_5

static struct local_s
{
    struct adc_channel_cfg ch0_cfg;
    struct adc_sequence    sequence;
    struct device          *adc_dev;
    uint16_t               smpl_buf[1];
}local = {
    .adc_dev                    = DEVICE_DT_GET(ADC_NODE),
    .ch0_cfg.gain               = ADC_GAIN,
    .ch0_cfg.reference          = ADC_REFERENCE,
    .ch0_cfg.acquisition_time   = ADC_ACQ_TIME_DEFAULT,
    .ch0_cfg.channel_id         = ADC_CHANEL,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.ch0_cfg.input_positive     = ADC_PORT,
#endif
};

/**
  **************************************************************************************************
  * @brief      ...
  **************************************************************************************************
**/
void adc_drv_init( void )
{
    int err;

    if(!device_is_ready(local.adc_dev))
    {
        return;
    }

    err = adc_channel_setup(local.adc_dev, &local.ch0_cfg);

    if(err != 0)
    {
        return;
    }
}

/**
  **************************************************************************************************
  * @brief      ...
  **************************************************************************************************
**/
uint16_t adc_drv_read( void )
{
    int err;

    local.sequence.channels       = BIT(ADC_CHANEL);
    local.sequence.buffer         = local.smpl_buf;
    local.sequence.buffer_size    = sizeof(local.smpl_buf);
    local.sequence.resolution     = ADC_RESOLUTION;

    err = adc_read(local.adc_dev, &local.sequence);

    return local.smpl_buf[0];
}