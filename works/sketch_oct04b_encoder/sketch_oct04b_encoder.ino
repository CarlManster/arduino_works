int ledPin = 13;
int piezoPin = 9;
int piezoFrequency = 6000;
int dotDelay = 200;

char* letters[] = { 
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", 
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
 };
char* numbers[] = { "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." };

void workSequence(char* sequence) {       // 모르스 부호 각 시퀀스 별 동작
  int i = 0;

  while (sequence[i] != NULL) {
    workDotOrDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);
}

void workDotOrDash(char dotOrDash) {
  digitalWrite(ledPin, HIGH);             // LED ON
  
  if (dotOrDash == '.') {
    tone(piezoPin, piezoFrequency, dotDelay);   // 짧은 소리 재생
    delay(dotDelay);
  } else {
    tone(piezoPin, piezoFrequency, dotDelay * 3); // 긴 소리 재생
    delay(dotDelay * 3);
  }
  digitalWrite(ledPin, LOW);              // LED OFF
  delay(dotDelay);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String str = Serial.readString();   // 문자열 읽기

    Serial.println(str);                // 읽은 문자열을 출력

    String morses = "";
    
    for (int i = 0 ; i < str.length(); i++) {
      char ch = str.charAt(i);          // char로 분리
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

      if (sequence != NULL) {           // 모르스 부호를 찾은 경우
        Serial.print(ch);
        Serial.print(" : ");
        Serial.println(sequence);

        workSequence(sequence);
        morses += String(sequence) + " ";
      } else {                          // 모르스 부호를 찾지 못한 경우
        morses += " ";
      }
    }

    Serial.println(morses);
  }
}
