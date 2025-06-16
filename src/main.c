#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "display_oled.h"
#include "temperature_handler.h"  
#include "microphone_handler.h"

int main() {
  stdio_init_all();

  setup_oled();
  setup_adc();
  setup_dma();

  vTaskStartScheduler();

  while(1){};
}