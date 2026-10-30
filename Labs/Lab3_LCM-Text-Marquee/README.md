# Lab 3：LCM控制實驗 – 文字走馬燈

> 微處理機系統 · 課程作業 · [回到目錄](../../README.md)

- **繳交期限**：2024/10/31
- **平台**：Andes ADP-CORVETTE-F1開發板 + ACET Shield Board
- **開發環境**：Arduino IDE 1.6.5

## 題目要求

設計可左／右位移的LCM(HD44780相容LCD)文字走馬燈程式，程式需有註解說明各種指令之控制。

- 一開始畫面清空(`clear()`)，游標顯示在左上角。
- **Push button 1**：第一組文字(長度40)顯示在第一列。
- **Push button A**：第二組文字(長度40)顯示在第二列。
- **Push button 4 / D**：文字左移 / 右移。
- **BTN1**：Clear Display
- **BTN2**：Return Home
- **BTN4**：Cursor on/off

## 程式碼

### Lab3.ino([Lab3.ino](Lab3.ino))

```cpp
#include <LiquidCrystal.h>

#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON4 BT4

/*******************************************************
This program will test the LCD panel and the buttons
Mark Bramwell, July 2010
********************************************************/

// Select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char KeyValue[] = {'1', '2', '3', 'A', '4', '5', '6', 'B',
                   '7', '8', '9', 'C', '*', '0', '#', 'D'};
byte Row = 0, Col = 0;
bool cursor_switch = false; // Cursor toggle

void setup() {
    // Pin setup
    pinMode(10, INPUT);           // R1: S1,S2,S3,S4 (1,2,3,A)
    pinMode(11, INPUT_PULLUP);    // R2: S5,S6,S7,S8 (4,5,6,B)
    pinMode(12, INPUT_PULLUP);    // R3: S9, S10, S11,S12 (7,8,9,C)
    pinMode(13, INPUT_PULLUP);    // R4: (*,0,#,D)
    pinMode(A0, OUTPUT);           // A1, C1: S1,S5,S9 (1,4,7,*)
    pinMode(A1, OUTPUT);           // A2, C2: S2,S6,S10 (2,5,8,0)
    pinMode(A2, OUTPUT);           // A3, C3: S3,S7,S11 (3,6,9,#)
    pinMode(A3, OUTPUT);           // A4, C4: S4,S8,S12 (*,0,#,D)

    // Pin left to right: R1 R2 R3 R4
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);

    lcd.begin(16, 2);              // Start the library
    lcd.clear();                    // Clear the display at start
    lcd.setCursor(0, 0);            // Set cursor to the top-left corner
    lcd.cursor();                   // Ensure the cursor is visible
}


void loop() {
    // Put your main code here, to run repeatedly:
    static int keypressedcount = 0;
    byte keyindex = 0;

    if (!digitalRead(BUTTON1)) { // Clear display
        lcd.clear();               // Clear the display
        lcd.setCursor(0, 0);       // Set cursor to the top-left corner
        lcd.cursor();              // Ensure the cursor is visible
        delay(500);
    }


    if (!digitalRead(BUTTON2)) { // Return home
        lcd.setCursor(0, 0);
        lcd.home();
        delay(500);
    }

    if (!digitalRead(BUTTON4)) { // Cursor on or off
        if (cursor_switch) {
            lcd.noCursor();
            cursor_switch = false;
        } else {
            lcd.cursor();
            cursor_switch = true;
        }
        delay(500);
    }

    // The rest of the code remains unchanged
    if (keyscan() == true) {
        keyindex = (Row - 1) * 4 + Col;
        delay(5);
        char key = KeyValue[keyindex - 1];

        if (key == '1') { // First text group
            lcd.setCursor(0, 0);
            lcd.print("Put your main code here, to run program.");
            delay(300);
        }

        if (key == 'A') { // Second text group
            lcd.setCursor(0, 1);
            lcd.print("This program will test the LCD for LAB 3");
            delay(300);
        }

        if (key == '4') { // Scroll text left
            for (int i = 0; i < 40; ++i) {
                lcd.scrollDisplayLeft();
                delay(300);
            }
        }

        if (key == 'D') { // Scroll text right
            for (int i = 0; i < 40; ++i) {
                lcd.scrollDisplayRight();
                delay(300);
            }
        }
    }
}

bool keyscan() {
    Row = 0;
    Col = 0;
    bool keypressed = false;

    // Scan column 1
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    delayMicroseconds(100);

    // Read keys in row 1
    if (digitalRead(10) == LOW) { // Key = 1
        digitalWrite(A0, HIGH);
        Col = 1;
        Row = 1;
        keypressed = true;
        return keypressed;
    }

    // Read keys in row 2
    if (digitalRead(11) == LOW) { // Key = 4
        digitalWrite(A0, HIGH);
        Col = 1;
        Row = 2;
        keypressed = true;
        return keypressed;
    }

    // Scan column 4
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, LOW);
    delayMicroseconds(100);

    // Read keys in row 1
    if (digitalRead(10) == LOW) { // Key = A
        digitalWrite(A3, HIGH);
        Col = 4;
        Row = 1;
        keypressed = true;
        return keypressed;
    }

    // Read keys in row 4
    if (digitalRead(13) == LOW) { // Key = D
        digitalWrite(A3, HIGH);
        Col = 4;
        Row = 4;
        keypressed = true;
        return keypressed;
    }

    return false;
}
```

