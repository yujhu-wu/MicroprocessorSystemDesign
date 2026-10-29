# 113 學年 微處理機系統期中考

> 微處理機系統 · 上機實作 · [回到目錄](../../README.md)

- **平台：** Andes ADP-CORVETTE-F1 開發板 + ACET Shield Board
- **開發環境：** Arduino IDE 1.6.5

期中考上機實作題（高級實作考題，Non-OS）。

## 題 1：LED 兩側飛入、交錯飛離

**題目：** 多功能板有 8 個紅色 LED 與 8 個綠色 LED，按下 BTNt（t = 1~4）時，t 個亮燈從兩側飛入、在中間交錯而過、再從兩側飛離（LED 全滅），重複兩次後停止。

[Q1_LED.ino](Q1_LED.ino)

```cpp
#define NUM 16
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4
int leds[NUM]={
  D0,D1,2,100,4,5,6,7,8,9,10,11,12,13,D14,D15
  };
/* Segment byte maps for numbers 0 to 9 , A, b , C */
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F,0X77,0X7C,0X39};

/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xFE,0xFD,0xFB,0xF7};
void setup ()
{
  for(int i=0;i<NUM;i++){
      pinMode(leds[i],OUTPUT);
      digitalWrite(leds[i],HIGH);
  }
  pinMode(BT1,INPUT);
  pinMode(BT2,INPUT);
  pinMode(BT3,INPUT);
  pinMode(BT4,INPUT);
}

void LedControl(unsigned val){
  for(int i=0;i<NUM;i++){
    if(val & (1<<i)){
      digitalWrite(leds[i],LOW);
    }
    else{
      digitalWrite(leds[i],HIGH);
    }
  }
}

/* Main program */
void loop()
{
    /* Update the display with the current counter value */
    if(!digitalRead(BUTTON1))
    {
      LedPattern(1);
    }
    if(!digitalRead(BUTTON2))
    {
      LedPattern(2);
    }
    if(!digitalRead(BUTTON3))
    {
      LedPattern(3);
    }
    if(!digitalRead(BUTTON4))
    {
      LedPattern(4);
    }
}

void LedPattern(int group_size){
  for(int repeat=0; repeat<2; repeat++){
    for(int i=0,j=NUM-1; i<NUM || j>=0; i++,j--){
      unsigned val =0;
      val |= (1<<i) | (1<<j);

      for(int k=1; k<group_size; k++){
        if(i+k <NUM) val|= (1<<(i+k));
        if(j-k >=0) val|= (1<<(j-k));
      }
      LedControl(val);
      delay(300);
    }
    LedControl(0x0000);
    delay(300);
  }
}
```

## 題 2-1：按鈕對應七段顯示器數字

**題目：** 按鈕 1~4 分別對應數字 2、4、6、8，按下時 4 個七段顯示器全部顯示相同數字。

[Q2-1_7Seg_Buttons.ino](Q2-1_7Seg_Buttons.ino)

```cpp
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO D2

#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

/* Segment byte maps for numbers 0 to 9 , A, b , C */
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F,0X77,0X7C,0X39};

/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {16,16,16,16,0x06,0x09,0x00};
void setup ()
{
    /* Set DIO pins to  */
    pinMode(LATCH_DIO,OUTPUT);
    pinMode(CLK_DIO,OUTPUT);
    pinMode(DATA_DIO,OUTPUT);
    WriteNumberToSegment(6 , -1);
}

/* Main program */
void loop()
{
    /* Update the display with the current counter value */
    if(!digitalRead(BUTTON1))
    {
      WriteNumberToSegment(3 , 2);
    }
    if(!digitalRead(BUTTON2))
    {
      WriteNumberToSegment(2 , 4);
    }
    if(!digitalRead(BUTTON3))
    {
      WriteNumberToSegment(1 , 6);
    }
    if(!digitalRead(BUTTON4))
    {
      WriteNumberToSegment(0 , 8);
    }
}

/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO,LOW);

  // There is a bug in the following two statements
  shiftOut(DATA_DIO,CLK_DIO,MSBFIRST,SEGMENT_MAP[Value] );
  shiftOut(DATA_DIO,CLK_DIO,MSBFIRST,SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO,HIGH);
}
```

## 題 2-2：數字 0 兩側飛入、交錯飛出

**題目：** 七段顯示器做出數字 0 從兩側飛入、交錯而過並飛出，之後無數字顯示，動作重複不停止。

[Q2-2_7Seg_FlyIn.ino](Q2-2_7Seg_FlyIn.ino)

```cpp
#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO D2

#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

/* Segment byte maps for numbers 0 to 9 , A, b , C */
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F,0X77,0X7C,0X39};

/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xFE,0xFD,0xFB,0xF7,0x06,0x09,0x00};
void setup ()
{
    /* Set DIO pins to  */
    pinMode(LATCH_DIO,OUTPUT);
    pinMode(CLK_DIO,OUTPUT);
    pinMode(DATA_DIO,OUTPUT);
}

/* Main program */
void loop()
{
  WriteNumberToSegment(4 , 0);
  delay(1500);
  WriteNumberToSegment(5 , 0);
  delay(3000);
  WriteNumberToSegment(4 , 0);
  delay(1500);
  WriteNumberToSegment(6 , -1);
  delay(1500);
}

/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO,LOW);

  // There is a bug in the following two statements
  shiftOut(DATA_DIO,CLK_DIO,MSBFIRST,SEGMENT_MAP[Value] );
  shiftOut(DATA_DIO,CLK_DIO,MSBFIRST,SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO,HIGH);
}
```

