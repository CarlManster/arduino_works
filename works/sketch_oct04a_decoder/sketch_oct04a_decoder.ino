#define PATTERN_COUNT (36)

static int threshold = 50;

static int maxPattern = 6;
static int waitMilli = 20;

static int shortCount = 5;
static int longCount = shortCount * 3;
static int restCount = shortCount * 10;

static const char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const char *codes[PATTERN_COUNT] = {
  "-.",                 // A, codes[0]
  ".---",               // B, codes[1]
  ".-.-",               // C
  ".--",                // D
  "-",                  // E
  "--.-",               // F
  "..-",                // G
  "----",               // H
  "--",                 // I
  "-...",               // J
  ".-.",                // K
  "-.--",               // L
  "..",                 // M
  ".-",                 // N
  "...",                // O
  "-..-",               // P
  "..-.",               // Q
  "-.-",                // R
  "---",                // S
  ".",                  // T
  "--.",                // U
  "---.",               // V
  "-..",                // W
  ".--.",               // X
  ".-..",               // Y
  "..--",               // Z
  ".....",              // 0
  "-....",              // 1
  "--...",              // 2
  "---..",              // 3
  "----.",              // 4
  "-----",              // 5
  ".----",              // 6
  "..---",              // 7
  "...--",              // 8
  "....-",              // 9, codes[35]
};

int pressAccumulated = 0;
int restAccumulated = 0;

String morseCode = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  int volume = analogRead(A0);

  int count = 0;
  if (volume >= threshold) { 
    pressAccumulated++;
    restAccumulated = 0;
  } else {
    restAccumulated++;
    count = pressAccumulated;
    pressAccumulated = 0;
    
    if (restAccumulated > restCount) {
      findLetter();
      restAccumulated = 0;
      morseCode = "";
    }
  }

  if (count > longCount) {
    morseCode += "-";
    Serial.print("-");
  } else if (count > shortCount) {
    morseCode += ".";
    Serial.print(".");
  }

  delay(waitMilli);
}

void findLetter() {
  char morseCodeArray[maxPattern];
  morseCode.toCharArray(morseCodeArray, maxPattern);
  
  if (strlen(morseCodeArray) > 0) {
    Serial.print(" : ");
    
    for (int i=0;i<PATTERN_COUNT;i++) {
      if (strlen(morseCodeArray) == strlen(codes[i]) && strcmp(morseCodeArray,codes[i]) == 0) {
        Serial.println(letters[i]);
        return;
      }
    }

    Serial.println('?');
  }
}
