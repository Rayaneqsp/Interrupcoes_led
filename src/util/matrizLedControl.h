#ifndef MATRIZLEDCONTROL_H
#define MATRIZLEDCONTROL_H


#include <stdint.h> 
#include "ledStruct.h"
#include "definitions.h"

void npInit(); 
void npClear(); 
void npWrite(); 
void changeDrawing(const npLED_t newDraw[]); 
void matrizLedControl_setAll(uint8_t r, uint8_t g, uint8_t b);
void startAnimation(const npLED_t num_[FRAMES][LED_COUNT]);
void apply_brightness(int brightness);
#endif