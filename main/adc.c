#include "adc.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "esp_random.h"

static SemaphoreHandle_t adcMutex = NULL;

int32_t adcGetVal(uint8_t channel)
{
    int32_t val = 0;

    if(xSemaphoreTake(adcMutex, portMAX_DELAY))
    {
        // Reading the ADC value takes some time
        vTaskDelay(pdMS_TO_TICKS(20)); 

        // Dummy value with simulated jitter
        val = (channel << 8) | (esp_random() & 0xFF);

        xSemaphoreGive(adcMutex);
    }
    return val;
}

void adcInit(void)
{
    adcMutex = xSemaphoreCreateMutex();
}