#define NUM 23 // 首先定義LED的數目
int leds[NUM] = {
  D0, D1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15, A0, A1, A2, A3, LED1, LED2, LED3, LED4
};

// 將每個腳位模式設為OUTPUT
void setup() {
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
  }
}

// 五種不同的LED燈號變化模式
void pattern1() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
    delay(100);
  }
}

void pattern2() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }
  delay(500);
}

void pattern3() {
  for(int i = NUM-1; i >= 0; i--){
    digitalWrite(leds[i], HIGH);
    delay(50);
    digitalWrite(leds[i], LOW);
  }
  delay(500);
}

void pattern4() {
  for(int i = 0; i < NUM; i += 2){
    digitalWrite(leds[i], HIGH);
  }
  delay(300);
  for(int i = 0; i < NUM; i += 2){
    digitalWrite(leds[i], LOW);
  }
  delay(300);
}

void pattern5() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    delay(150);
  }
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], LOW);
    delay(150);
  }
  delay(500);
}

void loop() {
  for (int j = 0; j < 2; j++) { // 每個模式重複2次
    pattern1();
    pattern2();
    pattern3();
    pattern4();
    pattern5();
  }
}
