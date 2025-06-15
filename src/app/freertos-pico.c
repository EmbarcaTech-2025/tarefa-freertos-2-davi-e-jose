#include "pico/stdio.h"
#include "rtos_resources.h"
#include <stdio.h>

int main() {
  stdio_init_all();

  rMutex = xSemaphoreCreateMutex();

  if (rMutex != NULL) {
    while (true) {
      printf("Hello, World!\n");
    }
  }
}
