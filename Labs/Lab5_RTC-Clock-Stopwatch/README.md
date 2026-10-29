# Lab 5：RTC 控制 – 時鐘顯示 & 碼錶控制

> 微處理機系統 · 課程作業 · [回到目錄](../../README.md)

- **繳交期限：** 2024/12/06
- **平台：** Andes ADP-CORVETTE-F1 開發板 + ACET Shield Board
- **開發環境：** Arduino IDE 1.6.5

## 題目要求

使用 RTC（Real-Time Clock）在 LCM 顯示日期時間，並實作碼錶功能，程式需有註解說明各種指令之控制。

- 先將 RTC 設定為 Demo 當天日期與時間，第一列顯示 `MM/DD    HH:MM:SS`（例：`05/09    05:08:06`）。
- 碼錶功能：
  1. **BTN1：** 進入碼錶功能，第二列最左邊顯示 `00:00:00`，最右邊顯示 `StopWatch`。
  2. **BTN4：** 開始計時，右側顯示 `Counting`；再按一次暫停並顯示 `Stop`；再按一次繼續計時，依此類推。
  3. **BTN2：** 碼錶重設為 `00:00:00`，右側顯示 `StopWatch`。
  4. **BTN3：** 結束碼錶，清空第二列。

## 程式碼

### Lab5.ino（[Lab5.ino](Lab5.ino)）

```cpp
#include <RTC.h>
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

#include <LiquidCrystal.h>
#include <RTC.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* Change these values to set the current initial time */
const byte seconds = 10;
const byte minutes = 53;
const byte hours = 13;
const byte day = 20;

unsigned long startTime = 0; // 記錄開始時間
unsigned long passTime = 0; // 累計的已經經過的時間
unsigned long pausedTime = 0; // 暫停時的時間
bool isPaused = false; // 記錄是否為暫停狀態

int flag = 0;
int state = 0;
int state4 = 0;

void setup() {
  // Set up the LCD's number of columns and rows
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(BT4, INPUT);
  lcd.begin(16, 2);
  // Set the time and start counting
  RTC.settime(day, hours, minutes, seconds);
  RTC.startcounting();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  realtime();

  if (digitalRead(BT1) == LOW) {
    flag = 1;
    state = 1;
  }

  if (digitalRead(BT2) == LOW) {
    if (state == 1) {
      flag = 2;
    }
  }

  if (digitalRead(BT3) == LOW) {
    flag = 3;
    state = 0;
  }

  if (digitalRead(BT4) == LOW) {
    if (state == 1) {
      flag = 4;
      if (state4 == 0) { // 開始計時
        state4 = 1;
        if (isPaused) {
          // 從暫停繼續計時
          startTime = RTC.gethours() * 3600 + RTC.getminutes() * 60 + RTC.getseconds();
          isPaused = false;
        } else {
          // 第一次按下開始計時
          startTime = RTC.gethours() * 3600 + RTC.getminutes() * 60 + RTC.getseconds();
          passTime = 0;
        }
      } else if (state4 == 1) { // 暫停
        state4 = 0;
        pausedTime = RTC.gethours() * 3600 + RTC.getminutes() * 60 + RTC.getseconds();
        passTime += pausedTime - startTime; // 保存當前已經經過的時間
        isPaused = true;
      }
    }
  }

  if (flag == 1) { // BUTTON1 pushed
    lcd.setCursor(0, 1);
    lcd.print("00:00:00 Stop Watch");
    passTime = 0;
  }

  if (flag == 2) { // BUTTON2 pushed
    passTime = 0;
    lcd.setCursor(0, 1);
    lcd.print("00:00:00 Stop Watch");
  }

  if (flag == 3) { // BUTTON3 pushed
    passTime = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    realtime();
  }

  if (flag == 4) { // BUTTON4 pushed
    if (state4 == 1) { // 計時進行中
      unsigned long currentTime = RTC.gethours() * 3600 + RTC.getminutes() * 60 + RTC.getseconds();
      unsigned long totalPassTime = passTime + (currentTime - startTime);

      int h = totalPassTime / 3600;
      int m = (totalPassTime % 3600) / 60;
      int s = totalPassTime % 60;

      lcd.clear();
      lcd.setCursor(0, 0);
      realtime();
      lcd.setCursor(0, 1);
      if (h < 10) lcd.print("0");
      lcd.print(h);
      lcd.print(":");
      if (m < 10) lcd.print("0");
      lcd.print(m);
      lcd.print(":");
      if (s < 10) lcd.print("0");
      lcd.print(s);
      lcd.setCursor(9, 1);
      lcd.print("Counting");
    } else if (state4 == 0) { // 暫停狀態
      lcd.clear();
      lcd.setCursor(0, 0);
      realtime();

      int h = passTime / 3600;
      int m = (passTime % 3600) / 60;
      int s = passTime % 60;

      lcd.setCursor(0, 1);
      if (h < 10) lcd.print("0");
      lcd.print(h);
      lcd.print(":");
      if (m < 10) lcd.print("0");
      lcd.print(m);
      lcd.print(":");
      if (s < 10) lcd.print("0");
      lcd.print(s);
      lcd.setCursor(9, 1);
      lcd.print(" Stop");
    }
  }

  delay(1000);
}

void realtime() { // Display initial time
  lcd.print("11/");
  lcd.print(RTC.getday());
  lcd.print(" ");

  if (RTC.gethours() < 10) lcd.print("0");
  lcd.print(RTC.gethours());
  lcd.print(":");

  if (RTC.getminutes() < 10) lcd.print("0");
  lcd.print(RTC.getminutes());
  lcd.print(":");

  if (RTC.getseconds() < 10) lcd.print("0");
  lcd.print(RTC.getseconds());
}
```

