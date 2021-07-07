
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include "DHT.h"
#define DHTPIN 5     
#define DHTTYPE DHT11   // DHT 11
const char* ssid = "CANALBOX-DBD6"; //Your Network SSID
const char* password = "1316523275"; //Your Network Password
WiFiClient client;
unsigned long myChannelNumber =1437546; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "WN3Z3P57Q1S9R0LN"; //Your Write API Key
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  delay(1000);
  Serial.begin(9600);

  WiFi.begin(ssid, password); 
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());
  
  dht.begin();
  
  ThingSpeak.begin(client);
}

void loop()
{
  
  delay(2000);
 
  int h = dht.readHumidity(); 
  int t = dht.readTemperature(); 

  Serial.println("\nTemperature:");
  Serial.println(t);// printing the value of temp in the serial Monitor
  Serial.println("Relative Humidity");
  Serial.println(h);// printing the value of hum in the serial Monitor
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
}
