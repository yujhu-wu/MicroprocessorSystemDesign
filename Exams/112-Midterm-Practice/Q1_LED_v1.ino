#define NUM 16
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4
int leds[NUM] = {
  D0, D1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15
};

void setup() {
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(BT4, INPUT);
}

// 定義 LED 控制函數
void LedControl(unsigned val) {
  for(int i = 0; i < NUM; i++) {
    if(val & (1 << i)) {
      digitalWrite(leds[i], LOW);  // 點亮 LED
    } else {
      digitalWrite(leds[i], HIGH); // 關閉 LED
    }
  }
}

void loop() {
  if(!digitalRead(BUTTON1)){
    LedPattern(1);
  } else if(!digitalRead(BUTTON2)){
    LedPattern(2);
  } else if(!digitalRead(BUTTON3)){
    LedPattern(3);
  } else if(!digitalRead(BUTTON4)){
    LedPattern(4);
  }
}

// 用於控制不同模式的 LED 燈亮模式
void LedPattern(int group_size) {
  for(int repeat = 0; repeat < 2; repeat++){
    for(int i = 0, j = NUM - 1; i < NUM || j >= 0; i++, j--){
      unsigned val = 0;
      val |= (1 << i) | (1 << j);  // 兩端點亮

      for(int k = 1; k < group_size; k++){
        if(i + k < NUM) val |= (1 << (i + k));  // 點亮左側額外的 LED
        if(j - k >= 0) val |= (1 << (j - k));  // 點亮右側額外的 LED
      }

      LedControl(val);  // 控制 LED
      delay(300);
    }

    // 每次 repeat 後全滅
    LedControl(0x0000);
    delay(300);
  }
}
