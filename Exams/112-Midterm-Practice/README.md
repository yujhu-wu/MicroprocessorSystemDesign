# 期中考練習(112學年考古題)

> 微處理機系統 · 上機實作 · [回到目錄](../../README.md)

- **平台**：Andes ADP-CORVETTE-F1開發板 + ACET Shield Board
- **開發環境**：Arduino IDE 1.6.5

以112學年期中考題目作為考前練習，以下為通過驗證的版本。

## 題1：LED兩側飛入、交錯飛離

**題目**：多功能板有8個紅色LED與8個綠色LED，按下BTNt(t = 1~4)時，t個亮燈從兩側飛入、在中間交錯而過、再從兩側飛離(LED全滅)，重複兩次後停止。

[Q1_LED_v1.ino](Q1_LED_v1.ino)

```cpp
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
```

[Q1_LED_v2.ino](Q1_LED_v2.ino)

```cpp
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
```

## 題2-1：按鈕對應七段顯示器數字

**題目**：按鈕1~4分別對應數字1、3、5、7，按下時4個七段顯示器全部顯示相同數字。

[Q2-1_7Seg_Buttons_v1.ino](Q2-1_7Seg_Buttons_v1.ino)

```cpp
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2 // D2 is OK, too

#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                              0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0
                             };
/*const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07}; // 這樣會顯示一個位置一個數字，如:7、5、3、1*/
const byte SEGMENT_SELECT[] = {16, 16, 16, 16};

void setup() {
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  WriteNumberToSegment(3 , -1);
}

/* Main program */
void loop()
{
  /* Update the display with the current counter value */
  if (!digitalRead(BUTTON1)){
    WriteNumberToSegment(3 , 1);
  }

  if (!digitalRead(BUTTON2)){
    WriteNumberToSegment(2 , 3);
  }

  if (!digitalRead(BUTTON3)){
    WriteNumberToSegment(1 , 5);
  }

  if(!digitalRead(BUTTON4)){
    WriteNumberToSegment(0 , 7);
  }
}

// Write a number between 0 and 9 to one of the 4 digits of the display
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO, HIGH);
}
```

[Q2-1_7Seg_Buttons_v2.ino](Q2-1_7Seg_Buttons_v2.ino)

```cpp
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2 // D2 is OK, too

#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                              0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0
                             };
const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07}; // Select digits 1 to 4
int display_number = -1;  // Variable to store the current number to display

void setup() {
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(BUTTON1)) {
    display_number = 1;
  }
  if (!digitalRead(BUTTON2)) {
    display_number = 3;
  }
  if (!digitalRead(BUTTON3)) {
    display_number = 5;
  }
  if (!digitalRead(BUTTON4)) {
    display_number = 7;
  }

  for (int i = 0; i < 4; i++) {
    WriteNumberToSegment(i, display_number);
    delay(5);
  }
}

// Write a number between 0 and 9 to one of the 4 digits of the display
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO, HIGH);
}
```

## 題2-2：數字9兩側飛入、交錯飛出

**題目**：七段顯示器做出數字9從兩側飛入、交錯而過並飛出，之後無數字顯示，動作重複不停止。

[Q2-2_7Seg_FlyIn.ino](Q2-2_7Seg_FlyIn.ino)

```cpp
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2

const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,
                              0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0}; // 0~9 and other symbols
const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07, 0x06, 0x09, 0x00}; // 控制4個顯示位
//0xF6 (0x06) = 1111 0110，0xF9 (0x09) = 1111 1001，只看後面4個數字，數字0表示燈亮的位置

void setup() {
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
}

void loop() {
  WriteNumberToSegment(4, 9);
  delay(1500);
  WriteNumberToSegment(5, 9);
  delay(3000);
  WriteNumberToSegment(4, 9);
  delay(1500);
  WriteNumberToSegment(6, -1);
  delay(1500);
}


// 將數字寫入指定的顯示位置
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO, HIGH);
}
```

