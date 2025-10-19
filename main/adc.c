#include "adc.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "esp_random.h"

/** @brief Mutex handle for thread-safe ADC access */
static SemaphoreHandle_t adcMutex = NULL;

/**
 * @brief Read a value from the specified ADC channel
 * 
 * This function simulates reading an ADC value from a hardware channel.
 * It uses a mutex for thread-safe access and introduces a realistic delay
 * to simulate the time required for an actual ADC conversion. The returned
 * value is a combination of the channel number and random jitter to simulate
 * real-world ADC behavior.
 * 
 * The function blocks until the mutex is available, ensuring that only one
 * task can access the ADC hardware at a time. This prevents race conditions
 * and ensures data integrity in multi-threaded environments.
 * 
 * @param channel The ADC channel number to read from (0-based indexing)
 * @return int32_t The simulated ADC reading value composed of:
 *                 - Upper 24 bits: channel number shifted left by 8 bits
 *                 - Lower 8 bits: random value for simulated noise/jitter
 *                 Returns 0 if mutex acquisition fails
 */
int32_t adcGetVal(uint8_t channel)
{
    int32_t val = 0;

    // Attempt to acquire the ADC mutex with infinite timeout
    if(xSemaphoreTake(adcMutex, portMAX_DELAY))
    {
        // Simulate ADC conversion time
        vTaskDelay(pdMS_TO_TICKS(20));

        // Generate simulated ADC value:
        // - Channel ID in upper bits for identification
        // - Random 8-bit value for simulated measurement jitter
        val = (channel << 8) | (esp_random() & 0xFF);

        // Release the mutex to allow other tasks to access ADC
        xSemaphoreGive(adcMutex);
    }
    
    return val;
}

/**
 * @brief Initialize the ADC subsystem
 * 
 * @note This function must be called before any ADC read operations.
 *       Failure to initialize will result in undefined behavior when
 *       calling adcGetVal().
 */
void adcInit(void)
{
    // Create a mutex for ADC access synchronization
    adcMutex = xSemaphoreCreateMutex();
}