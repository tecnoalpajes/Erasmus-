void setup() {
  //Serial port initialitation
  Serial.begin(19200);
}

void loop() {
  //Temperature sensor reading
  int TempvalueRaw = analogRead(A0);
  float voltage = TempvalueRaw * (5.0 / 1023.0);
  float Tempvalue = voltage - 0.5;
  Tempvalue = Tempvalue / 0.01;

  //Humidity sensor reading
  int moistureValue = analogRead(A1);
  moistureValue = map(moistureValue, 1, 1023, 1, 100);

  //Light sensor reading
  int LDRvalue = analogRead(A2);
  LDRvalue = map(LDRvalue, 1, 1023, 1, 100);

  //Message at serial port
  Serial.println("Wellcome to TOIS project!");
  Serial.println("@plantArduino");
  Serial.println("");

  //THRESHOLD for sensors
  int tempThreshold = 25;
  int moistureThreshold = 50;
  int LDRThreshold = 50;

  String message = ""; //string for message content
  
  int positiveState = 0; //variable for positive message

  //Checking the TEMPERATURE of the plant
  if (Tempvalue > tempThreshold) {
    message += " My temperature is fine at ";
    message += Tempvalue;
    message += " degrees, ";
	
    positiveState++; //increasing if positive
	
  } else {
    message += " My temperature is low at  ";
    message += Tempvalue;
    message += " degrees, ";
  }

  //Checking the HUMIDITY of the plant
   if (moistureValue > moistureThreshold) {
    message += " My soil is fine at ";
    message += moistureValue;
    message += " of humidity, ";

    positiveState++; //increasing if positive

  } else {
    message += " My soil is dry at ";
    message += moistureValue;
    message += " of humidity, ";
  }

  //Checking the LIGHTNING of the plant
  if (LDRvalue > LDRThreshold) {
    message += " I have enough with ";
    message += LDRvalue;
    message += " amount of light, ";

    positiveState++; //increasing if positive

  } else {
    message += " I have not enough with ";
    message += LDRvalue;
    message += " of lightning, ";
  }

  //Summarize the state of the plant
  String startofMessage = "";
  if (positiveState >= 2) {
    startofMessage = "¡Everything goes perfect! ";
  
  }else {
    startofMessage = "I don´t feel so well... ";
  }

  //Writing the final message  
  String finishedMessage = "";
  finishedMessage += startofMessage;
  finishedMessage += message;

  Serial.println(finishedMessage);
  Serial.println("");
  Serial.println("");

  delay(1000);

}
