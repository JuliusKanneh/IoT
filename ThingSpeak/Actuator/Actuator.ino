#include <ThingSpeak.h> 
#include <ESP8266WiFi.h> 
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Your network credentials
const char* ssid = "CANALBOX-DBD6";    //  Your Wi-Fi Name 
const char* password = "1316523275";   // Wi-Fi Password 

//  GPIO 5 meaning D1 pins 
int Red = 5;   
//  GPIO 4 meaning D2 pins 
int Yellow = 4;
//  GPIO 0 meaning D3 pins 
int Green = 0;

//change your channel number here
unsigned long channel=1442247;
//1,2 and 3 are channel fields. You don't need to change if you are following this tutorial. However, you can modify it according to your application
unsigned int led1= 1;
unsigned int led2= 2;
unsigned int led3= 3;

WiFiClient  client;

void setup() {
  Serial.begin(115200); //Default Baudrate 
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);
  
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
  digitalWrite(D3, 0);
  
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);

}

void loop() {
  //get the last data of the fields
  int led_1 = ThingSpeak.readFloatField(channel, led1);
  int led_2 = ThingSpeak.readFloatField(channel, led2);
  int led_3 = ThingSpeak.readFloatField(channel, led3);

  if(led_1 == 1){
    digitalWrite(D1, 1);
    Serial.println("D1 is On..!");
  }else if(led_1 == 0){
    digitalWrite(D1, 0);
    Serial.println("D1 is Off..!");
  }

  if(led_2 == 1){
    digitalWrite(D2, 1);
    Serial.println("D2 is On..!");
  }else if(led_2 == 0){
    digitalWrite(D2, 0);
    Serial.println("D2 is Off..!");
  }

  if(led_3 == 1){
    digitalWrite(D3, 1);
    Serial.println("D3 is On..!");
  }else if(led_3 == 0){
    digitalWrite(D3, 0);
    Serial.println("D3 is Off..!");
  }

  Serial.println(led_1);
  Serial.println(led_2);
  Serial.println(led_3);
  delay(500);
  
}
