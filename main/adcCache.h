#ifndef MAIN_ADC_CACHE_H_
#define MAIN_ADC_CACHE_H_

#include <stdint.h>

#define ADC_CACHE_NB_CHANNELS 10

void adcCacheInit();

int32_t adcCacheGetVal(uint8_t channel);

#endif //  MAIN_ADC_CACHE_H_
