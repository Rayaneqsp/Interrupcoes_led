## Funcionamento do Código

Este projeto foi desenvolvido para a **placa BitDogLab** utilizando o microcontrolador **RP2040**. O código controla uma **matriz de LEDs 5x5 WS2812** e um **LED RGB** com base em interações com dois botões. O comportamento do sistema segue as funcionalidades descritas abaixo:

### Funcionalidades:

- **Piscar do LED RGB**:
   - O LED RGB (conectado às GPIOs 11, 12 e 13) pisca continuamente 5 vezes por segundo. O efeito de piscar é realizado alternando o estado do LED vermelho a cada 200ms.

- **Incremento e Decremento com Botões**:
   - **Botão A (GPIO 5)**: Ao pressionar o botão A, o número exibido na matriz de LEDs é **incrementado** em 1, circulando entre 0 e 9.
   - **Botão B (GPIO 6)**: Ao pressionar o botão B, o número exibido na matriz de LEDs é **decrementado** em 1, circulando entre 9 e 0.

- **Exibição de Números na Matriz de LEDs WS2812**:
   - A matriz de LEDs 5x5 WS2812 (conectada à GPIO 7) exibe os números de **0 a 9** de forma digital, com os LEDs acesos de acordo com o padrão de segmentos que formam o número. A exibição é realizada por meio de uma representação binária, onde cada LED corresponde a um segmento de um número.

- **Debouncing de Botões**:
   - O código implementa **debouncing de botões** via software, garantindo que múltiplos acionamentos não sejam registrados devido ao fenômeno de "bouncing" (oscilação do botão ao ser pressionado). Isso é feito verificando o tempo passado desde a última interrupção e ignorando pressões rápidas demais.

### Requisitos de Hardware:

- **Matriz de LEDs WS2812**: Conectada à GPIO 7 (25 LEDs no total).
- **LED RGB**: Conectado às GPIOs 11 (vermelho), 12 (verde) e 13 (azul).
- **Botão A**: Conectado à GPIO 5.
- **Botão B**: Conectado à GPIO 6.

### Fluxo de Funcionamento:

- **Inicialização**:
   - O código configura as GPIOs para o LED RGB, a matriz WS2812, e os botões com resistores pull-up internos. Ele também configura as interrupções para os botões A e B.
   
- **Loop Principal**:
   - Dentro do loop principal (`while (true)`), o LED RGB pisca continuamente e a função `display_number` exibe o número atual na matriz de LEDs.
   - O número exibido é atualizado sempre que um botão é pressionado, incrementando ou decrementando o valor conforme a interação do usuário.

 -**Interrupções de Botões**:
   - As interrupções de GPIO para os botões A e B garantem que o código responda rapidamente às mudanças de estado dos botões, com uma rotina de debouncing aplicada para evitar leituras incorretas.

### Como Usar:

1. Carregue o código na placa BitDogLab com o ambiente de desenvolvimento **VSCode**.
2. Conecte a matriz de LEDs WS2812 e o LED RGB nos pinos especificados.
3. Pressione os botões A e B para incrementar e decrementar os números exibidos na matriz de LEDs.

### Observações:

- **Debouncing**: O código trata o efeito de bouncing nos botões utilizando uma técnica de debouncing via software, que evita múltiplas leituras de um único pressionamento.
- **Exibição de Números**: A exibição de números de 0 a 9 é feita de forma estática, com cada número sendo representado por uma combinação fixa de LEDs acesos na matriz 5x5.

# Autora:
Rayane Queiroz dos Santos Passos

#### Link do video: https://www.dropbox.com/referrals/AADLdKHyjQWB_QiVqVbmLjVpCDlrQ5NASgI?src=global9

