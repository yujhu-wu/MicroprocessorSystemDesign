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
