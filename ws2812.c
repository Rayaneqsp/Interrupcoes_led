#include <stdio.h> 
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/irq.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/sync.h"
#include "ws2812.pio.h" 

// Definições de pinos 
#define NUM_PIXELS 30           
#define LED_PIN 7                
#define RED_PIN 13              
#define GREEN_PIN 11            
#define BLUE_PIN 12             
#define BUTTON_A_PIN 5       
#define BUTTON_B_PIN 6       

// Variáveis globais para controle do número exibido
volatile int current_number = 0;

// Representações binárias dos números para os LEDs
const uint32_t numbers[10][NUM_PIXELS] = {
    {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0}, // 0
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0}, // 1
    {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0}, // 2 
    {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0}, // 3
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0}, // 4
    {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0}, // 5
    {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0}, // 6
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0}, // 7
    {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0}, // 8
    {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},  // 9
};

// Função de debounce para os botões
void debounce_and_update(uint gpio, uint32_t events) {
    static absolute_time_t last_time = {0};
    
    if (absolute_time_diff_us(last_time, get_absolute_time()) > 200000) {
        if (gpio == BUTTON_A_PIN) {
            current_number = (current_number + 1) % 10; // Incrementa
        } else if (gpio == BUTTON_B_PIN) {
            current_number = (current_number - 1 + 10) % 10; // Decrementa
        }
        last_time = get_absolute_time(); // Atualiza o tempo
    }
}

// Função para exibir o número no display de LEDs
void display_number(PIO pio, uint sm, const uint32_t pattern[]) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t color = pattern[i] ? 0xFF0000 : 0x000000; // Acende ou apaga o LED
        pio_sm_put_blocking(pio, sm, color); // Envia a cor para o LED
    }
}

// Configuração dos LEDs RGB
void setup_rgb_leds() {
    gpio_init(RED_PIN);
    gpio_init(GREEN_PIN);
    gpio_init(BLUE_PIN);
    
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
}

// Configuração dos botões
void setup_buttons() {
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    
    gpio_pull_up(BUTTON_A_PIN); // Ativa o pull-up
    gpio_pull_up(BUTTON_B_PIN); // Ativa o pull-up
}

// Função para piscar o LED RGB
void blink_rgb_led() {
    static absolute_time_t last_blink = {0};
    static bool state = false;
    
    if (absolute_time_diff_us(last_blink, get_absolute_time()) > 100000) {
        gpio_put(RED_PIN, state); // Alterna o estado do LED vermelho
        state = !state; // Troca o estado
        last_blink = get_absolute_time(); // Atualiza o tempo
    }
}

int main() {

    stdio_init_all(); // Inicializa a comunicação serial

    // Inicializa o PIO para controle dos LEDs WS2812
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &ws2812_program);
    uint sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, LED_PIN, 800000, false);

    setup_buttons();  // Configura os botões
    setup_rgb_leds(); // Configura os LEDs RGB

    // Configura interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, debounce_and_update);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, debounce_and_update);

    while (true) {
        blink_rgb_led(); // Pisca o LED RGB
        display_number(pio, sm, numbers[current_number]); // Exibe o número atual
        sleep_ms(100); // Aguarda 100ms antes de repetir
    }

    return 0;
}
