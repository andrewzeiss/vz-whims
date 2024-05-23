#define vibePin1 2
#define vibePin1 3
#define vibePin1 4
#define vibePin1 5
#define vibePin1 6

int vibePins[5] = { 2, 3, 4, 5, 6 };
int i, j, p, pos;
bool approved, questionAnswered = false, readyToContinueToNext = false;

int num_of_vibes = sizeof(vibePins) / sizeof(vibePins[0]);  //stores the # of items in servoArray
unsigned long runTime = 15000; //5000
unsigned long vibeRunTime = runTime / sizeof(vibePins);
unsigned long delayTime = runTime / 10, halfDelay = delayTime / 2;


void setup() {
  Serial.begin(9600);
  Serial.println("Vibration Discrete Test");
  for (p = 0; p <= num_of_vibes - 1; p++) {
    pinMode(vibePins[j], OUTPUT);
  }
}

void loop() {
 // Start of testing
  GetApproval();
  HalfCycle(); // Beginning and Ending Stimuli
  GetApproval();

 // Three complete cycles
  while (readyToContinueToNext == false) {
    for (int z = 1; z <= 3; z++) {
      SingleCycle();
      Serial.println("out");
      continueToNext();
    }
  }

  // // End to Random Test
  Serial.println("Test 100 to random");
  GetApproval();
  EndToRand();

  // Fifty to Random Test
  Serial.println("Test 50 to Random");
  GetApproval();
  FiftyToRand();
}


void GetApproval() {
  approved = false;
  Serial.println("Press (y) when ready to move on");
  while (approved == false) {
    if (Serial.readString() == "y") {
      approved = true;
    }
  }
}

void continueToNext() {  // Function to move on or repeat a trial
  questionAnswered = false, readyToContinueToNext = false;
  Serial.println("Press (n) to repeat and (y) to continue");
  while (questionAnswered == false) {
    if (Serial.available() > 0) {
      if (Serial.readString() == "y") {
        readyToContinueToNext = true;
        questionAnswered = true;
      } else {
        readyToContinueToNext = false;
        questionAnswered = true;
      }
    }
  }
}

void SingleCycle() {
  Serial.println(num_of_vibes);
  for (i = 0; i <= num_of_vibes - 1; i++) {
    Serial.println(i + 1);
    if (i == 0) {
      digitalWrite(vibePins[i], HIGH);
      delay(delayTime);
    } else {
      digitalWrite(vibePins[i - 1], LOW);
      digitalWrite(vibePins[i], HIGH);
      delay(delayTime);
    }
  }
  for (p = 0; p <= num_of_vibes - 1; p++) {
    digitalWrite(vibePins[p], LOW);
  }
  delay(delayTime);
  for (i = num_of_vibes - 1; i >= 0; i--) {
    Serial.println(i + 1);
    digitalWrite(vibePins[i + 1], LOW);
    digitalWrite(vibePins[i], HIGH);
    delay(delayTime);
  }
  for (p = 0; p <= num_of_vibes - 1; p++) {
    digitalWrite(vibePins[p], LOW);
  }
}

void HalfCycle() {
  Serial.println(num_of_vibes);
  for (i = 0; i <= num_of_vibes - 1; i++) {
    Serial.println(i + 1);
    if (i == 0) {
      digitalWrite(vibePins[i], HIGH);
      delay(delayTime);
    } else {
      digitalWrite(vibePins[i - 1], LOW);
      digitalWrite(vibePins[i], HIGH);
      delay(delayTime);
    }
  }
  for (p = 0; p <= num_of_vibes - 1; p++) {
    digitalWrite(vibePins[p], LOW);
  }
  GetApproval();
  for (i = num_of_vibes - 1; i >= 0; i--) {
    Serial.println(i + 1);
    digitalWrite(vibePins[i + 1], LOW);
    digitalWrite(vibePins[i], HIGH);
    delay(delayTime);
  }
  for (p = 0; p <= num_of_vibes - 1; p++) {
    digitalWrite(vibePins[p], LOW);
  }
}

void EndToRand() {  //  From 0 to 100 then 100 to a random quartile 0,25,50...
  int testy[4] = { 1, 3, 2, 4};
  int testSize1 = sizeof(testy) / sizeof(testy[0]);
  Serial.println(testSize1);
  for (j = 0; j < testSize1; j++) {
    Serial.print("Going to vibe #");
    Serial.println(testy[j]);
    readyToContinueToNext = false;
    while (readyToContinueToNext == false) {
      for (i = 0; i <= num_of_vibes - 1; i++) {
        Serial.println(i + 1);
        if (i == 0) {
          digitalWrite(vibePins[i], HIGH);
          delay(delayTime);
        } else {
          digitalWrite(vibePins[i - 1], LOW);
          digitalWrite(vibePins[i], HIGH);
          delay(delayTime);
        }
      }
      for (p = 0; p <= num_of_vibes - 1; p++) {
        digitalWrite(vibePins[p], LOW);
      }
      delay(delayTime);
      for (i = num_of_vibes; i >= testy[j]; i--) { //num_of_vibes - 1
        Serial.println(i + 1);
        digitalWrite(vibePins[i], LOW);  // +1?
        digitalWrite(vibePins[i - 1], HIGH);
        delay(delayTime);
      }
      GetApproval();
      for (p = 0; p <= num_of_vibes - 1; p++) {
        digitalWrite(vibePins[p], LOW);
      }
      continueToNext();
    }
  }
}

void FiftyToRand() {  // Will move to fifty first for the location of fifty before starting. Can repeat
  int testy2[4] = { 1, 2, 4, 5};
  int testSize2 = sizeof(testy2) / sizeof(testy2[0]);
  Serial.println(testSize2);
  readyToContinueToNext = false;
  while (readyToContinueToNext == false) {
    for (i = 0; i <= (num_of_vibes / 2); i++) {
      Serial.println(i + 1);
      if (i == 0) {
        digitalWrite(vibePins[i], HIGH);
        delay(delayTime);
      } else {
        digitalWrite(vibePins[i - 1], LOW);
        digitalWrite(vibePins[i], HIGH);
        delay(delayTime);
      }
    }
    GetApproval();
    for (p = 0; p <= num_of_vibes - 1; p++) {
      digitalWrite(vibePins[p], LOW);
    }
    continueToNext();
  }
  for (j = 0; j < testSize2; j++) {
    Serial.print("Going to vibe #");
    Serial.println(testy2[j]);
    readyToContinueToNext = false;
    if (testy2[j] < 3) {
      while (readyToContinueToNext == false) {
        for (i = num_of_vibes / 2; i >= testy2[j] - 1; i--) {
          Serial.println(i + 1);
          digitalWrite(vibePins[i + 1], LOW);
          digitalWrite(vibePins[i], HIGH);
          delay(delayTime);
        }
        GetApproval();
        for (p = 0; p <= num_of_vibes - 1; p++) {
          digitalWrite(vibePins[p], LOW);
        }
        continueToNext();
      }
    } else {
      readyToContinueToNext = false;
      while (readyToContinueToNext == false) {
        for (i = num_of_vibes / 2; i <= testy2[j] - 1; i++) {
          Serial.println(i + 1);
          if (i == 0) {
            digitalWrite(vibePins[i], HIGH);
            delay(delayTime);
          } else {
            digitalWrite(vibePins[i - 1], LOW);
            digitalWrite(vibePins[i], HIGH);
            delay(delayTime);
          }
        }
        GetApproval();
        for (p = 0; p <= num_of_vibes - 1; p++) {
          digitalWrite(vibePins[p], LOW);
        }
        continueToNext();
      }
    }
  }
}