#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2
#define BUTTON1 BT1
#define BUTTON2 BT2

char keyvalue[] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
byte Row = 0, Col = 0;
/* Segment byte maps for numbers 0 to 9 , A, b , c, d, E, F*/ /*MSB: dp g f e d c b a*/;
const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                              0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71, 0x0
                             };
const byte DP = 0x80; // Digit Point
int num[4] = {16, 16, 16, 16};
int a; // number of the button which is pushed
int segment = 0;
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
    WriteNumberToSegment(i, num[i]);
    delay(1);
  }
  if (keyscan()) {
    shift();
    delay(200);
  }
  if (! digitalRead(BUTTON1)) { //左到右
    Left2Right();
  }
  else if(! digitalRead(BUTTON2)){
    Right2Left();
  }
  else DisplayAll();
}

void DisplayAll(){
  for(int k = 0; k < 4; k++){
    WriteNumberToSegment(k, num[k]);
  }
}


// 输入数字
void addnum(int n) {
  if (segment < 4) {
    num[segment] = n;
    segment++;
  } else {
    // 若输入数字超过4个数字，先进的数字先出，新输入的数字补在后位
    for (int i = 0; i < 3; i++) {
      num[i] = num[i + 1];
    }
    num[3] = n;
  }
  delay(200);
}

// 使数字由左到右移动
void Left2Right() {
  int N1[4] = {}; // 记录移动数字
  int N2[4] = {}; // 记录原本数字
  int N3[4] = {16, 16, 16, 16}; // 不显示（为达到闪烁效果）

  for (int i = 0; i < 4; i++) {
    N1[i] = num[i];
    N2[i] = num[i];
    num[i] = 16; // 先全暗
  }

  int c1 = 0;
  while (c1 < 500) {
    DisplayAll();
    c1++;
  }

  // 按顺序显示4xxx 34xx 234x 1234
  for (int i = 0; i < 4; i++) {
    int flag = 3 - i;
    for (int k = 0; k < i + 1; k++) {
      num[k] = N1[flag];
      flag++;
    }

    int c2 = 0;
    while (c2 < 500) {
      DisplayAll();
      c2++;
    }

    // 显示完数字变暗，显示闪烁效果
    int a1 = 0;
    while (a1 < 200) {
      for (int k = 0; k < 4; k++) {
        WriteNumberToSegment(k, N3[k]);
      }
      a1++;
    }
  }

  // 按顺序显示x123 xx12 xxx1 xxxx
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      N1[j] = num[j];
    }
    for (int k = i; k < 3; k++) {
      num[k + 1] = N1[k];
    }
    num[i] = 16;

    int c3 = 0;
    while (c3 < 500) {
      DisplayAll();
      c3++;
    }

    // 显示完数字变暗，显示闪烁效果
    int a1 = 0;
    while (a1 < 200) {
      for (int k = 0; k < 4; k++) {
        WriteNumberToSegment(k, N3[k]);
      }
      a1++;
    }
  }

  // 将原本数字放回numbers数组
  for (int i = 0; i < 4; i++) {
    num[i] = N2[i];
  }
}

// 使数字由右到左移动
void Right2Left() {
  int N1[4] = {}; // 记录移动数字
  int N2[4] = {}; // 记录原本数字
  int N3[4] = {16, 16, 16, 16}; // 不显示（为达到闪烁效果）

  for (int i = 0; i < 4; i++) {
    N1[i] = num[i];
    N2[i] = num[i];
    num[i] = 16; // 先全暗
  }

  int c1 = 0;
  while (c1 < 500) {
    DisplayAll();
    c1++;
  }

  // 按顺序显示xxx1 xx12 x123 1234
  for (int i = 0; i < 4; i++) {
    int flag = i;
    for (int j = 3; j >= 3 - i; j--) {
      num[j] = N1[flag];
      flag--;
    }

    int c2 = 0;
    while (c2 < 500) {
      DisplayAll();
      c2++;
    }

    // 显示完数字变暗，显示闪烁效果
    int a1 = 0;
    while (a1 < 200) {
      for (int k = 0; k < 4; k++) {
        WriteNumberToSegment(k, N3[k]);
      }
      a1++;
    }
  }

  // 按顺序显示234x 34xx 4xxx xxxx
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      N1[j] = num[j];
    }
    for (int k = 0; k < 3 - i; k++) {
      num[k] = N1[k + 1];
    }
    num[3 - i] = 16;

    int c3 = 0;
    while (c3 < 500) {
      DisplayAll();
      c3++;
    }

    // 显示完数字变暗，显示闪烁效果
    int a1 = 0;
    while (a1 < 200) {
      for (int k = 0; k < 4; k++) {
        WriteNumberToSegment(k, N3[k]);
      }
      a1++;
    }
  }

  // 将原本数字放回numbers数组
  for (int i = 0; i < 4; i++) {
    num[i] = N2[i];
  }
}

bool keyscan() {
    bool keypressed = false;
    const int rowPins[4] = {10, 11, 12, 13};
    const int colPins[4] = {A0, A1, A2, A3};

    // Scan each column
    for (int col = 0; col < 4; col++) {
        digitalWrite(colPins[col],LOW);
        delayMicroseconds(100);

        // Check each row
        for (int row = 0; row < 4; row++) {
            if (digitalRead(rowPins[row]) == LOW) {
              a = col * 4 + row; // Calculate button index
              keypressed = true;
              return keypressed;
            }
        }
        digitalWrite(colPins[col],HIGH);
    }
    return false;
}


//位移陣列內的數字
void shift() {
  for (int i = 0; i < 3; i++) {
    num[i] = num[i + 1]; //位移原本陣列內容物
  }
  num[3] = a; //輸入新數字
}

/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  // The following order cannot be changed. MAP first and then SELECT.
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO, HIGH);
}
