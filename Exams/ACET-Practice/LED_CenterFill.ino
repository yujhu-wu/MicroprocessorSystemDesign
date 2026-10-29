#define NUM 16 // 首先定義LED的數目
int leds[NUM] = {0, 1, 2,100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15};

void setup() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
    digitalWrite(leds[8],LOW);
    digitalWrite(leds[7],LOW);
    delay(300);
    digitalWrite(leds[6],LOW);
    digitalWrite(leds[9],LOW);
    delay(300);
    digitalWrite(leds[5],LOW);
    digitalWrite(leds[10],LOW);
    delay(300);
    digitalWrite(leds[4],LOW);
    digitalWrite(leds[11],LOW);
    delay(300);
    digitalWrite(leds[3],LOW);
    digitalWrite(leds[12],LOW);
    delay(300);
    digitalWrite(leds[2],LOW);
    digitalWrite(leds[13],LOW);
    delay(300);
    digitalWrite(leds[1],LOW);
    digitalWrite(leds[14],LOW);
    delay(300);
    digitalWrite(leds[0],LOW);
    digitalWrite(leds[15],LOW);
    delay(300);
    ledControll(0x0000);
}

void ledControll(unsigned int light){
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
  }
  for(int i = 0; i < NUM; i++){
    if((1<<i) & light)
      digitalWrite(leds[i], LOW);
  }
}
