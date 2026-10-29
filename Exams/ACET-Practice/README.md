# ACET 晶心開發系統檢定 實作題練習

> 微處理機系統 · 上機實作 · [回到目錄](../../README.md)

- **平台：** Andes ADP-CORVETTE-F1 開發板 + ACET Shield Board
- **開發環境：** Arduino IDE 1.6.5

針對 **ACET 晶心開發系統技術能力分級檢定** 實作題庫（ADP-Corvette-F1，Non-OS）進行練習，作為微處理機系統證照考試準備。

## LED：間隔閃爍

**題目：** 全部 LED 間隔閃爍，奇數亮則偶數不亮，反之亦然。

[LED_Alternate.ino](LED_Alternate.ino)

```cpp
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
```

## LED：由中間往兩側飛出（逐顆移動）

**題目：** 亮燈從中間往兩側移動飛出。

[LED_CenterOut.ino](LED_CenterOut.ino)

```cpp
#define NUM 16 // 首先定義LED的數目
int leds[NUM] = {0, 1, 2,100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15};

void setup() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
    digitalWrite(leds[8],LOW);
    digitalWrite(leds[7],LOW);
    delay(300);
    digitalWrite(leds[8],HIGH);
    digitalWrite(leds[7],HIGH);
    delay(300);
    digitalWrite(leds[6],LOW);
    digitalWrite(leds[9],LOW);
    delay(300);
    digitalWrite(leds[6],HIGH);
    digitalWrite(leds[9],HIGH);
    delay(300);
    digitalWrite(leds[5],LOW);
    digitalWrite(leds[10],LOW);
    delay(300);
    digitalWrite(leds[5],HIGH);
    digitalWrite(leds[10],HIGH);
    delay(300);
    digitalWrite(leds[4],LOW);
    digitalWrite(leds[11],LOW);
    delay(300);
    digitalWrite(leds[4],HIGH);
    digitalWrite(leds[11],HIGH);
    delay(300);
    digitalWrite(leds[3],LOW);
    digitalWrite(leds[12],LOW);
    delay(300);
    digitalWrite(leds[3],HIGH);
    digitalWrite(leds[12],HIGH);
    delay(300);
    digitalWrite(leds[2],LOW);
    digitalWrite(leds[13],LOW);
    delay(300);
    digitalWrite(leds[2],HIGH);
    digitalWrite(leds[13],HIGH);
    delay(300);
    digitalWrite(leds[1],LOW);
    digitalWrite(leds[14],LOW);
    delay(300);
    digitalWrite(leds[1],HIGH);
    digitalWrite(leds[14],HIGH);
    delay(300);
    digitalWrite(leds[0],LOW);
    digitalWrite(leds[15],LOW);
    delay(300);
    digitalWrite(leds[0],HIGH);
    digitalWrite(leds[15],HIGH);
    delay(300);
    digitalWrite(leds[1],LOW);
    digitalWrite(leds[14],LOW);
    delay(300);
    digitalWrite(leds[1],HIGH);
    digitalWrite(leds[14],HIGH);
    delay(300);
    digitalWrite(leds[2],LOW);
    digitalWrite(leds[13],LOW);
    delay(300);
    digitalWrite(leds[2],HIGH);
    digitalWrite(leds[13],HIGH);
    delay(300);
    digitalWrite(leds[3],LOW);
    digitalWrite(leds[12],LOW);
    delay(300);
    digitalWrite(leds[3],HIGH);
    digitalWrite(leds[12],HIGH);
    delay(300);
    digitalWrite(leds[4],LOW);
    digitalWrite(leds[11],LOW);
    delay(300);
    digitalWrite(leds[4],HIGH);
    digitalWrite(leds[11],HIGH);
    delay(300);
    digitalWrite(leds[5],LOW);
    digitalWrite(leds[10],LOW);
    delay(300);
    digitalWrite(leds[5],HIGH);
    digitalWrite(leds[10],HIGH);
    delay(300);
    digitalWrite(leds[6],LOW);
    digitalWrite(leds[9],LOW);
    delay(300);
    digitalWrite(leds[6],HIGH);
    digitalWrite(leds[9],HIGH);
    delay(300);
}

void ledControll(unsigned int light){
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
  }
  for(int i = 0; i < NUM; i++){
    if((1<<i) & light)
      digitalWrite(leds[i], LOW);
  }
}
```

## LED：由中間往兩側依序點亮

**題目：** 從中間開始往兩側依序點亮 LED，全部亮起後熄滅。

[LED_CenterFill.ino](LED_CenterFill.ino)

