#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network information
char ssid[] = "CANALBOX-DBD6";
char wifi_password[] = "1316523275";

//Cayenne authentication info from the Cayenne Dashboard
char username[] = "00be5fb0-0976-11ec-9b2d-abd5fca49150";
char password[] = "b38634a5f495ea8fd5bc897f7864c056a615186a";
char clientID[] = "ebab7190-0983-11ec-9a6a-b964661ada9f";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifi_password);
}

void loop() {
  Cayenne.loop();
}
