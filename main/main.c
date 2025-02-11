#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "temperature_100k.h"  // Include your new header

static const char *TAG = "MAIN";

void app_main(void)
{
    // Initialize the thermistor (ADC configuration, etc.)
    thermistor_init();

    while (1) {
        float temperature = get_temperature();
        ESP_LOGI(TAG, "Room Temperature: %.2f °C", temperature);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}