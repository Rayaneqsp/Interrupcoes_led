#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
#include "matrizLedControl.h"
#include "ledStruct.h"
#include "definitions.h"

// Definição do pino dos LEDS.
#define LED_PIN 7

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit()
{

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0)
  {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, LED_PIN, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i)
  {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear()
{
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite()
{
  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < LED_COUNT; ++i)
  {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

/**
 * Troca o desenho dos LEDS sem usar a estrutura pronta.
 */
void matrizLedControl_setAll(uint8_t r, uint8_t g, uint8_t b)
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    npSetLED(i, r, g, b); // Configura cada LED
  }
  npWrite(); // Aplica as mudanças nos LEDs
}

/**
 * Atera o brilho dos LEDS no buffer.
 */
void brightness()
{
  // CODE
}

/**
 * Troca o desenho dos LEDS.
 * Recebe um array do struct npLED_t criado para rgb
 * leia sobre em ledStruct.h
 */
void changeDrawing(const npLED_t newDraw[])
{
  // Coloca os novos valores fornecidos no buffer
  for (size_t i = 0; i < LED_COUNT; i += 5) {
    // Define o limite para os próximos 5 elementos
    size_t limit = (i + 5 <= LED_COUNT) ? i + 5 : LED_COUNT;

    if ((i / 5) % 2 == 0) {
      // Coloca na ordem normal
      for (size_t j = i; j < limit; j++)
      {
        npSetLED(j, newDraw[j].R, newDraw[j].G, newDraw[j].B);
      }
    } else {
      // Coloca na ordem inversa
      for (size_t j = limit; j > i; j--) {
        npSetLED(limit - (j - i), newDraw[j - 1].R, newDraw[j - 1].G, newDraw[j - 1].B);
      }
    }
  }

  // Escreve nos LEDs
  npWrite();
}

/**
 * Realiza uma animação dos LEDS em um intervalo de tempo, usando a mudança de desenhos.
 */
void startAnimation(const npLED_t animation_type[FRAMES][LED_COUNT])
{
  for (size_t i = 0; i < FRAMES; i++) // Frame por frame
  {
    // Passa um frame completo para a função changeDrawing
    changeDrawing(animation_type[i]);
    sleep_ms(1000); // Aguarda 1 segundo antes de mudar para o próximo frame
  }

  // Limpa leds
  npClear();
}