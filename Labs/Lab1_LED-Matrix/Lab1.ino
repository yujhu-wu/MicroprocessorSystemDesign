#define NUM 15 // 定義 LED 的數量
int leds[NUM] = {
  D0, D1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15
};

// 將每個腳位模式設為 OUTPUT
void setup() {
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
  }
}

// 定義不同的 LED 控制模式
void LedControl(unsigned val) {
  for (int i = 0; i < NUM; i++) {
    if (val & (1 << (i % 16))) {
      digitalWrite(leds[i], LOW);  // 點亮 LED
    } else {
      digitalWrite(leds[i], HIGH); // 關閉 LED
    }
  }
}

// 5種 LED 燈號變化模式，每種模式重複2次
void loop() {
  // 模式 1: 所有 LED 交替點亮
  for (int repeat = 0; repeat < 2; repeat++) {
    LedControl(0xAAAA);
    delay(400);
    LedControl(0x5555);
    delay(400);
  }

  // 模式 2: 所有 LED 閃爍
  for (int repeat = 0; repeat < 2; repeat++) {
    LedControl(0xFFFF); // 所有 LED 點亮
    delay(300);
    LedControl(0x0000); // 所有 LED 關閉
    delay(300);
  }

  // 模式 3: 前半部分和後半部分燈交替閃爍
  int firstHalf = 0b0000000001111111; // 前8個LED
  int secondHalf = 0b1111111110000000; // 後8個LED

  for (int repeat = 0; repeat < 2; repeat++) {
    // 前半部分點亮，後半部分熄滅
    LedControl(firstHalf);
    delay(300);
    // 後半部分點亮，前半部分熄滅
    LedControl(secondHalf);
    delay(300);
  }

  // 模式 4: 每三個一組閃爍
  LedControl(0x0000); // 所有 LED 關閉
  for (int repeat = 0; repeat < 2; repeat++) {
    for(int i = 0; i < NUM; i+=3){
      digitalWrite(leds[i], LOW);
      digitalWrite(leds[i+1], LOW);
      digitalWrite(leds[i+2], LOW);
      delay(300);
      digitalWrite(leds[i], HIGH);
      digitalWrite(leds[i+1], HIGH);
      digitalWrite(leds[i+2], HIGH);
    }
  }

  // 模式 5:由左到右依序點亮不熄滅，再由右到左依序熄滅
  for (int repeat = 0; repeat < 2; repeat++) {
    for (int i = NUM - 1; i >= 0; i--) {
      digitalWrite(leds[i], LOW);
      delay(80);
    }
    for (int i = 0; i < NUM; i++) {
      digitalWrite(leds[i], HIGH);
      delay(80);
    }
  }
}
