int ledPin = 13;
int piezoPin = 9;
int piezoFrequency = 6000;
int dotDelay = 200;

char* letters[] = { 
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", 
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
 };
char* numbers[] = { "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." };

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
  
  if (dotOrDash == '.') {
    tone(piezoPin, piezoFrequency, dotDelay);
    delay(dotDelay);
  } else {
    tone(piezoPin, piezoFrequency, dotDelay * 3);
    delay(dotDelay * 3);
  }
  digitalWrite(ledPin, LOW);
  delay(dotDelay);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String str = Serial.readString();

    Serial.println(str);

    String morses = "";
    
    for (int i = 0 ; i < str.length(); i++) {
      char ch = str.charAt(i);
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
        Serial.print(ch);
        Serial.print(" : ");
        Serial.println(sequence);

        workSequence(sequence);
        morses += String(sequence) + " ";
      } else {
        morses += " ";
      }
    }

    Serial.println(morses);
  }
}
