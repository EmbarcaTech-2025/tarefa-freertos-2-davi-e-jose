#ifndef DISPLAY_OLED_H
#define DISPLAY_OLED_H
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/ssd1306_i2c.h"

extern const uint I2C_SDA; // Pino SDA do I2C
extern const uint I2C_SCL; // Pino SCL do I2C
extern uint8_t ssd[ssd1306_buffer_length]; // Buffer do display OLED

void setup_oled();

void display_oled(float value, char unit[2]);

void display_oled_idle();

void idle_display_task(void *params);
#endif // DISPLAY_OLED_H