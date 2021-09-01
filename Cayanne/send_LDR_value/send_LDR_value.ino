#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

//WiFi Credential (Connect to WiFi)
char ssid[] = "CANALBOX-DBD6";
char wifi_password[] = "1316523275";

//Cayenne Credentials 
char username[] = "00be5fb0-0976-11ec-9b2d-abd5fca49150";
char password[] = "b38634a5f495ea8fd5bc897f7864c056a615186a";
char clientID[] = "ebab7190-0983-11ec-9a6a-b964661ada9f";

int ldr = A0;
int ldr_data;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifi_password);
  pinMode(A0, INPUT);
}

void loop() {
  Cayenne.loop();
  ldr_data = analogRead(ldr);
  Serial.println(ldr_data);
//  virtualWrite(channel_number, value, "type value", "unit value");
  //or use map form 0 to 100
//  Cayenne.virtualWrite(1, map(ldr_data, 0, 1024, 0, 100));
  Cayenne.virtualWrite(2, ldr_data);
}

CAYENNE_IN(0) {
  
}
