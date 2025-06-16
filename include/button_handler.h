#ifndef BUTTON_HANDLER_H

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#include "pico/stdlib.h"

extern void init_buttons();
static void buttons_callback(uint gpio, uint32_t events);

#endif // !BUTTON_HANDLER_H
