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

void menu_message() {
  printf("\nMatrix Led Menu:\n");
  printf("Number - Exibits de number in LEDS\n");
  printf("A - \n");
  printf("B - \n");
  printf("C - \n");
  printf("D - \n");
  printf("# - \n");
  printf("* - \n\n");
}

int main() {

  // Inicializa entradas e saídas.
  stdio_init_all();

  // Inicializa o Keypad
  keypad_init();

  // Inicializa matriz de LEDs NeoPixel.
  npInit(LED_PIN);
  // npClear();

  // Não faz mais nada. Loop infinito.
  while (true) {
    sleep_ms(1000);
  }
}
