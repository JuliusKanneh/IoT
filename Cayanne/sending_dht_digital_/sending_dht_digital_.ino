#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

//WiFi Connection Info
char ssid[] = "CANALBOX-DBD6";
char wifi_password[] = "1316523275";

//Cayenne Authentication 
char username[] = "00be5fb0-0976-11ec-9b2d-abd5fca49150";
char password[] = "b38634a5f495ea8fd5bc897f7864c056a615186a";
char clietID[] = "ebab7190-0983-11ec-9a6a-b964661ada9f";

DHT dht(DHTPIN, DHTTYPE);

//Variales to hold the temperature and humidity 
float h;
float t;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clietID, ssid, wifi_password);
  dht.begin();
}

void loop() {
  Cayenne.loop();
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print(h);
  Serial.println("%");
  Serial.print(t);
  Serial.println("c");

  Cayenne.virtualWrite(3, h);
  Cayenne.virtualWrite(4, t);

  delay(2000);
}
