/*

WiFi 101 ThingSpeak Data Uploader

Hardware Required:

* Arduino Zero or Uno Board

* Arduino Wifi Shield 101

* Photocell

* Temperature Sensor (This example uses a TMP36)

* 10K Ohm Resistor

created Sept 2015

by Helena Bisby <support@arduino.cc>

This example code is in the public domain

https://www.arduino.cc/en/Tutorial/WiFi101ThingSpeakDataUploader

*/

#include <SPI.h>
#include <WiFiNINA.h>

// Local Network Settings
#include "arduino_secrets3.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;             // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";

String APIKey = "XXXXXXXXXXXXXXXX";             // enter your channel's Write API Key

const int updateThingSpeakInterval = 20 * 1000; // 20 second interval at which to update ThingSpeak

// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;

// Initialize Arduino Ethernet Client

WiFiClient client;

void setup() {

  // Start Serial for debugging on the Serial Monitor

  Serial.begin(19200);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for Leonardo only

  }

  // check for the presence of the shield:

  if (WiFi.status() == WL_NO_SHIELD) {

    Serial.println("WiFi shield not present");

    // don't continue:

    while (true);

  }

  // attempt to connect to Wifi network:

  while ( status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:

    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:

    delay(10000);

  }

  // you're connected now, so print out the status:

  printWifiStatus();
}

void loop() {

  // read values from pins and store as strings

  String soil = String(analogRead(A0), DEC); // read light value

  // find temp value

  String light = String(analogRead(A2), DEC); // read light value

  // Print Update Response to Serial Monitor

  if (client.available()) {

    char c = client.read();

    Serial.print(c);

  }

  // Disconnect from ThingSpeak

  if (!client.connected() && lastConnected) {

    Serial.println("...disconnected");

    Serial.println();

    client.stop();

  }

  // Update ThingSpeak

  if (!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval)) {

    updateThingSpeak("field1=" + soil + "&field2=" + ligth);

    Serial.println(soil);

    Serial.println(ligth);

  }

  lastConnected = client.connected();
}

void updateThingSpeak(String tsData) {

  if (client.connect(thingSpeakAddress, 80)) {

    client.print("POST /update HTTP/1.1\n");

    client.print("Host: api.thingspeak.com\n");

    client.print("Connection: close\n");

    client.print("X-THINGSPEAKAPIKEY: " + APIKey + "\n");

    client.print("Content-Type: application/x-www-form-urlencoded\n");

    client.print("Content-Length: ");

    client.print(tsData.length());

    client.print("\n\n");

    client.print(tsData);

    lastConnectionTime = millis();

    if (client.connected()) {

      Serial.println("Connecting to ThingSpeak...");

      Serial.println();

    }

  }
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}
