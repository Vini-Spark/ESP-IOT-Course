#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "temperature_100k.h"  // Include your new header

static const char *TAG = "MAIN";

// Function to check room temperature
void room_temperature_task(void)
{
    while (1) {
        float temperature = get_temperature();
        ESP_LOGI(TAG, "Room temperature: %.2f°C", temperature);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void app_main(void)
{
    // Initialize the thermistor (ADC configuration, etc.)
    thermistor_init();

    // Create a task to check the room temperature
    xTaskCreate(&room_temperature_task, // Task function
                "temperature_task",     // Task name
                2048,                   // Stack size (bytes)
                NULL,                   // Task parameters
                1,                      // Task priority
                NULL);                  // Task handle

    
}