#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>

// Custom libraries
#include "temperature_100k.h"

// Constants and configuration
#define DEFAULT_VREF         3300    // Assumed VCC in mV (3.3V)
#define ADC_MAX              4095    // For 12-bit ADC
#define NO_OF_SAMPLES        64      // Number of samples for multisampling

// Voltage divider configuration:
// Assuming: VCC ---[10k resistor]---+---[100k NTC]--- GND
#define SERIES_RESISTOR      10000   // 10 kΩ resistor
#define NOMINAL_RESISTANCE   100000  // 100 kΩ thermistor at 25°C
#define NOMINAL_TEMPERATURE  25      // 25°C in Celsius
#define BETA_COEFFICIENT     3950    // Beta coefficient for your thermistor

static const char *TAG = "THERMISTOR";

/**
 * @brief Configures the ADC channel used for thermistor measurements.
 */
void thermistor_init(void)
{
    // ADC1 channel 4 corresponds to GPIO32 on ESP32.
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
}

/**
 * @brief Reads the thermistor voltage, calculates its resistance, and then converts that to temperature.
 *
 * @return Temperature in Celsius.
 */
float get_temperature(void)
{
    uint32_t adc_reading = 0;

    // Multisampling to reduce noise
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        adc_reading += adc1_get_raw(ADC1_CHANNEL_4);
    }
    adc_reading /= NO_OF_SAMPLES;

    // Convert ADC reading to voltage (mV)
    uint32_t voltage = (adc_reading * DEFAULT_VREF) / ADC_MAX;

    // Avoid division by zero in case voltage equals VREF
    if (voltage >= DEFAULT_VREF) {
        ESP_LOGW(TAG, "Voltage reading equals or exceeds VREF, check wiring.");
        return -1000.0f;  // Return a clearly out-of-range value
    }

    // Calculate the thermistor resistance using the voltage divider formula:
    // V_out = VCC * (R_NTC / (R_series + R_NTC))  =>  R_NTC = R_series * (V_out / (VCC - V_out))
    float thermistorResistance = SERIES_RESISTOR * ((float)voltage / (DEFAULT_VREF - voltage));

    // Calculate temperature in Kelvin using the Beta parameter equation:
    // 1/T = 1/T0 + (1/Beta)*ln(R_NTC/R0)
    float temperatureK = 1.0f / ( (1.0f / (NOMINAL_TEMPERATURE + 273.15f)) +
                          (1.0f / BETA_COEFFICIENT) * log(thermistorResistance / NOMINAL_RESISTANCE) );
    float temperatureC = temperatureK - 273.15f;

    ESP_LOGI(TAG, "ADC Raw: %lu, Voltage: %lu mV, R_NTC: %.2f Ω, Temp: %.2f °C",
             (unsigned long)adc_reading, (unsigned long)voltage, thermistorResistance, temperatureC);

    return temperatureC;
}
