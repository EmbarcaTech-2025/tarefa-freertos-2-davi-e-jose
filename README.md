
# Tarefa: Roteiro de FreeRTOS #2 - EmbarcaTech 2025

Autor: **José Augusto Alves de Moraes e Davi Henrique Vieira Lima**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, Junho de 2025

---

## ⚡ Pinagem

| Componente  | Pino GPIO  |
|-------------|------------|
| SDA (Display Oled)    | 14         |
| SCL (Display Oled)    | 15         |
| Microfone   | 28         |
| Botão A     | 5          |
| Botão B     | 6          |

---

## ⚙️ Como compilar e executar
1. **Primeiramente, clone o repositório com o comando**:
```
  git clone https://github.com/EmbarcaTech-2025/tarefa-freertos-2-davi-e-jose.git
```

2. **Após isso, é necessário adicionar a pasta FreeRTOS ao projeto por meio dos comandos**:
```
cd tarefa-freertos-2-davi-e-jose
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git FreeRTOS
```

3. **Com isso, no VsCode, importe o projeto como um *Pico Project*, apertando o ícone `Import Project`**.

Observação: escolha a versão 2.1.1 do Pico-SDK

4. **Nesta etapa, no terminal, digite os seguintes comandos:**
```
  cd build
  cmake ..
``` 

5. **Após isso, aperte o ícone `Compile Project`** para compilar o projeto.

6. **Conecte o Pico via USB segurando o botão BOOTSEL** e aperte o ícone `Run Project (USB)` para gravar o projeto.
---

## 📈 Resultados esperados ou observados

Ao executar o código, espera-se o seguinte comportamento:

1.  **Inicialização do Sistema**:
  * Após a energização da BitDogLab, o sistema inicializa os periféricos: Display Oled, ADC, DMA e botões.

  * A tarefa para quando o Display está ocioso é criada.

  * O Kernel Scheduler é inicializado.

  * O Display Oled mostra a seguinte mensagem:
    ```
    Monitoramento
    Press A: Temp
    Press B: Mic
    ```
  * Isso indica que, para **monitorar a temperatura interna do microcontrolador**, é necessário apertar o **botão A** e, para **monitorar o nível sonoro do ambiente**, é precisa apertar o **botão B**.


2.  **Monitoramento da Temperatura Interna Microcontrolador (Botão A)**:

  Ao pressionar o **Botão A**, a cada segundo, será exibido a temperatura interna, em °C, do microcontrolador em tempo real.

  Exemplo de exibição no display oled:
  ```
    25 42 C
  ```

  Ao pressionar o **Botão A enquanto está sendo realizado o monitoramento da temperatura**, o display volta a exibir a mensagem original quando ele está ocioso.

  Ao pressionar o **Botão B enquanto está sendo realizado o monitoramento da temperatura**, o sistema passa a realizar o monitoramento do nível sonoro do ambiente.

3.  **Monitoramento do Nível Sonoro do Ambiente (Botão B)**:

  Ao pressionar o **Botão B**, a cada segundo, será exibido o nível sonoro do ambiente, em dB, em tempo real.

  Exemplo de exibição no display oled:
  ```
    60 50 dB
  ```

  Ao pressionar o **Botão B enquanto está sendo realizado o monitoramento da nível sonoro**, o display volta a exibir a mensagem original quando ele está ocioso.

  Ao pressionar o **Botão A enquanto está sendo realizado o monitoramento da nível sonoro**, o sistema passa a realizar o monitoramento da temperatura do microcontrolador.

4.  **Execução Concorrente e Controle Responsivo**:

    * As tarefas funcionam de forma independente e concorrente.

    * A suspensão e retomada das tarefas são imediatas e sem afetar as demais execuções.

    * O sistema se mantém em funcionamento contínuo, respondendo aos comandos dos botões indefinidamente.

---

## 🎥 Vídeo Demonstrativo
Veja o vídeo demonstrativo [aqui](https://youtube.com/shorts/6omBiOSpbXo?feature=share).

## 📜 Licença
GNU GPL-3.0.
