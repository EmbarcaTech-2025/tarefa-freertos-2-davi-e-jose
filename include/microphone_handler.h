#ifndef MICROPHONE_HANDLER_H
#define MICROPHONE_HANDLER_H

#include "FreeRTOS.h"
#include "task.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#define MIC_CHANNEL 2 // Canal ADC do microfone
#define MIC_ADC_PIN 28 // Pino do ADC
#define ADC_CLOCK_DIV 96.f // Divisor de clock do ADC
#define SAMPLES 200 // Número de amostras 
#define ADC_RESOLUTION (1 << 12)  // Resolução do ADC (12-bit ADC -> 4096 níveis)
#define V_REF 3.3f  // Tensão de referência do ADC
#define MIC_OFFSET 1.65f  // Offset do sinal do microfone (meio da escala de 3.3V)

extern uint dma_channel; // Canal DMA
extern dma_channel_config dma_cfg; // Configuração do DMA
extern uint16_t adc_buffer[SAMPLES]; // Buffer de armazenamento de amostras de ADC

void setup_adc();

void setup_dma();

void sample_mic();

float mic_rms();

float convert_to_dB(float v_rms);

extern TaskHandle_t microphone_task_handle;

void microphone_task(void *pvParameters);
#endif // MICROPHONE_HANDLER_H