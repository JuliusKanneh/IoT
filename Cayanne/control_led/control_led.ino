#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

//WiFi setup
char ssid[] = "CANALBOX-DBD6";
char wifi_password[] = "1316523275";

//Cayenne Configuraion
char username[] = "00be5fb0-0976-11ec-9b2d-abd5fca49150";
char password[] = "b38634a5f495ea8fd5bc897f7864c056a615186a";
char clientID[] = "ebab7190-0983-11ec-9a6a-b964661ada9f";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifi_password);
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(16, HIGH);
}

void loop() {
  Cayenne.loop();
}

CAYENNE_IN(0) {
  digitalWrite(16, getValue.asInt()); //receiving the state/value of channel[0] and powering on/off the led based on the value received (0/1)
}

CAYENNE_IN(1) {
  digitalWrite(5, getValue.asInt());
}
