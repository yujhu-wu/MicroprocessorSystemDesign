# 課堂練習與加分題

> 微處理機系統 · 上機實作 · [回到目錄](../../README.md)

- **平台：** Andes ADP-CORVETTE-F1 開發板 + ACET Shield Board
- **開發環境：** Arduino IDE 1.6.5

課堂上的即時練習與加分題。

## 0910：5 種 LED 燈號變化

**題目：** 以 LED 陣列做出 5 種燈號變化模式（Lab 1 的課堂練習版）。

[0910_LED_5Patterns.ino](0910_LED_5Patterns.ino)

```cpp
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
```

## 0910 加分題 1：奇偶燈交替亮

**題目：** 讓 LED 奇數燈與偶數燈交替點亮。

[0910_Bonus1_OddEven.ino](0910_Bonus1_OddEven.ino)

```cpp
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
```

## 1001 加分題 2：四個數字常亮在七段顯示器

**題目：** 在 4 位數七段顯示器上同時常亮顯示 4 個數字（例：0930）。

[1001_Bonus2_4Digits.ino](1001_Bonus2_4Digits.ino)

```cpp
/* Define shift register pins used for seven segment display */
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2 // D2 is OK, too

const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                              0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0
                             };

const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07}; // Select digits 1 to 4
int array[4] = {0, 9, 3, 0}; // Display "0930"

void setup() {
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
}

void loop() {
  // Continuously display the digits 0, 9, 3, 0
  for (int i = 0; i < 4; i++) {
    WriteNumberToSegment(i, array[i]);
  }
}

// Write a decimal number between 0 and 9 to one of the 4 digits of the display
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO, HIGH);
}
```

## 1001：按鍵掃描改寫

**題目：** 將 4×4 按鍵掃描（keyscan）改寫成迴圈形式，並將按下的數字顯示在七段顯示器上。

[1001_KeyScan_7Seg.ino](1001_KeyScan_7Seg.ino)

```cpp
//要求：幫我把 keyscan的地方用for迴圈做四次 ，但a的值要可以自己設定
/* Define shift register pins used for seven segment display */
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2 // D2 is OK, too
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4
#define BUTTON_A0 A0
#define BUTTON_A1 A1
#define BUTTON_A2 A2
#define BUTTON_A3 A3
char KeyValue[] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
byte Row = 0, Col = 0;
/* Segment byte maps for numbers 0 to 9 , A, b , C, d, E, F*/ /*MSB: dp g f e d c b a*/;
const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                              0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0
                             };
const byte DP = 0x80; // Digit Point
int array[4] = {16, 16, 16, 16};
int a; // number of the button which is pushed

/* Byte maps to select digit 1 to 4 */ // E: 1110 D: 1101 B: 1011 7: 0111 // the 0's place
const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07}; // {0xFE,0xFD,0xFB,0xF7}; is OK, too.
void setup () { /* Set DIO pins to outputs */

  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)

  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D) // (A, B, C, D) is correct.
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

}

/* Main program */
void loop() {
  bool keypressed = false;
  //scan col1
  for (int i = 0; i < 4; i++) {
    WriteNumberToSegment(i, array[i]);
    delay(1);
  }
  if (keyscan()) {
    shift();
    delay(200);
  }
  if (! digitalRead(BUTTON1)) { //左到右
    for (int i = 3; i >= 0; i--) {
      for (int j = 0; j < 4; j++) {
        WriteNumberToSegment(j, array[i]);
        delay(300);
      }
      WriteNumberToSegment(0, 16);
      delay(500);
    }

  }
  if (! digitalRead(BUTTON2)) { //右到左
    for (int i = 0; i < 4; i++) {
      for (int j = 3; j >= 0; j--) {
        WriteNumberToSegment(j, array[i]);
        delay(300);
      }
      WriteNumberToSegment(3, 16);
      delay(500);
    }
  }
}
//先判斷按的那個 button 在第幾行再判斷第幾列,然後用 a 紀錄那個 button 所代表的數字,接著用 keypressed 判斷是 true or false 然後回傳。
bool keyscan() {
    bool keypressed = false;

    for (int col = 0; col < 4; col++) {
        digitalWrite(A0, col == 0 ? LOW : HIGH);
        digitalWrite(A1, col == 1 ? LOW : HIGH);
        digitalWrite(A2, col == 2 ? LOW : HIGH);
        digitalWrite(A3, col == 3 ? LOW : HIGH);
        delayMicroseconds(100);

        for (int row = 0; row < 4; row++) {
            if (digitalRead(10 + row) == LOW) {
                Col = col + 1; // Adjust column index (1-4)
                Row = row + 1; // Adjust row index (1-4)
                a = col * 4 + row; // Calculate button index
                keypressed = true;
                return keypressed;
            }
        }
    }

    return false;
}

//位移陣列內的數字
void shift() {
  for (int i = 0; i < 3; i++) {
    array[i] = array[i + 1]; //位移原本陣列內容物
  }
  array[3] = a; //輸入新數字
}
/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  // The following order cannot be changed. MAP first and then SELECT.
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO, HIGH);
}
```

## 1126：RTC 時間顯示

**題目：** 設定 RTC 初始時間並在 LCD 上顯示時:分:秒。

[1126_RTC_LCD.ino](1126_RTC_LCD.ino)

```cpp
#include <LiquidCrystal.h>
#include <RTC.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* Change these values to set the current initial time */
const byte seconds = 55;
const byte minutes = 59;
const byte hours = 23;
const byte day = 26;

void setup() {
     // set up the LCD's number of columns and rows
     lcd.begin(16, 2);

     // set the time and start counting
     RTC.settime(day, hours, minutes, seconds);
     //RTC.setmonth(2);
     RTC.startcounting();
}

void loop() {
     lcd.clear();
     lcd.print("2024 Counting...");
     lcd.setCursor(0, 1);

     // Format hours, minutes, and seconds with leading zeros if necessary
     int hour = RTC.gethours();
     int minute = RTC.getminutes();
     int second = RTC.getseconds();
     int currentDay = RTC.getday();

     // Print formatted time
     lcd.print(hour < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(hour);
     lcd.print(":");
     lcd.print(minute < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(minute);
     lcd.print(":");
     lcd.print(second < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(second);

     lcd.print("   11/");
     lcd.print(currentDay < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(currentDay);

     delay(1000);
}
```

