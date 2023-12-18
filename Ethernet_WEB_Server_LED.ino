/*  TITLE: Control of LEDs from a WEB server.
*/
 // Libraries
  #include <SPI.h> 
  #include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
  byte mac[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
  IPAddress ip(192,168,1,74);
  IPAddress gateway(192,168,1,1); 
  IPAddress subnet(255,255,255,0);
   
// Initialize the Ethernet server library
// with the IP address and port 80 by default for HTTP:
  EthernetServer server(80); 
  
  int LED = 7; // digital LED pin used
  String estate = "OFF"; // initial state of LED
   
  void setup() {
    Serial.begin(9600); // open serial communications

   // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip, gateway, subnet);
    server.begin();
    Serial.print("the IP from the local server is:  ");
    Serial.println(Ethernet.localIP()); // it gives as the number
   
    pinMode(LED,OUTPUT); // LED definition
  }
   
  void loop()
  { 
    // Creation of a Web client
    EthernetClient client = server.available(); 
    // listen for incoming clients
    if (client) 
    {
      Serial.println(); 
      Serial.println("New client");
      Serial.println();
      boolean currentLineIsBlank = true; 
      String chain="";
      while (client.connected()) 
      {
        if (client.available()) 
        {
          char c = client.read();
          Serial.write(c);
          chain.concat(c);
           int position=chain.indexOf("LED=");
           // output the value of the digital pin
            if(chain.substring(position)=="LED=ON"){
              digitalWrite(LED,HIGH);
              estate="ON";
            }
            if(chain.substring(position)=="LED=OFF") {
              digitalWrite(LED,LOW);
              estate="OFF";
            }
          if (c == '\n' && currentLineIsBlank) // send a standard HTTP response header
          {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println();
              client.println("<html>");
              client.println("<body style='background-color: #cbced1;'>");
              client.println("<br/><br/>");
              client.println("<h1 align='center'>CONTROL YOUR LED</h1>");
              client.println("<br/><br/>");
              client.println("<div style='text-align:center;'>");
              client.println("<button onClick=location.href='./?LED=ON\' style='margin:auto;background-color: #626d78;color: snow;padding: 10px;width:85px;'>");
              client.println("ON");
              client.println("</button>");
              client.println("<button onClick=location.href='./?LED=OFF\' style='margin:auto;background-color: #626d78;color: snow;padding: 10px;width:85px;'>");
              client.println("OFF");
              client.println("</button>");
              client.println("<br/><br/>");
              client.println("<b>LED ESTATE= ");
              client.print(estate);
              client.println("</b><br/>");
              client.println("<br/><br/>");
              client.println("<h1 align='center'>FROM A WEB SERVER</h1>");
              client.println("<p></p><p></p><p></p>");
			           client.println("<div style='text-align: center;'><img src='https://www.educa2.madrid.org/web/educamadrid/principal/files/3df3efeb-7bc1-4392-8ee8-7eb01a160e8f/TOIS-based-.png?thumbnail=true' alt='logo' title='logo'></div>");
              client.println("</b></body>");
              client.println("</html>");
              break;
          }
          if (c == '\n') {
            currentLineIsBlank = true;
          }
          else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }
      }
       // give the web browser time to receive the data
      delay(1);
      client.stop();// close the connection:
    }
  }



