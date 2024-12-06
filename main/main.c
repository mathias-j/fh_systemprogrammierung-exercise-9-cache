/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adcCache.h"
#include "adc.h"
#include "esp_timer.h"

static void endlessAdcReads(void *pvParameters)
{
    (void)pvParameters;

    for(;;)
    {
        int32_t sum = 0;

        const int64_t start_us = esp_timer_get_time();
        for(size_t channel=0; channel<ADC_CACHE_NB_CHANNELS; channel++)
        {
            sum += adcCacheGetVal(channel);
        }
        const int64_t difTime_us = esp_timer_get_time() - start_us;

        printf("Mean value: %ld (time: %lldus)\n", sum / ADC_CACHE_NB_CHANNELS,
            difTime_us);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    adcInit();
    adcCacheInit();
    xTaskCreate(endlessAdcReads, "endlessAdcReads", 2048, NULL, 5, NULL);
}
