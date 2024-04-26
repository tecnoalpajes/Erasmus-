int ledCount = 5;    // the number of LEDs in the bar graph
int ledPins[] = {12, 11, 10, 8, 7};   // an array of pin numbers to which LEDs are attached

int ledPin = 9;
// select the pin for the "wind sensor"
int sensorValue = 0;
void setup() {
 pinMode(ledPin, OUTPUT);
 for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop() {
 int sensorReading = analogRead(0);
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(sensorReading, 0, 700, 0, ledCount);
  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
sensorValue = analogRead(3);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(1023-sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
}
