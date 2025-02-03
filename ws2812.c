#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"  // Biblioteca para controlar os LEDs WS2812

// Definições dos pinos
#define LED_RGB_RED_PIN 13
#define LED_RGB_GREEN_PIN 11
#define LED_RGB_BLUE_PIN 12
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define WS2812_PIN 7

// Variáveis globais
volatile int counter = 0;  // Contador para os números exibidos na matriz
volatile bool button_a_pressed = false;
volatile bool button_b_pressed = false;

// Função para debouncing
bool debounce(uint gpio) {
    static uint32_t last_time = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());
    if (now - last_time < 200) {  // Debounce de 200ms
        return false;
    }
    last_time = now;
    return true;
}

// Função de interrupção para o botão A
void button_a_isr(uint gpio, uint32_t events) {
    if (debounce(gpio)) {
        button_a_pressed = true;
    }
}

// Função de interrupção para o botão B
void button_b_isr(uint gpio, uint32_t events) {
    if (debounce(gpio)) {
        button_b_pressed = true;
    }
}

// Função para piscar o LED RGB vermelho a 5Hz
void blink_led_rgb() {
    static bool led_state = false;
    static uint32_t last_blink_time = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    if (now - last_blink_time >= 200) {  // 200ms = 5Hz
        led_state = !led_state;

        // Controla o LED vermelho: pisca entre ligado e desligado
        gpio_put(LED_RGB_RED_PIN, led_state ? 1 : 0);  // Pisca o LED vermelho

        // Atualiza o tempo do último piscar
        last_blink_time = now;
    }
}

// Função para limpar a tela da matriz WS2812 (desligar todos os LEDs)
void clear_ws2812() {
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, 0);  // Enviar '0' para apagar todos os LEDs
    }
}

void num_0() {
    // Representação do número 0 em uma matriz 4x4 com LEDs vermelhos
    uint8_t vetor[4][4] = {
        {1, 1, 1, 1},  // Primeira linha com LEDs acesos para formar o topo do 0
        {1, 0, 0, 1},  // Segunda linha, laterais acesas
        {1, 0, 0, 1},  // Terceira linha, laterais acesas
        {1, 1, 1, 1}   // Quarta linha com LEDs acesos para formar a base do 0
    };

    // Enviar os dados para a matriz WS2812 (acendendo os LEDs vermelhos conforme a matriz acima)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (vetor[i][j] == 1) {
                // Aqui você vai configurar o LED como vermelho (no caso, é só um exemplo de como fazer isso)
                // O comando abaixo deve ser substituído pela lógica do seu controle de LEDs
                // Caso você utilize PIO para o controle de WS2812, ajuste o código aqui
                // Como exemplo, pode ser algo como:
                pio_sm_put_blocking(pio0, 0, 0xFF0000); // 0xFF0000 representa a cor vermelha em RGB
            } else {
                pio_sm_put_blocking(pio0, 0, 0x000000); // 0x000000 representa a cor apagada (preto)
            }
        }
    }
}


void num_1() {
    uint8_t vetor[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_2() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_3() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_4() {
    uint8_t vetor[5][5] = {
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_5() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}


void num_6() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_7() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_8() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

void num_9() {
    uint8_t vetor[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    for (int i = 0; i < 5; i++) {
        pio_sm_put_blocking(pio0, 0, vetor[i][0]);
        pio_sm_put_blocking(pio0, 0, vetor[i][1]);
        pio_sm_put_blocking(pio0, 0, vetor[i][2]);
        pio_sm_put_blocking(pio0, 0, vetor[i][3]);
        pio_sm_put_blocking(pio0, 0, vetor[i][4]);
    }
}

int main() {
    // Inicialização do hardware
    stdio_init_all();

    // Configuração dos pinos do LED RGB
    gpio_init(LED_RGB_RED_PIN);
    gpio_init(LED_RGB_GREEN_PIN);
    gpio_init(LED_RGB_BLUE_PIN);
    gpio_set_dir(LED_RGB_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_RGB_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_RGB_BLUE_PIN, GPIO_OUT);

    // Configuração dos botões
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);  // Ativa o resistor de pull-up interno
    gpio_pull_up(BUTTON_B_PIN);  // Ativa o resistor de pull-up interno

    // Configuração das interrupções para os botões A e B
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &button_a_isr);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &button_b_isr);

    // Configuração do PIO para os LEDs WS2812
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, 0, offset, WS2812_PIN, 800000, true);

    // Loop principal
    while (true) {
        // Piscar o LED RGB vermelho
        blink_led_rgb();

        // Verificar se o botão A foi pressionado
        if (button_a_pressed) {
            clear_ws2812();  // Limpar a tela antes de exibir o novo número
            switch (counter) {
                case 0: num_0(); break;
                case 1: num_1(); break;
                case 2: num_2(); break;
                case 3: num_3(); break;
                case 4: num_4(); break;
                case 5: num_5(); break;
                case 6: num_6(); break;
                case 7: num_7(); break;
                case 8: num_8(); break;
                case 9: num_9(); break;
            }
            counter = (counter + 1) % 10;  // Incrementar o contador (0-9)
            button_a_pressed = false;
        }

        // Verificar se o botão B foi pressionado
        if (button_b_pressed) {
            clear_ws2812();  // Limpar a tela antes de exibir o novo número
            counter = (counter - 1 + 10) % 10;  // Decrementar o contador (0-9)
            switch (counter) {
                case 0: num_0(); break;
                case 1: num_1(); break;
                case 2: num_2(); break;
                case 3: num_3(); break;
                case 4: num_4(); break;
                case 5: num_5(); break;
                case 6: num_6(); break;
                case 7: num_7(); break;
                case 8: num_8(); break;
                case 9: num_9(); break;
            }
            button_b_pressed = false;
        }
    }

    return 0;
}
