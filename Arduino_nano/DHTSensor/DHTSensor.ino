#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  Serial.println(F("DHTxx Text"));
  dht.begin();
}

void loop(){
  //wait a few seconds between measurement
  delay(2000);

  //Reading temperature or humidity takes about 250 milliseconds!
  //Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //Read temeperature as Celcius (default)
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println(" ");
  Serial.println(F("Temperature: "));
  Serial.print(t);
  Serial.println(" ");
}
