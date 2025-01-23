#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "util/matrizLedControl.h"
#include "util/keypad.h"
#include "util/drawing.h"
#include "pins.h"


void menu_message()
{
  printf("\nMatrix Led Menu:\n");
  printf("Number - Exibits the number animation\n");
  printf("A - Turn off leds\n");
  printf("B - All Leds blue. 100.\n");
  printf("C - All Leds red. 80.\n");
  printf("D - All Leds green. 50.\n");
  printf("# - All Leds white. 20.\n");
  printf("* - \n\n");
}

int main()
{
  // Inicializa entradas e saídas.
  stdio_init_all();
  printf("Init: ALL\n");

  // Inicializa o Keypad
  keypad_init();
  printf("Init: Keypad\n");

  // Inicializa matriz de LEDs NeoPixel.
  npInit(LED_PIN);
  printf("Init: LEDS\n");
  npClear();

  // Loop de ações a serem completadas
  while (true)
  {
    // Get the input from the board
    char press_key = keypad_get_key();
    if (press_key)
      printf("Tecla pressionada: %c\n", press_key);
    switch (press_key)
    {
    case 'A':
      //
      break;
    case 'B':
      //
      break;
    case 'C':
      //
      break;
    case 'D':
      //
      break;
    case '#':
      //
      break;
    case '*':
      //
      break;
    default:
      sleep_ms(100);
    }
  }
}
