#ifndef TEMPERATURE_100K_H
#define TEMPERATURE_100K_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the ADC channel for thermistor readings.
 */
void thermistor_init(void);

/**
 * @brief Reads the thermistor temperature.
 *
 * @return Temperature in Celsius.
 */
float get_temperature(void);

#ifdef __cplusplus
}
#endif

#endif // TEMPERATURE_100K_H
