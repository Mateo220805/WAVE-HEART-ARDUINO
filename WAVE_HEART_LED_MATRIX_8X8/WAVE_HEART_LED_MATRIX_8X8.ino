#include "LedControl.h"

// Pinout del MAX7219
int DIN = 8;
int CLK = 13;
int CS = 10;
int maxInUse = 1; // Número de controladores MAX7219 en uso

LedControl lc = LedControl(DIN, CLK, CS, maxInUse);

// Corazón representado en una matriz 8x8
byte heart[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
};

void setup() {
  lc.shutdown(0, false);       // Despierta el MAX7219 del modo de ahorro de energía
  lc.setIntensity(0, 8);       // Establece el brillo (0 es mínimo, 15 es máximo)
  lc.clearDisplay(0);          // Limpia la pantalla
}

void loop() {
  drawHeart();
  delay(1000);
  heartBeatAnimation();
  delay(1000);
  heartFadeInOut();
  delay(1000);
  heartScroll();
  delay(1000);
  heartBlink();
  delay(1000);
}

void drawHeart() {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, heart[row]);
  }
}

void heartBeatAnimation() {
  for (int i = 0; i < 2; i++) { // Realiza dos latidos
    lc.setIntensity(0, 0); // Disminuye el brillo para "encoger" el corazón
    delay(150);
    lc.setIntensity(0, 8); // Restablece el brillo para "expandir" el corazón
    delay(150);
  }
}

void heartFadeInOut() {
  for (int i = 0; i < 16; i++) {
    lc.setIntensity(0, i);
    delay(50);
  }
  for (int i = 15; i >= 0; i--) {
    lc.setIntensity(0, i);
    delay(50);
  }
}

void heartScroll() {
  for (int i = 0; i < 8; i++) {
    for (int row = 0; row < 8; row++) {
      lc.setRow(0, row, heart[row] >> i);
    }
    delay(100);
  }
}

void heartBlink() {
  for (int i = 0; i < 2; i++) {
    lc.setRow(0, 0, 0);
    delay(100);
    drawHeart();
    delay(100);
  }
}