//My Libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
 
//My network credentials
const char* ssid = "DrWise";
const char* password = "kigalijulius";

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); //declaring the DHT11 sensor passing its pin and type as parameter

//Read current temperature & humidity
float t = 0.0;
float h = 0.0;

//Create an AsyncwebServer object on port 80
AsyncWebServer server(80);

unsigned long previousMillis = 0; //variable will hold the las time DHT was updated

const long interval = 10000; //updates DHT readings every 10 seconds 

//Declaring a global variable index_html[] to be stored in the flash using PRGOGMEM. 
//Not PROGMEM is an arduino feature that stores values of variables in the falsh instead of the RAM and calls it when needed. This saves the RAM space.
//BB: When declaring a variablem in PROGMEM using r"--()--", make sure to have the beginning the same. this is used to save raw string.
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
      font-family: Arial;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP8266 HDH Server </h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
    <span class ="dht-labels">Temperature</span>
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;" ></i>
    <span class="dht-label">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
  setInterval(function (){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
      if (this.readyState == 4 && this.status == 200){
        document.getElementById("temperature").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
  }, 10000 );

  setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readystatechange == 4 && this.status == 200) {
        document.getElementById("humidity").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/humidity", true);
    xhttp.send();
  }, 10000 );
</script>
)rawliteral";

//Replaces placeholder with DHT values
String processor(const String& var){
  Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  //Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println(".");
  }

  //Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  //Route for root / webpage
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
    });

    //Route for temperature
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(t).c_str());
      });

    //Route for humidity
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(h).c_str());
      });

    //Start Server
    server.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    //save the last time you updated the DHT value
    previousMillis = currentMillis;

    //Read temperature as Celcius (the default)
    float newT = dht.readTemperature();
    //If temperature read failed, don't change t value
    if(isnan(newT)){
       Serial.print("Failed to read from DHT sensor!");
    }else{
      t = newT;
      Serial.println(t);
    }

    //Read Humidity
    float newH = dht.readHumidity();
    //if humidity read failed, don't change h value
    if (isnan(newH)){
      Serial.println("Failed to read from DHT sensor!");
    }else{
      h = newH;
      Serial.println(h);
    }
  }
}
