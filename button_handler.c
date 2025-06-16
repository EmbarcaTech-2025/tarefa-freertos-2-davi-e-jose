#include "button_handler.h"
#include "hardware/irq.h"
#include <pico/types.h>

absolute_time_t last_press_time_a = 0;
absolute_time_t last_press_time_b = 0;

static void buttons_callback(uint gpio, uint32_t events) {}

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
