#include <dht.h>
#define dht_apin A0
dht DHT;

int relay_sensor = 10;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("DHT11 Humidity and Temperaure sensor\n\n");
  delay(1000);
  pinMode(relay_sensor, OUTPUT);
}

void loop() {
  DHT.read11(dht_apin);
  int temp = DHT.temperature; 
  int r_humidity = DHT.humidity;
  Serial.print("Current Humidity = "); 
  Serial.print(r_humidity);
  Serial.print("%");
  Serial.print("Current Temperature = ");
  Serial.print(temp);
  Serial.println(" C");
  delay(500);

  if(r_humidity > 65){
    digitalWrite(relay_sensor, HIGH);
  }else{
    digitalWrite(relay_sensor, LOW);
  }
}
