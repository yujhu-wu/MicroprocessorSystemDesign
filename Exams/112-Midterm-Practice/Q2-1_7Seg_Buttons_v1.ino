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
