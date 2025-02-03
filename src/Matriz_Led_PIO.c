#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "util/matrizLedControl.h"
#include "util/drawing.h"

// Definições dos pinos dos botões
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

// Variáveis globais para controlar o estado atual da animação
int current_animation = 0;
int total_animations = 10; // Total de animações disponíveis

// Função para exibir a mensagem do menu
void menu_message()
{
    printf("\nMatrix Led Menu:\n");
    printf("1 - Ian Antunes\n");
    printf("2 - Matheus Vinicius\n");
    printf("3 - Samuel Canario\n");
    printf("5 - Rayane Queiroz\n");
    printf("6 - Rayane Queiroz\n");
    printf("7 - Rayane Queiroz\n");
    printf("8 - Rayane Queiroz\n");
    printf("9 - Taris Henrique\n");
    printf("Pressione A para avançar para a próxima animação.\n");
    printf("Pressione B para retornar à animação anterior.\n");
}

// Função para limpar os LEDs
void clean_leds()
{
    npClear();
    npWrite();
}

// Função para ajustar a intensidade dos LEDs para 10%
uint32_t dim_color(uint32_t color)
{
    // Desmonta as cores RGB
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    // Aplica 10% de intensidade (multiplicando por 0.1)
    r = (uint8_t)(r * 0.1);
    g = (uint8_t)(g * 0.1);
    b = (uint8_t)(b * 0.1);

    // Recombina as cores com a intensidade reduzida
    return (r << 16) | (g << 8) | b;
}

// Função para iniciar a animação com base no índice
void start_current_animation() {
    switch (current_animation)
    {
        case 0:
            printf("Animação iniciada: Ian Antunes.\n");
            startAnimation(num_0);
            break;
        case 1:
            printf("Animação iniciada: Matheus Vinicius.\n");
            startAnimation(num_1);
            break;
        case 2:
            printf("Animação iniciada: Samuel Canario.\n");
            startAnimation(num_2);
            break;
        case 3:
            break;
        case 4:
            printf("Animação iniciada: Rayane Queiroz.\n");
            startAnimation(num_3);
            break;
        case 5:
            printf("Animação iniciada: Rayane Queiroz.\n");
            startAnimation(num_4);
            break;
        case 6:
            printf("Animação iniciada: Rayane Queiroz.\n");
            startAnimation(num_5);
            break;
        case 7:
            printf("Animação iniciada: Rayane Queiroz.\n");
            startAnimation(num_6);
            break;
        case 8:
            printf("Animação iniciada: Taris Henrique.\n");
            startAnimation(num_7);
            break;
        case 9:
            printf("Animação iniciada: Taris Henrique.\n");
            startAnimation(num_8);
            break;
        case 10:
            printf("Animação iniciada: Taris Henrique.\n");
            startAnimation(num_9);
            break;
        default:
            break;
    }
}

// Função para verificar o estado do botão e mudar a animação
void update_animation()
{
    if (gpio_get(BUTTON_A_PIN) == 0) // Botão A pressionado
    {
        current_animation = (current_animation + 1) % total_animations; // Avança para a próxima animação
        printf("Próxima animação: %d\n", current_animation + 1);
        start_current_animation();
        sleep_ms(500); // Debounce para evitar múltiplos acionamentos
    }
    else if (gpio_get(BUTTON_B_PIN) == 0) // Botão B pressionado
    {
        current_animation = (current_animation - 1 + total_animations) % total_animations; // Retrocede para animação anterior
        printf("Animação anterior: %d\n", current_animation + 1);
        start_current_animation();
        sleep_ms(500); // Debounce para evitar múltiplos acionamentos
    }
}

int main()
{
    // Inicializa entradas e saídas.
    stdio_init_all();
    printf("Init: ALL\n");

    // Inicializa a matriz de LEDs NeoPixel.
    npInit();
    printf("Init: LEDS\n");
    npClear();

    // Configura os pinos dos botões A e B
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);  // Ativa o resistor de pull-up interno
    gpio_pull_up(BUTTON_B_PIN);  // Ativa o resistor de pull-up interno

    // Exibe o menu
    menu_message();

    // Inicia a primeira animação
    start_current_animation();

    // Loop principal
    while (true)
    {
        update_animation(); // Verifica o estado dos botões e atualiza a animação

        // Aguarda um curto período para não sobrecarregar o processador
        sleep_ms(100);
    }

    return 0;
}
