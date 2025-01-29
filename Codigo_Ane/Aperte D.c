#include <LedControl.h>

// Configuração da matriz MAX7219
LedControl lc = LedControl(11, 13, 10, 1); // DIN, CLK, CS, número de displays

// Padrões para as expressões faciais
byte smileyFace[8] = {
  0b00111100, //   ****
  0b01000010, //  *    *
  0b10100101, // * *  * *
  0b10000001, // *      *
  0b10100101, // * *  * *
  0b10011001, // *  **  *
  0b01000010, //  *    *
  0b00111100  //   ****
};

byte smileyEyesClosed[8] = {
  0b00111100, //   ****
  0b01000010, //  *    *
  0b10100101, // * *  * *
  0b10000001, // *      *
  0b10111101, // * **** *
  0b10000001, // *      *
  0b01000010, //  *    *
  0b00111100  //   ****
};

// Função para mostrar um padrão na matriz
void showPattern(byte pattern[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, pattern[row]); // Desenha linha por linha
  }
}

void setup() {
  lc.shutdown(0, false);       // Liga a matriz
  lc.setIntensity(0, 8);       // Define o brilho (50%)
  lc.clearDisplay(0);          // Limpa a matriz
}

void loop() {
  // Mostra a carinha sorrindo
  showPattern(smileyFace);
  delay(1000); // Pausa de 1 segundo
  
  // Mostra a carinha piscando
  showPattern(smileyEyesClosed);
  delay(1000); // Pausa de 1 segundo
}

