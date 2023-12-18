#define THREASHOLD 50
#define LEVEL_1 1
#define LEVEL_2 5
#define LEVEL_3 10

#include <CapacitiveSensor.h> 

CapacitiveSensor   capSensor = CapacitiveSensor(7, 5);
int low = 1000;

String messageOne = "1 Second is almost nothing";
String messageTwo = "5 Seconds is not enough";
String messageThree = "10 Seconds is quite perfect!";

void setup(){
  Serial.begin(19200);
  pinMode(12, OUTPUT);

  calibrate();
  Serial.println("");
  Serial.println("Wellcome to ToiS project!");
  Serial.println("@thehappyplant");
  Serial.println("");
}

void loop(){
  boolean isTouching = false;
  long timeStartTouching = millis();
  int levelReached = 0;

  do {
    int val =  getCapSensor(capSensor);
    if (val - low > THREASHOLD) {
      isTouching = true;
      digitalWrite(12, HIGH);
    } else {
      isTouching = false;
      digitalWrite(12, LOW);
    }

    int timeTouching = millis() - timeStartTouching;

    if (timeTouching / 1000 >= LEVEL_3) {
      if (levelReached < 3) {
        levelReached = 3;
        Serial.println(messageThree);
      }
    
    } else if (timeTouching / 1000 >= LEVEL_2) {
      if (levelReached < 2) {
        levelReached = 2;
        Serial.println(messageTwo);
      }
    
    } else if (timeTouching / 1000 >= LEVEL_1) {
      if (levelReached < 1) {
        levelReached = 1;
        Serial.println(messageOne);
      }
    }
  } while (isTouching);
}

void calibrate() {
  long timer = millis();
  while (millis() - timer < 100) {
    int val =  capSensor.capacitiveSensor(30);
    if (val < low) {
      low = val;
    }
  }
}

#define SAMPLES 10
int getCapSensor(CapacitiveSensor sensor) {
  int maxVal = 0;
  for (int i = 0; i < SAMPLES; i++) {
    int val = capSensor.capacitiveSensor(30);
    if (val > maxVal)maxVal = val;
  }
  return maxVal;
}

