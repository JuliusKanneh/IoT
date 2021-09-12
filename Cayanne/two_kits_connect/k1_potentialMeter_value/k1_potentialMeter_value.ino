#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

//WiFi network info.
char ssid[] = "CANALBOX-BA81"; 
char wifiPassword[] = "8955819532";
            
            
// Cayenne Device authentication info
char username[] = "00be5fb0-0976-11ec-9b2d-abd5fca49150"; 
char password[] = "b38634a5f495ea8fd5bc897f7864c056a615186a"; 
char clientID[] = "74ac1450-0bea-11ec-9b2d-abd5fca49150";
            
//Variables for DHT11 values
int Potentiometer = A0; 
int Potentiometer_data;
            
void setup() {

Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
            
  pinMode(A0,INPUT);

}
            
void loop() {
            
Cayenne.loop();

  Potentiometer_data = analogRead(Potentiometer);

  //virtualWrite(channel_number, value, "type value", "unit value")
  Cayenne.virtualWrite(1, Potentiometer_data);
            
  delay(1000);
}
