#ifndef TEMPERATURE_HANDLER_H
#define TEMPERATURE_HANDLER_H

#include <stdint.h>

#define ADC_TEMPERATURE_CHANNEL 4

extern double temperature;

extern void get_celsius(void *pvParameters);

#endif // !TEMPERATURE_HANDLER_H
