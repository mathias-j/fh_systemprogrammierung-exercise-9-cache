#ifndef MAIN_ADC_H_
#define MAIN_ADC_H_

#include <stdint.h>

int32_t adcGetVal(uint8_t channel);
void adcInit(void);

#endif // MAIN_ADC_H_
