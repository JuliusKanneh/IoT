#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

ESP8266WebServer server(80);

//Make my own wifi name and password as access point
const char *ssid = "DrWiseAP";
const char *access_key = "myAccess2021";

#define LED 5
int statusLED = LOW; //status of LED whenever power is given to NODEMCU

//---------------Declaring constants to make the page to be visited.---------------
const String HtmlHtml = "<html> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /> </head> </html>";
const String HtmlTitle = "<h1>Control LED Using NodeMCU WiFi Access Point on Menya IoT kit</h1><br />\n";
const String HtmlLedStateLow = "<big>LED is now <b>OFF</b> </big><br /><br />\n";
const String HtmlLedStateHigh = "<big>LED is now <b>ON</b> </big><br /><br />\n";
const String HtmlButtons = "<a href=\"LEDOn\"><button style=\"background-color:green; color:white; width:20%; height:5%;\">ON</button></a>\n"
                            "<a href=\"LEDOff\"><button style=\"background-color:red; color:white; width:20%; height:5%;\">OFF</button></a><br />";
const String HtmlHtmlClose = "</html>";
//----------------------------------------------------------------------------------

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Testing: ");
  
  WiFi.softAP(ssid, access_key); //Make the device a hotspot or access point

  IPAddress apip = WiFi.softAPIP(); //Get the IP of the server
  Serial.println("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //Prints the IP address of the server to be visited in the Serial Monitor
  Serial.println(" in your browser.");

  server.on("/", response);
  server.on("/LEDOn", handleLedOn);
  server.on("/LEDOff", handleLedOff);

  server.begin(); //Starts the server
  Serial.println("HTTP server beginned");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, statusLED);
}

//Function to turn on the LED
void handleLedOn(){
  statusLED = HIGH; //condition to make the LED turn on 
  digitalWrite(LED, statusLED);
  Serial.println("NodeMCU ESP8266 is ON");
  response(); 
}

//Function to turn of the LED
void handleLedOff(){
  statusLED = LOW;
  digitalWrite(LED, statusLED);
  Serial.println("NodeMCU ESP8266 is OFF");
  response();
}

//Function to handle each client making request
void response(){
  String htmlRes = HtmlHtml + HtmlTitle; //initial web page
  if(statusLED == HIGH){
    htmlRes += HtmlLedStateHigh; // displays the htmlRes initial + the status "LED is OFF" and saves both the result back in htmlRes.
  }else{
    htmlRes += HtmlLedStateLow; // displays the htmlRes initial + the status "LED is ON" and saves the result back in the htmlRes.
  }

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void loop() {
  server.handleClient(); //call this when you make a request by inserting the IP in the browser.
}
