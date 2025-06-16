#ifndef RTOS_RESOURCES
#define RTOS_RESOURCES

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

typedef enum state_t { IDLE, MIC, TEMP } state_t;

extern state_t state;
extern SemaphoreHandle_t rMutex;
extern TaskHandle_t mic_handle;
extern TaskHandle_t temp_handle;

#endif // !RTOS_RESOURCES
