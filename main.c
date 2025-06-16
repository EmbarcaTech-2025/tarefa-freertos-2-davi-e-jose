#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"

#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#define MIC_CHANNEL 2 // Canal ADC do microfone
#define MIC_ADC_PIN 28 // Pino do ADC
#define ADC_CLOCK_DIV 96.f // Divisor de clock do ADC
#define SAMPLES 200 // Número de amostras 
#define ADC_RESOLUTION (1 << 12)  // Resolução do ADC (12-bit ADC -> 4096 níveis)
#define V_REF 3.3f  // Tensão de referência do ADC
#define MIC_OFFSET 1.65f  // Offset do sinal do microfone (meio da escala de 3.3V)

uint dma_channel; // Canal DMA
dma_channel_config dma_cfg; // Configuração do DMA
uint16_t adc_buffer[SAMPLES]; // Buffer de armazenamento de amostras de ADC

// Função para configuração do ADC
void setup_adc(){
  adc_gpio_init(MIC_ADC_PIN); // Inicialização do pino como ADC
  adc_init(); // Inicialização do módulo ADC

  adc_select_input(MIC_CHANNEL); // Seleção do canal de entrada do ADC
  adc_fifo_setup(true, true, 1, false, false); // Configuração do FIFO
  adc_set_clkdiv(ADC_CLOCK_DIV); // Definição do divisor de Clock
}

// Função para configuração do DMA para obteção de dados do ADC
void setup_dma(){
  // Requisição de um canal DMA disponível
  dma_channel = dma_claim_unused_channel(true);

  // Configuração padrão para o canal DMA 
  dma_cfg = dma_channel_get_default_config(dma_channel);

  // Definição do tamanho da transferência de dados (16 bits)
  channel_config_set_transfer_data_size(&dma_cfg, DMA_SIZE_16);

  // Desativação do incremento do endereço de leitura
  channel_config_set_read_increment(&dma_cfg, false);

  // Ativação do incremento do endereço de escrita 
  channel_config_set_write_increment(&dma_cfg, true);

  // Definição do gatilho da transferência DMA como o ADC
  channel_config_set_dreq(&dma_cfg, DREQ_ADC);
}

// Função para coletar amostras do microfone via DMA
void sample_mic() {
    adc_fifo_drain(); // Esvaziamendo do FIFO do ADC
    adc_run(false); // Desativação do ADC

    dma_channel_configure(dma_channel, &dma_cfg, adc_buffer, &(adc_hw->fifo), SAMPLES, true); // Configuração do canal DMA
    
    adc_run(true); // Ativação do ADC
    dma_channel_wait_for_finish_blocking(dma_channel); // Aguardo da conclusção da transferência DMA
    adc_run(false); // Desativação do ADC
}

// Função para calcular a potência RMS do sinal do microfone
float mic_rms() {
  float sum_sq = 0.0f;

  // Percorre as amostras coletadas 
  for (uint i = 0; i < SAMPLES; ++i) {
    float voltage = (adc_buffer[i] * V_REF / ADC_RESOLUTION) - MIC_OFFSET;  // Conversão ADC para tensão (V)
    sum_sq += voltage * voltage;  // Soma dos quadrados
  }

  float rms = sqrt(sum_sq / SAMPLES);  // Cálculo RMS
  return rms;
}

// Função para converter o sinal RMS para dB
float convert_to_dB(float v_rms) {
  float ref_voltage = 0.001f;  // 1mV de referência para conversão dB
  if (v_rms <= 0) return -100.0f;  // Tratamento de Excessão (v_rms <= 0)
    
  return 20.0f * log10f(v_rms / ref_voltage);  // Cálculo para conversão para dB
}

TaskHandle_t microphone_task_handle = NULL;
void microphone_task() {
  while (1) {
    sample_mic(); // Coleta de amostras do microfone via DMA
    float v_rms = mic_rms(); // Cálculo da potência RMS
    float dB = convert_to_dB(v_rms); // Conversão para dB
    vTaskDelay(pdMS_TO_TICKS(1000)); // Atraso de 1 segundo
  }
}

int main() {
  stdio_init_all();
  setup_adc(); 
  setup_dma(); 

  xTaskCreate(microphone_task, "Microphone_Task", 256, NULL, 1, &microphone_task_handle);

  vTaskStartScheduler();

  while(1){};
}