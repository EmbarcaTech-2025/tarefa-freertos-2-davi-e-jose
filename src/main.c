#include "FreeRTOS.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#include "button_handler.h"
#include "display_oled.h"
#include "microphone_handler.h"
#include "rtos_resources.h"

int main() {
  stdio_init_all();

  setup_oled();
  setup_adc();
  setup_dma();
  init_buttons();
  xTaskCreate(idle_display_task, "IdleDisplay", 256, NULL, 1, NULL);

  vTaskStartScheduler();

  while (1) {
  };
}