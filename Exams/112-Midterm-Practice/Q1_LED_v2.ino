#define NUM 16
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

int leds[NUM] = {D0, D1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15};

void setup() {
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);  // 初始化所有 LED 為關閉狀態
  }
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(BT4, INPUT);
}

void loop() {
  if (!digitalRead(BUTTON1)) {
    ledPattern(1);
  }
  if (!digitalRead(BUTTON2)) {
    ledPattern(2);
  }
  if (!digitalRead(BUTTON3)) {
    ledPattern(3);
  }
  if (!digitalRead(BUTTON4)) {
    ledPattern(4);
  }
}

void ledPattern(int pattern) {
  for(int repeat = 0; repeat < 2; repeat++) {
    for(int i = 0, j = NUM - 1; i < NUM && j >= 0; i++, j--) {
      lightLeds(i, j, pattern);
      delay(300);
      turnOffLeds(i, j, pattern);
    }
    turnOffAllLeds();
    delay(300);
  }
}

void lightLeds(int i, int j, int pattern) {
  digitalWrite(leds[i], LOW);
  digitalWrite(leds[j], LOW);

  // 根據模式決定點亮幾個 LED
  for (int k = 1; k < pattern; k++) {
    if (i + k < NUM){
      digitalWrite(leds[i + k], LOW);
    }
    if (j - k >= 0) {
      digitalWrite(leds[j - k], LOW);
    }
  }
}

void turnOffLeds(int i, int j, int pattern) {
  digitalWrite(leds[i], HIGH);
  digitalWrite(leds[j], HIGH);

  // 根據模式決定關閉幾個 LED
  for (int k = 1; k < pattern; k++) {
    if (i + k < NUM){
      digitalWrite(leds[i + k], HIGH);
    }
    if (j - k >= 0){
      digitalWrite(leds[j - k], HIGH);
    }
  }
}

void turnOffAllLeds() {
  for (int i = 0; i < NUM; i++) {
    digitalWrite(leds[i], HIGH);  // 關閉所有 LED
  }
}
