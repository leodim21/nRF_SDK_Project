
#include "adc_drv.h"
#include <zephyr/drivers/adc.h>

#define ADC_NODE            DT_NODELABEL(adc)
#define ADC_RESOLUTION      10
#define ADC_CHANEL          0
#define ADC_PORT            SAADC_CH_PSELN_PSELN_AnalogInput0
#define ADC_REFERENCE       ADC_REF_INTERNAL
#define ADC_GAIN            ADC_GAIN_1_5

struct adc_channel_cfg ch0_cfg = {
    .gain               = ADC_GAIN,
    .reference          = ADC_REFERENCE,
    .acquisition_time   = ADC_ACQ_TIME_DEFAULT,
    .channel_id         = ADC_CHANEL,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive     = ADC_PORT,
#endif
};

uint16_t smpl_buf[1];
struct adc_sequence sequence = {
    .channels       = BIT(ADC_CHANEL),
    .buffer         = smpl_buf,
    .buffer_size    = sizeof(smpl_buf),
    .resolution     = ADC_RESOLUTION,
};

static const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);

void adc_drv_init( void )
{
    int err;

    if(!device_is_ready(adc_dev))
    {
        return;
    }

    err = adc_channel_setup(adc_dev, &ch0_cfg);

    if(err != 0)
    {
        return;
    }
}

uint16_t adc_drv_read( void )
{
    int err;

    err = adc_read(adc_dev, &sequence);

    return smpl_buf[0];
}