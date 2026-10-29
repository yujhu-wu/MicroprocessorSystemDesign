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
