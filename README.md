# 微處理機系統 上機實作練習

微處理機系統課程的實作作業與上機考練習，並為**ACET晶心開發系統技術能力分級檢定**證照考試做準備。  
操作 Andes **ADP-CORVETTE-F1**開發板與ACET Shield Board上的LED、七段顯示器、按鍵、LCD、蜂鳴器與RTC。

- **平台：** Andes ADP-CORVETTE-F1(AndesCore N25)+ ACET Shield Board
- **開發環境：** Arduino IDE 1.6.5
- **使用技術：** GPIO、位元運算、MC74HC595A移位暫存器、4×4按鍵矩陣掃描、HD44780 LCM、PWM、RTC

## 課程作業（Labs）

| Lab | 主題 | 使用元件 |
|---|---|---|
| [Lab 1](Labs/Lab1_LED-Matrix/README.md) | LED 燈號變化（5 種模式） | GPIO、LED |
| [Lab 2](Labs/Lab2_7-Segment-PushButton/README.md) | 按鍵輸入 + 七段顯示器跑馬燈 | 7-Segment、MC74HC595A、Keypad |
| [Lab 3](Labs/Lab3_LCM-Text-Marquee/README.md) | LCM 文字走馬燈 | LCD (HD44780)、Keypad |
| [Lab 4](Labs/Lab4_PWM-Recorder/README.md) | PWM 錄放音機 | 蜂鳴器、PWM、LCD |
| [Lab 5](Labs/Lab5_RTC-Clock-Stopwatch/README.md) | RTC 時鐘 & 碼錶 | RTC、LCD |

## 上機考與證照練習

| 資料夾 | 內容 |
|---|---|
| [113 期中考](Exams/113-Midterm/README.md) | LED 兩側飛入交錯、七段顯示器按鍵與飛入動畫 |
| [期中考練習（112 考古）](Exams/112-Midterm-Practice/README.md) | 考前練習，同類型題目 |
| [ACET 實作題練習](Exams/ACET-Practice/README.md) | LED、七段顯示器、Keypad + LCD、蜂鳴器 |

## 其他

| 資料夾 | 內容 |
|---|---|
| [課堂練習與加分題](In-class/README.md) | LED 燈號、七段顯示器、按鍵掃描、RTC |
| [位元運算加分題](Bonus-Bit-Manipulation/README.md) | 6 題 C 語言位元運算 |

## 使用方式

以Arduino IDE 1.6.5(已安裝Corvette-F1板型支援)開啟 `.ino` 檔，選擇板子**Corvette-F1-N25**後上傳。
