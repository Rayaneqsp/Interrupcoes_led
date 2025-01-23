#ifndef MATRIZLEDCONTROL_H
#define MATRIZLEDCONTROL_H

#include <stdint.h> // to uint work

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

void npInit(uint pin);
void npClear();
void brightness();
void changeDrawing();

#endif