```cpp
#define NUM 16 // 首先定義LED的數目
int leds[NUM] = {0, 1, 2,100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15};

void setup() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
    digitalWrite(leds[8],LOW);
    digitalWrite(leds[7],LOW);
    delay(300);
    digitalWrite(leds[6],LOW);
    digitalWrite(leds[9],LOW);
    delay(300);
    digitalWrite(leds[5],LOW);
    digitalWrite(leds[10],LOW);
    delay(300);
    digitalWrite(leds[4],LOW);
    digitalWrite(leds[11],LOW);
    delay(300);
    digitalWrite(leds[3],LOW);
    digitalWrite(leds[12],LOW);
    delay(300);
    digitalWrite(leds[2],LOW);
    digitalWrite(leds[13],LOW);
    delay(300);
    digitalWrite(leds[1],LOW);
    digitalWrite(leds[14],LOW);
    delay(300);
    digitalWrite(leds[0],LOW);
    digitalWrite(leds[15],LOW);
    delay(300);
    ledControll(0x0000);
}

void ledControll(unsigned int light){
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
  }
  for(int i = 0; i < NUM; i++){
    if((1<<i) & light)
      digitalWrite(leds[i], LOW);
  }
}
```

## 七段顯示器：數字 8 單字位移

**題目：** 七段顯示器做出數字 8 單字位移，且不斷循環。

[7Seg_Shift8.ino](7Seg_Shift8.ino)

```cpp
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2


const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,
0x6F,  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0};
const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07};
// {0xFE,0xFD,0xFB,0xF7}; is OK, too.
const byte DP = 0x80; // Digit Point


void setup() {
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
}

void loop() {
  for(int i = 0; i <= 3; i++){
    WriteNumberToSegment(i, 8);
    delay(300);
  }
}

void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  // The following order cannot be changed. MAP first and then SELECT.
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO, HIGH);
}
```

## LCD + Keypads：按鍵顯示數字

**題目：** 按下 4×4 Keypads 其中一個按鍵，LCD 顯示該按鍵的編號（1~16）。

[Keypad_LCD_v1.ino](Keypad_LCD_v1.ino)

```cpp
int speakerPin = D3;
char song[] = {'c','d','e','f','g','a','b','D'};
char song2[] = "d";
unsigned long beats[] = {1};
int tempo = 500;

void setup() {
  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)
  //Pin left to right :R1 R2 R3 R4 C1 C2 C3 C4

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
    digitalWrite(A0,LOW);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A0,HIGH);
      playNote(speakerPin,song[0], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A1,HIGH);
      playNote(speakerPin,song[1], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A2,HIGH);
      playNote(speakerPin,song[2], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,LOW);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A3,HIGH);
      playNote(speakerPin,song[3], beats[0]*tempo);
    }
    digitalWrite(A0,LOW);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A0,HIGH);
      playNote(speakerPin,song[4], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A2,HIGH);
      playNote(speakerPin,song[5], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A2,HIGH);
      playNote(speakerPin,song[6], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,LOW);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A3,HIGH);
      playNote(speakerPin,song[7], beats[0]*tempo);
    }
    delay(tempo/10);

}

void playNote(int OutputPin, char note, unsigned long duration) {
  // 播放音符對應的頻率
  char names[] = {'c','d','e','f','g','a','b','D'};
  int tones[] = {262,294,330,349,392,440,494,523,587,659,698,784,880,988,1046,1175,1318,1397,1568,1760,1976};

  for(int i=0;i<8;i++){
    if(names[i]==note){
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}
```

[Keypad_LCD_v2.ino](Keypad_LCD_v2.ino)

```cpp
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
```

## PWM：蜂鳴器播放音樂

**題目：** 以 PWM 控制蜂鳴器產生音樂及唱歌。

[Buzzer_Song.ino](Buzzer_Song.ino)

```cpp
int speakerPin = D3;
char song[] = "geefddcdefggg";
unsigned long beats[] = {1,1,2,1,1,2,1,1,1,1,1,1,1,2,4};
int tempo = 300;

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < sizeof(song); i++) {
    if (song[i] == ' ') { // If it's a space, do not play music
      delay(beats[i] * tempo); // Rest
    } else { // Call playNote function to convert the note into a signal to play through the speaker
      playNote(speakerPin, song[i], beats[i] * tempo);
    }
    // Delay between notes to create a legato or staccato effect
    delay(tempo / 10);
  }
}

void playNote(int OutputPin, char note, unsigned long duration) {
  // Define note names and their corresponding frequencies
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };
  int tones[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1046, 1175, 1318, 1397, 1568, 1760, 1976 };

  // Iterate over note names and frequencies
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      // Play the corresponding tone
      tone(OutputPin, tones[i], duration);

      // Add delay and stop the tone after playing it
      delay(duration);
      noTone(OutputPin);
    }
  }
}
```

