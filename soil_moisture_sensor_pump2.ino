// Arduino soil moisture code

// declare variables for digitalpins
int pump = 11;

// delay time between sensor readings (milliseconds)
const int delayTime = 1000; 

// "wet" and "dry" thresholds - these require calibration
int wet = 250;
int dry = 400;


void setup(){ // code that only runs once
  // set pins as outputs
  pinMode(pump,OUTPUT);
  
  // initialize serial communication
  Serial.begin(19200);
}

void loop(){ // code that loops forever
 
  //Moisture sensor reading
  int moistureValue = analogRead(A0);
  moistureValue = map(moistureValue, 700, 250, 1, 100)
  
  // If sensor reading is greater than "wet" threshold,
  // turn on the blue LED. If it is less than the "dry"
  // threshold, turn on the red LED and the pump. 
  
  if(moistureValue<wet){
    digitalWrite(pump,LOW);
    Serial.println("I´m really wet");
    Serial.print(moistureValue);
    Serial.println("  %");
  }
  else if(moistureValue>dry){
    digitalWrite(pump,HIGH);
    Serial.println("I need more water!");
    Serial.print(moistureValue);
    Serial.println("  %");
  }
  else{
    digitalWrite(pump,LOW);
    Serial.println("My humidity is perfect");
    Serial.print(moistureValue);
    Serial.println("  %");
  }
  
  // wait before taking next reading
  delay(delayTime);
  
}
