#define NUM 23 // 首先定义 LED 的数量
int leds[NUM] = {
  D0, D1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15
};

// 将每个脚位模式设为 OUTPUT
void setup() {
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
  }
}

// 虽然 A3、A2、A1、A0 是类比脚位，
// 但也可以把它当做数字脚位使用。

void loop() {
  // 执行 LED 控制
  LedControl(0xAAAA);
  delay(200);
  LedControl(0x5555);
  delay(200);
}

void LedControl(unsigned val) {
  for (int i = 0; i < NUM; i++) {
    // 根据掩码控制 LED
    if (val & (1 << (i % 16))) {
      digitalWrite(leds[i], LOW);  // 点亮 LED
    } else {
      digitalWrite(leds[i], HIGH); // 关闭 LED
    }
  }
}
