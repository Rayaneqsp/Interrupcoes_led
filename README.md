# Interrupcoes_led
Tarefa de interrupções em leds da aula 27/01
## Instruções de Funcionamento

Este projeto utiliza o **Raspberry Pi Pico W** para controlar uma **matriz de LEDs WS2812** e exibir números de 0 a 9. O número exibido pode ser incrementado ou decrementado utilizando dois botões físicos.

### 1. **Configuração do Hardware**
- **LED RGB**: Conecte os pinos do LED RGB aos pinos GPIO 13 (vermelho), GPIO 11 (verde) e GPIO 12 (azul) do Raspberry Pi Pico.
- **Botões**: Conecte os botões físicos aos pinos GPIO 5 e GPIO 6.
- **Matriz WS2812**: Conecte a matriz de LEDs WS2812 ao pino GPIO 7.

### 2. **Funcionamento do Sistema**
- **LED RGB**: O LED RGB pisca a cada 200 ms (frequência de 5Hz) em vermelho.
  
- **Contador numérico**:
  - O número exibido na matriz de LEDs varia de 0 a 9.
  - Ao pressionar o **botão A** (pino GPIO 5), o contador é incrementado e o número correspondente é exibido na matriz de LEDs.
  - Ao pressionar o **botão B** (pino GPIO 6), o contador é decrementado e o número correspondente é exibido na matriz de LEDs.
  
- **Matriz de LEDs**: Cada número (de 0 a 9) é exibido como uma representação de uma matriz 5x5 de LEDs acesos ou apagados.

### 3. **Comportamento do Sistema**
- A cada pressionamento de um botão, o número é exibido na matriz WS2812.
- Quando o contador chega a 9 e o botão A é pressionado, ele retorna a 0.
- Quando o contador chega a 0 e o botão B é pressionado, ele retorna a 9.

Esse sistema oferece uma forma interativa de visualizar números em uma matriz de LEDs, utilizando interrupções para detectar a pressão dos botões e atualizar a exibição da matriz em tempo real.

**Link do vídeo:**
