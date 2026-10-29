# Lab 4：PWM 控制實驗 – 錄放音機

> 微處理機系統 · 課程作業 · [回到目錄](../../README.md)

- **繳交期限：** 2024/11/22
- **平台：** Andes ADP-CORVETTE-F1 開發板 + ACET Shield Board
- **開發環境：** Arduino IDE 1.6.5

## 題目要求

以 PWM 驅動蜂鳴器，製作可錄音與播放的電子琴，程式需有註解說明各種指令之控制。

- **Push button 1~7：** 發出七個音符，LCM 第一列最左邊顯示 Do、Re、Mi、Fa、So、La、Si。
- **Push button A / B / C：** 切換高 / 中 / 低音，LCM 第一列最右邊顯示 High、Middle、Low。
- **BTN1：** 開始錄音，LCM 第二列顯示 `Recording`。
- **BTN2：** 結束錄音，第二列顯示 `No Recording`。
- **BTN3：** 播放錄音，第二列顯示 `Playing`。
- **BTN4：** 播放預錄歌曲，第一列顯示歌名，第二列顯示 `Playing a Song.`

## 程式碼

### Lab4.ino（[Lab4.ino](Lab4.ino)）

```cpp
#define de 200

#define BUTTON_1 D10
#define BUTTON_2 D11
#define BUTTON_3 D12
#define BUTTON_4 D13

const byte column[] = {A0,A1,A2,A3};
char oldWang[] = "aaaeffe bbaag";
unsigned long beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4};
#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String songs="";
int speakerPin = D3;
char notes;
int tempo = 300;
int t=0;
int record=0;
String flower="";
void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode (column[0],OUTPUT); //將A0~A2設為OUTPUT
  pinMode (column[1],OUTPUT);
  pinMode (column[2],OUTPUT);
  pinMode (column[3],OUTPUT);
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(BT4, INPUT);
    lcd.begin(16, 2);
  lcd.cursor();
}

void loop() {

  runbuttom(0);     //代表讓A0調整為LOW  函式寫在下方
  if(!digitalRead(BUTTON_1)){
     lcd.setCursor(0,0);
     lcd.write("Do");
     notes = 'c';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("c");}

     delay(de);
  }
  if(!digitalRead(BUTTON_2)){
     lcd.setCursor(0,0);
     lcd.write("Fa");
     notes = 'f';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("f");}
     delay(de);
  }
  if(!digitalRead(BUTTON_3)){
     lcd.setCursor(0,0);
     lcd.write("Si");
     notes = 'b';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("b");}
     delay(de);
  }



  runbuttom(1);

  if(!digitalRead(BUTTON_1)){
     lcd.setCursor(0,0);
     lcd.write("Re");
     notes = 'd';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("d");}
     delay(de);
  }
  if(!digitalRead(BUTTON_2)){
     lcd.setCursor(0,0);
     lcd.write("So");
     notes = 'g';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("g");}
     delay(de);
  }


  runbuttom(2);

  if(!digitalRead(BUTTON_1)){
     lcd.setCursor(0,0);
     lcd.write("Mi");
     notes = 'e';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("e");}
     delay(de);
  }
  if(!digitalRead(BUTTON_2)){
     lcd.setCursor(0,0);
     lcd.write("La");
     notes = 'a';
     playNote(speakerPin,notes, tempo);
     if(record){
     songs.concat("a");}
     delay(de);
  }


   runbuttom(3);

  if(!digitalRead(BUTTON_1)){
    t=2;
    lcd.setCursor(10,0);
    lcd.write("       ");
    lcd.setCursor(12,0);
    lcd.write("HIGH");
  }
  if(!digitalRead(BUTTON_2)){
    t=1;
    lcd.setCursor(10,0);
    lcd.write("       ");
    lcd.setCursor(10,0);
    lcd.write("MIDDLE");
  }
  if(!digitalRead(BUTTON_3)){
    t=0;
    lcd.setCursor(10,0);
    lcd.write("       ");
    lcd.setCursor(13,0);
    lcd.write("LOW");
  }


  if(!digitalRead(BT1)){
    lcd.setCursor(0,1);
    lcd.write("                ");
    lcd.setCursor(0,1);
    lcd.write("Recording");
    songs.remove(0);
    record=1;
    }


  if(!digitalRead(BT2)){
    lcd.setCursor(0,1);
    lcd.write("                ");
    lcd.setCursor(0,1);
    lcd.write("No Recording");
    record=0;
    }


   if(!digitalRead(BT3)){
    lcd.setCursor(0,1);
    lcd.write("                ");
    lcd.setCursor(0,1);
    lcd.write("Playing");
    for(int i=0;i < sizeof(songs);i++){
          if (songs[i] == ' ') {
            delay(tempo); // rest
         } else {
  // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
            playNote(speakerPin,songs[i], tempo);
         }
    // 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
            delay(tempo/10);
      }

    }

    if(!digitalRead(BT4)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Land of Old Wang");//王老先生有塊地
    lcd.setCursor(0,1);
    lcd.write("Playing a Song");
     for (int i = 0; i < sizeof(oldWang); i++) {
 // 如果是空白的話，不撥放音樂
    if (oldWang[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
  // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
      playNote(speakerPin,oldWang[i], beats[i] * tempo);
    }
    // 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
    delay(tempo/10);
  }

    }

}



void runbuttom(byte r){   //切換A0~A3
  digitalWrite(column[0],HIGH);
  digitalWrite(column[1],HIGH);
  digitalWrite(column[2],HIGH);
  digitalWrite(column[3],HIGH);
  digitalWrite(column[r],LOW);
  }

void playNote(int OutputPin, char note, unsigned long duration) {
   // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };
  int tones[] = { 262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1046, 1175, 1318, 1397, 1568, 1760, 1976 };

  // 播放音符對應的頻率(低音)
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i+t*7], duration);
  //下方的 delay() 及 noTone ()，測試過後一定要有這兩行，整體的撥放出來的東西才不會亂掉，可能是因為 Arduino 送出tone () 頻率後會馬上接著執行下個指令，不會等聲音播完，導致撥出的聲音混合而亂掉
      delay(duration);
      noTone(OutputPin);
    }
  }
}
```

