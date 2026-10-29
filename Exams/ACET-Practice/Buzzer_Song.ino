int speakerPin = D3;
char song[] = "geefddcdefggg";
unsigned long beats[] = {1,1,2,1,1,2,1,1,1,1,1,1,1,2,4};
int tempo = 300;

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < sizeof(song); i++) {
    if (song[i] == ' ') { // If it's a space, do not play music
      delay(beats[i] * tempo); // Rest
    } else { // Call playNote function to convert the note into a signal to play through the speaker
      playNote(speakerPin, song[i], beats[i] * tempo);
    }
    // Delay between notes to create a legato or staccato effect
    delay(tempo / 10);
  }
}

void playNote(int OutputPin, char note, unsigned long duration) {
  // Define note names and their corresponding frequencies
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };
  int tones[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1046, 1175, 1318, 1397, 1568, 1760, 1976 };

  // Iterate over note names and frequencies
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      // Play the corresponding tone
      tone(OutputPin, tones[i], duration);

      // Add delay and stop the tone after playing it
      delay(duration);
      noTone(OutputPin);
    }
  }
}
