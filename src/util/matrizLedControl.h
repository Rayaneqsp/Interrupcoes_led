#ifndef MATRIZLEDCONTROL_H
#define MATRIZLEDCONTROL_H


#include <stdint.h> // to uint work
#include "ledStruct.h"
#include "definitions.h"

void npInit(); // Init the LED matriz pin
void npClear(); // Clear the matriz buffer
void npWrite(); // Write the buffer in the LEDS
void changeDrawing(const npLED_t newDraw[]); // Change the LEDS colors based on 25(R,G,B) array.
void matrizLedControl_setAll(uint8_t r, uint8_t g, uint8_t b);
void startAnimation(const npLED_t num_[FRAMES][LED_COUNT]);
void apply_brightness(int brightness);
#endif