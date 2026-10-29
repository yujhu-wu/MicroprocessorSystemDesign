#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2

const byte SEGMENT_MAP[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,
                              0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x0}; // 0~9 and other symbols
const byte SEGMENT_SELECT[] = {0x0E, 0x0D, 0x0B, 0x07, 0x06, 0x09, 0x00}; // 控制4個顯示位
//0xF6 (0x06) = 1111 0110，0xF9 (0x09) = 1111 1001，只看後面4個數字，數字0表示燈亮的位置

void setup() {
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
}

void loop() {
  WriteNumberToSegment(4, 9);
  delay(1500);
  WriteNumberToSegment(5, 9);
  delay(3000);
  WriteNumberToSegment(4, 9);
  delay(1500);
  WriteNumberToSegment(6, -1);
  delay(1500);
}


// 將數字寫入指定的顯示位置
void WriteNumberToSegment(byte Segment, byte Value) {
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO, HIGH);
}
