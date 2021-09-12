#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>

//WiFi Credential (Connect to WiFi)
char ssid[] = "CANALBOX-DBD6";
char wifi_password[] = "1316523275";

//Cayenne Credentials 
char username[] = "00be5fb0-0976-11ec-9b2d-abd5fca49150";
char password[] = "b38634a5f495ea8fd5bc897f7864c056a615186a";
char clientID[] = "5ad07260-137e-11ec-9b2d-abd5fca49150";

//Capacitive soil moisture sensor setings
//-------------------------------------------------------------//
int sensor_pin = A0;
const int constant_value_in_air  = 0; //this is must be higher than the value in water
const int constant_value_in_water = 0; //this must be lower than the value in air.
int moisture_value = 0;
float sensor_voltage = 0;
int soil_moisture_percent = 0;

//DHT 11 Settings
//-------------------------------------------------------------//
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//Variables to hold temperature and humidity
float t;
float h;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifi_password);
  dht.begin();
  pinMode(A0, INPUT);
}

void loop() {
  Cayenne.loop();
  moisture_value = analogRead(sensor_pin);

  t = dht.readTemperature();
  h = dht.readHumidity();

//  Displaying to Serial Monitor
  Serial.println(moisture_value);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("C");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  
//  virtualWrite(channel_number, value, "type value", "unit value");
  //or use map form 0 to 100
//  Cayenne.virtualWrite(1, map(ldr_data, 0, 1024, 0, 100));


//  Pushing sensors values to Cayene dashboard
//-------------------------------------------------------------//
  Cayenne.virtualWrite(0, moisture_value);
  Cayenne.virtualWrite(1, t);
  Cayenne.virtualWrite(2, h);
}

CAYENNE_IN(0) {
  
}
