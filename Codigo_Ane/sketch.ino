#include <Keypad.h>
#include <LedControl.h>

// Configuração da matriz MAX7219
LedControl lc = LedControl(11, 13, 10, 1); // DIN, CLK, CS, número de displays

// Definição do keypad
const byte ROW_NUM    = 4; // Número de linhas
const byte COLUMN_NUM = 4; // Número de colunas

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; // Pinos das linhas
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // Pinos das colunas

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

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
  lc.setIntensity(0, 8);        // Define o brilho (50%)
  lc.clearDisplay(0);           // Limpa a matriz

  Serial.begin(9600);           // Inicializa o monitor serial
}

void loop() {
  char key = keypad.getKey();  // Lê a tecla pressionada

  if (key) { // Se uma tecla foi pressionada
    Serial.println(key);  // Exibe a tecla pressionada no monitor serial
    
    if (key == 'D' || key == 'd') {  // Se a tecla "D" for pressionada
      // Mostra a carinha sorrindo
      showPattern(smileyFace);
      delay(1000); // Pausa de 1 segundo
      
      // Mostra a carinha piscando
      showPattern(smileyEyesClosed);
      delay(1000); // Pausa de 1 segundo
    }
  }
}
