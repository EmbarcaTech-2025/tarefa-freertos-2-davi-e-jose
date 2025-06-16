#include "temperature_handler.h"
#include "display_oled.h"
#include "hardware/adc.h"
#include "projdefs.h"
#include "rtos_resources.h"
#include "task.h"

#define ADC_TEMPERATURE_CHANNEL 4

double temperature[10] = {0};
int tx = 0;

double adc_to_fahrenheit(uint16_t adc_value) {
  const float conversion_factor = 3.3f / (1 << 12);
  double voltage = adc_value * conversion_factor;
  double temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
  return (temperature * 1.8) + 32;
}

double fahrenheit_to_celsius(float fahrenheit) {
  return (fahrenheit - 32) * (5.0 / 9.0);
}

void get_celsius(void *pvParameters) {
  adc_init();
  adc_set_temp_sensor_enabled(true);

  while (true) {
    if (xSemaphoreTake(rMutex, (TickType_t)10) == pdTRUE) {
      adc_select_input(ADC_TEMPERATURE_CHANNEL);
      uint16_t adc_value = adc_read();
      double fahrenheit = adc_to_fahrenheit(adc_value);
      temperature[tx] = fahrenheit_to_celsius(fahrenheit);
      tx = (tx + 1) % 10;
      display_oled(temperature[tx], "C");
      xSemaphoreGive(rMutex);
      vTaskDelay(pdMS_TO_TICKS(50));
    }
  }
}
