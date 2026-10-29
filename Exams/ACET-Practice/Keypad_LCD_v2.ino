#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte row = 0, col = 0;

const byte rowPins[] = {10, 11, 12, 13};
const byte colPins[] = {A0, A1, A2, A3};
const byte keymap[4][4] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12},
  {13, 14, 15, 16}
};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.noCursor();
}

void loop() {
  byte keyIndex = 0;
  lcd.setCursor(0, 0);
  if (keyscan(keyIndex)) {
    lcd.clear();
    lcd.print(keyIndex);
  }
}

bool keyscan(byte &keyIndex) {
  for (byte c = 0; c < 4; c++) {
    digitalWrite(colPins[c], LOW);
    delayMicroseconds(100);
    for (byte r = 0; r < 4; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        keyIndex = keymap[r][c];
        digitalWrite(colPins[c], HIGH);
        return true;
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
  return false;
}
