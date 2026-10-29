int speakerPin = D3;
char song[] = {'c','d','e','f','g','a','b','D'};
char song2[] = "d";
unsigned long beats[] = {1};
int tempo = 500;

void setup() {
  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)
  //Pin left to right :R1 R2 R3 R4 C1 C2 C3 C4

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
    digitalWrite(A0,LOW);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A0,HIGH);
      playNote(speakerPin,song[0], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A1,HIGH);
      playNote(speakerPin,song[1], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A2,HIGH);
      playNote(speakerPin,song[2], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,LOW);
    delayMicroseconds(100);
    if(digitalRead(10)==LOW){
      digitalWrite(A3,HIGH);
      playNote(speakerPin,song[3], beats[0]*tempo);
    }
    digitalWrite(A0,LOW);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A0,HIGH);
      playNote(speakerPin,song[4], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A2,HIGH);
      playNote(speakerPin,song[5], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    digitalWrite(A3,HIGH);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A2,HIGH);
      playNote(speakerPin,song[6], beats[0]*tempo);
    }
    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,LOW);
    delayMicroseconds(100);
    if(digitalRead(11)==LOW){
      digitalWrite(A3,HIGH);
      playNote(speakerPin,song[7], beats[0]*tempo);
    }
    delay(tempo/10);

}

void playNote(int OutputPin, char note, unsigned long duration) {
  // 播放音符對應的頻率
  char names[] = {'c','d','e','f','g','a','b','D'};
  int tones[] = {262,294,330,349,392,440,494,523,587,659,698,784,880,988,1046,1175,1318,1397,1568,1760,1976};

  for(int i=0;i<8;i++){
    if(names[i]==note){
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}
