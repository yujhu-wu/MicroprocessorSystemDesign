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
