#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "CANALBOX-BA81";
const char* password = "8955819532";

#define LDR_pin A0

WiFiClient client;
unsigned long myChannelNumber = 1401620; //My Channel Number 
const char* myWriteAPIKey = "DYFAW9OJDMPNMJEU"; //channel API key
 
void setup() {
  delay(1000);
  Serial.begin(9600);
  
  WiFi.begin(ssid, password); //begin wifi
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());
  
  ThingSpeak.begin(client);
  
}

void loop() {
  int LDR_value = analogRead(LDR_pin);
  ThingSpeak.writeField(myChannelNumber, 1, LDR_value, myWriteAPIKey); //Update in ThingSpeak
  Serial.println(LDR_value);
  delay(1500);
}
