#define NUM 16 // 首先定義LED的數目
int leds[NUM] = {0, 1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15};

// 將每個腳位模式設為OUTPUT
void setup() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    if(i>10) continue;
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i],LOW);
    delay(200);
    digitalWrite(leds[i], HIGH);
  }

  for(int i = NUM-1; i >= 0; i--){
    digitalWrite(leds[i], LOW);
    delay(200);
    digitalWrite(leds[i], HIGH);
  }
}
