int inputPin = 0;
int ledPin = 13;
int piezoPin = 9;
int piezoValueOn = 127;
int piezoValueOff = 0;
int dotDelay = 200;

char* letters[] = { 
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", 
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
 };
char* numbers[] = { "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." };
char strings[] = { };
char* morses[] = { };

void workSequence(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
    workDotOrDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);
}

void workDotOrDash(char dotOrDash) {
  digitalWrite(ledPin, HIGH);
  analogWrite(piezoPin, piezoValueOn);
  if (dotOrDash == '.') {
    delay(dotDelay);
  } else {
    delay(dotDelay * 3);
  }
  digitalWrite(ledPin, LOW);
  analogWrite(piezoPin, piezoValueOff);
  delay(dotDelay);
}

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int i = 0;
  
  while (Serial.available() > 0) {
    char ch = Serial.read();
    char* sequence = NULL;

    if (ch >= 'a' && ch <= 'z') {
      sequence = letters[ch - 'a'];
    } else if (ch >= 'A' && ch <= 'Z') {
      sequence = letters[ch - 'A'];
    } else if (ch >= '0' && ch <= '9') {
      sequence = numbers[ch - '0'];
    } else if (ch == ' ') {
      delay(dotDelay * 4);
    }

    if (sequence != NULL) {
      workSequence(sequence);
      morses[i] = sequence;
    } else {
      morses[i] = " ";
    }

    strings[i] = ch;

    i++;
  }

  Serial.println(strings);
  for (int j = 0; j < sizeof(morses); j++) {
    Serial.println(morses[j]);
  }
}
