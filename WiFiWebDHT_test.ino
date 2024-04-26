/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <WiFiNINA.h>
#include <DHT.h> //Introduzco la libreria necesaria para el sensor DHT11
//Declara constantes y pin de entrada
#define DHTPIN 2 //Indicamos el pin donde conectaremos la patilla data de nuestro sensor.
// Definimos el tipo de sensor que vas a emplear. En este caso usamos el DHT11
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor

#include "arduino_secrets3.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  dht.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
client.println("<title>Weather Report</title>\n");
client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n");
client.println("body{margin-top: 50px;} h1 {color: #851010;margin: 50px auto 30px;}\n");
client.println("p {font-size: 30px;color: #444444;margin-bottom: 10px;}\n");
client.println("</style>\n");
client.println("</head>\n");
client.println("<body>\n");
client.println("<div id=\"webpage\">\n");
client.println("<h1>TOIS Weather Report</h1>\n");

          // output the value of each analog input pin
float h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
float t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
            
            client.print("<p>Temperature: ");
            client.println(t,1);
            client.println(" *C</p>");
            client.print("<p>Humidity: ");
            client.println(h,0);
            client.println(" %</p>");
            client.println();
            client.println("</div>\n");
            client.println("</body>\n");         
          client.println("</html>\n");
          break;
      }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
