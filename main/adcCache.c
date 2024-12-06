#include "adcCache.h"
#include "adc.h"

void adcCacheInit()
{
    // TODO implement this function
}

int32_t adcCacheGetVal(uint8_t channel)
{
    // TODO use a cached value here instead of calling adcGetVal
    return adcGetVal(channel);
}