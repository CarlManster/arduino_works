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
  int volume = analogRead(A0); 	// 아날로그 A0에서 읽기

  int count = 0;
  if (volume >= threshold) {  	// 상태값이 임계값 이상이면 누른것으로 간주
    pressAccumulated++;			    // 누른 시간 증가
    restAccumulated = 0;		    // 휴지 시간 초기화
  } else {						          // 상태값이 임계값 미만이면 누르지 않는 것으로 간주
    restAccumulated++;			    // 휴지 시간 증가
    count = pressAccumulated;	  // 누른 시간을 정산
    pressAccumulated = 0;		    // 누른 시간 초기화
    
    if (restAccumulated > restCount) { // 휴지 시간이 일정 시간 지속되면 종료 처리 후 판독
      findLetter();
      restAccumulated = 0;		  // 휴지 시간 초기화
      morseCode = "";			      // 누적된 모르스 코드 문자열 초기화
    }
  }

  if (count > longCount) {			// 정산된 누른 시간이 길게 누른 것으로 판단될 경우
    morseCode += "-";
    Serial.print("-");
  } else if (count > shortCount) {	// 정산된 누른 시간이 짧게 누른 것으로 판단될 경우
    morseCode += ".";
    Serial.print(".");
  }

  delay(waitMilli);					// Loop 간 간격
}

void findLetter() {
  char morseCodeArray[maxPattern];
  morseCode.toCharArray(morseCodeArray, maxPattern); // String을 char array로 변환
  
  if (strlen(morseCodeArray) > 0) { // 문자열의 길이가 0보다 크면 패턴을 찾음
    Serial.print(" : ");
    
    for (int i=0;i<PATTERN_COUNT;i++) {
      if (strlen(morseCodeArray) == strlen(codes[i]) && strcmp(morseCodeArray,codes[i]) == 0) {
        Serial.println(letters[i]);	// 발견된 패턴이 있으면 해당 문자열 출력
        return;
      }
    }

    Serial.println('?');			// 발견된 패턴이 없으면 ? 문자열 출력
  }
}
