#ifndef PINS_H
#define PINS_H

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Numer of Rows and collumns
#define ROWS 4
#define COLS 4

// KEYPAD GPIO
const uint8_t row_pins[ROWS] = {16, 17, 18, 19};
const uint8_t col_pins[COLS] = {20, 21, 22, 26};

#endif