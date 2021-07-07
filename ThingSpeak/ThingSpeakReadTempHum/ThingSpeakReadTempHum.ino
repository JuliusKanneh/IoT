#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN 5     
#define DHTTYPE DHT11 
const char ssid[] = "CANALBOX-DBD6";
const char pass[] = "1316523275";
WiFiClient client;

//---------------- Chanel Details-----------------//
unsigned long statusCode;
unsigned long counterChannelNumber = 1437546; //Channel ID
const char * myCounterReadAPIKey = "N8G2B6NIBZRT3CGC"; //Read API Key
const char * myWriteAPIKey = "WN3Z3P57Q1S9R0LN"; //Write API Key
const int FieldNumber1 = 1; //Field 1
const int FieldNumber2 = 2; //Field 2
//-------------------------------------------------//

DHT dht(DHTPIN, DHTTYPE); //initializing DHT

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  dht.begin(); //starting the DHT sensor
  ThingSpeak.begin(client);
}

void loop() {
  //-------------------Network-----------------------//
  
  if (WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.print(" .... ");
    while (WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Successfully.");
  }
  //-----------------End of Netowrk Connection ---------//


  //----- Sending Data to Channel 1--------------------//
  int t = dht.readTemperature(); 
  ThingSpeak.writeField(counterChannelNumber, 1, t, myWriteAPIKey);
  
  //------ End of sending data to channel 1 -----------//

  
  //----- Sending data to channel 2 ------------------//
  
  int h = dht.readHumidity();
  ThingSpeak.writeField(counterChannelNumber, 2, h, myWriteAPIKey);

  //---------------End of sending data to channel 2-----------------//

  
  //-----------------Reading data from Channel 1 ------------------------//
  
  long temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.print("Temperature: ");
    Serial.print(temp);
  }else{
    Serial.println("Unable to read temperature / No internet connection");
  }
  delay(100);
  
  //------------------ End of reading data from Channel 1 -----------------//

  
  //----------------- Reading data from Channel 2 ------------------------//
  long hum = ThingSpeak.readLongField(counterChannelNumber, FieldNumber2, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode ==200){
    Serial.print("Humidity: ");
    Serial.println(hum);
  }
  delay(100);
  
  //----------------------End of rading data from Channel 2 -----------------//
}
