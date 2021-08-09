#include <ESP8266WiFi.h>;
 #include <WiFiClient.h>;
 #include <ThingSpeak.h>;
 const char* ssid = "your_ssid"; //Your Network SSID
 const char* password = "your_pass"; //Your Network Password
 WiFiClient client;
 unsigned long myChannelNumber =your_channel_number; //Your Channel Number (Without Brackets)
 const char * myWriteAPIKey = "your_write_api_key"; //Your Write API Key

 void setup() {
  delay(1000);

  Serial.begin(9600);
  
  ThingSpeak.begin(client); 
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

void loop(){
  int LDR_value =analogRead(A0);
   
  ThingSpeak.writeField(myChannelNumber, 1,LDR_value, myWriteAPIKey); //Update in ThingSpeak 
  //                    (myChannelNumber,Field_number, myWriteAPIKey)
  Serial.println(LDR_value);

  delay(1500);
}
