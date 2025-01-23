#include <stdint.h>
#include "ledStruct.h"
#include "pins.h"

npLED_t draw_type_B[LED_COUNT];
npLED_t draw_type_C[LED_COUNT];
npLED_t draw_type_D[LED_COUNT];
npLED_t draw_type_TAG[LED_COUNT];

npLED_t draw_type_1[LED_COUNT];
npLED_t draw_type_2[LED_COUNT];
npLED_t draw_type_3[LED_COUNT];
npLED_t draw_type_4[LED_COUNT];
npLED_t draw_type_5[LED_COUNT];
npLED_t draw_type_6[LED_COUNT];
npLED_t draw_type_7[LED_COUNT];
npLED_t draw_type_8[LED_COUNT];
npLED_t draw_type_9[LED_COUNT];

void draws_init()
{
    // Init Drawing of button B
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        draw_type_B[i].B = 255;
    }

    // Init Drawing of button C
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        draw_type_C[i].R = 255;
    }

    // Init Drawing of button D
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        draw_type_D[i].G = 255;
    }

    // Init Drawing of button #
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        draw_type_TAG[i].B = 255;
        draw_type_TAG[i].R = 255;
        draw_type_TAG[i].G = 255;
    }
}
