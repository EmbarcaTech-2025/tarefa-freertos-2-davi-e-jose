#include "button_handler.h"
#include "display_oled.h"
#include "hardware/adc.h"
#include "hardware/irq.h"
#include "microphone_handler.h"
#include "rtos_resources.h"
#include "temperature_handler.h"
#include <pico/stdlib.h>
#include <string.h>

absolute_time_t last_press_time_a = 0;
absolute_time_t last_press_time_b = 0;

state_t state = IDLE;
TaskHandle_t mic_handle = NULL;
TaskHandle_t temp_handle = NULL;

static void buttons_callback(uint gpio, uint32_t events) {
  if (gpio == 5) {
    if (absolute_time_diff_us(last_press_time_a, get_absolute_time()) >
        200000) {
      last_press_time_a = get_absolute_time();
      if (state == TEMP) {
        vTaskDelete(temp_handle);
        state = IDLE;
        display_oled_idle();
        // Placeholder pra indicar que não está executando uma tarefa
        return;
      }

      adc_select_input(ADC_TEMPERATURE_CHANNEL);
      if (state != IDLE)
        vTaskDelete(mic_handle);

      xTaskCreate(get_celsius, "Temp Read", 256, NULL, 1, &temp_handle);
      state = TEMP;
    }
  } else if (gpio == 6) {
    if (absolute_time_diff_us(last_press_time_b, get_absolute_time()) >
        200000) {
      last_press_time_b = get_absolute_time();

      if (state == MIC) {
        vTaskDelete(mic_handle);
        state = IDLE;
        display_oled_idle();
        // Placeholder pra indicar que não está executando uma tarefa
        return;
      }

      adc_select_input(MIC_CHANNEL); // Seleção do canal de entrada do ADC
      if (state != IDLE)
        vTaskDelete(temp_handle);

      xTaskCreate(microphone_task, "Mic Read", 256, NULL, 1, &mic_handle);
      state = MIC;
    }
  }
}

void init_buttons() {
  gpio_init(BUTTON_A_PIN);
  gpio_init(BUTTON_B_PIN);

  gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
  gpio_set_dir(BUTTON_B_PIN, GPIO_IN);

  gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true,
                                     buttons_callback);
  gpio_set_irq_enabled(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true);

  gpio_pull_up(BUTTON_A_PIN);
  gpio_pull_up(BUTTON_B_PIN);
}
