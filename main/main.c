/**
 * @file main.c
 * @brief Main application file for ADC Cache Exercise
 * 
 * This is the main application file for Exercise 9 of the FH Systemprogrammierung course.
 * It demonstrates the use of an ADC cache system by continuously reading values from
 * multiple ADC channels and calculating performance metrics.
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adcCache.h"
#include "adc.h"
#include "esp_timer.h"

/**
 * @brief FreeRTOS task that continuously reads ADC values and measures performance
 * 
 * @param pvParameters Task parameters (unused, cast to void to suppress warnings)
 */
static void endlessAdcReads(void *pvParameters)
{
    (void)pvParameters;

    for(;;)
    {
        int32_t sum = 0;  // Accumulator for calculating mean value

        // Record start time for performance measurement
        const int64_t start_us = esp_timer_get_time();
        
        // Read values from all ADC channels and accumulate sum
        for(size_t channel = 0; channel < ADC_CACHE_NB_CHANNELS; channel++)
        {
            sum += adcCacheGetVal(channel);
        }
        
        // Calculate elapsed time for all channel reads
        const int64_t difTime_us = esp_timer_get_time() - start_us;

        // Display results: mean value and execution time
        printf("Mean value: %ld (time: %lldus)\n", 
               sum / ADC_CACHE_NB_CHANNELS, difTime_us);

        // Wait 2 seconds before next measurement cycle
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/**
 * @brief Main application entry point
 */
void app_main(void)
{
    // Initialize ADC hardware interface
    adcInit();
    
    // Initialize ADC cache system
    adcCacheInit();
    
    // Create FreeRTOS task for continuous ADC measurements
    // Task parameters: function, name, stack size (2KB), parameters, priority, handle
    xTaskCreate(endlessAdcReads, "endlessAdcReads", 2048, NULL, 5, NULL);
}
