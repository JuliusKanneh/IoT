//My Libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
 
//My network credentials
const char* ssid = "DrWise";
const char* password = "kigalijulius";

//UR-SR04_0 pins for book-keeping
const int trig_pin = 5;
const int echo_pin = 4;

//UR-SR04_1 pins for visitors entry
const int trig_pin1 = 12;
const int echo_pin1 = 13;

//Book-keeping variables Ultrasonic sensor_0
long duration = 0;
long distance = 0;
long t_books_in = 0, t_books_out = 0, t_shelved_books = 0, t_books = 6;
int counter = 0;

//Visitor entry variables Ultrasonic sensor_1
long duration1 = 0;
long distance1 = 0; 
long p_in = 0, p_out = 0, t_visitors = 0; 

//Create an AsyncwebServer object on port 80
AsyncWebServer server(80);

unsigned long previousMillis = 0; //variable will hold the las time DHT was updated

const long interval = 10000; //updates DHT readings every 10 seconds 

//Declaring a global variable index_html[] to be stored in the flash using PRGOGMEM. 
//Not PROGMEM is an arduino feature that stores values of variables in the falsh instead of the RAM and calls it when needed. This saves the RAM space.
//BB: When declaring a variablem in PROGMEM using r"--()--", make sure to have the beginning and end the same. this is used to save raw string.
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="5"/>
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <script src="https://kit.fontawesome.com/7453cfc9cc.js" crossorigin="anonymous"></script>
  <link rel="stylesheet" href="style.css">
</head>

<body>
  <nav>
    <ul>
      <li><a href="#">Home</a></li>
      <li><a href="#">Books</a></li>
      <li><a href="#">Contact</a></li>
      <li><a href="#">About</a></li>
    </ul>
  </nav>
  
  <div>
    <h1>Welcome to Smart Library System</h1>
  </div>

  <div class="row">
  
    <div class="column">
      <div class="card">
        <i class="fas fa-walking"></i>
        <span class="title">People In </span>
        <br /> <br />
        <span id="p_in">%P_IN%</span>
      </div>
    </div>

    <div class="column">
      <div class="card">
        <i class="fas fa-walking"></i>
        <span class="title">People Out</span>
        <br /> <br />
        <span id="p_out">%P_OUT%</span>
      </div>
    </div>

    <div class="column">
      <div class="card">
        <i class="fas fa-book"></i>
        <span class="title">Total Shelved Book</span>
        <br /> <br />
        <span id="t_shelved_books">%T_SHELVED_BOOKS%</span>
      </div>
    </div>

    <div class="column">
      <div class="card">
        <i class="fas fa-book"></i>
        <span class="title">Total Books Out</span>
        <br /> <br />
        <span id="t_books_out">%T_BOOKS_OUT%</span>
      </div>
    </div>

    <div class="column">
      <div class="card">
        <i class="fas fa-book"></i>
        <span class="title">Total Books</span>
        <br /> <br />
        <span id="t_books">%T_BOOKS%</span>
      </div>
    </div>

    <div class="column">
      <div class="card">
        <i class="fas fa-book"></i>
        <span class="title">Total Visitors </span>
        <br /> <br />
        <span id="t_visitors">%T_VISITORS%</span>
      </div>
    </div>
    
  </div>

</body>
<script>
  //This is not working.
  //Interval to update the total books on shelve every 10000ms
  setInterval(function (){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
      if (this.readyState == 4 && this.status == 200){
        document.getElementById("t_shelved_books").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/t_shelved_books", true);
    xhttp.send();
  }, 5000 );

   setInterval(function (){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
      if (this.readyState == 4 && this.status == 200){
        document.getElementById("t_books_out").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/t_books_out", true);
    xhttp.send();
  }, 5000 );

</script>
)rawliteral";

//CSS
const char style_css[] PROGMEM = R"rawliteral(
   * {
        box-sizing: border-box;
    }
    
    body {
        margin: 5px 20px;
        font-family: Arial, Helvetica, sans-serif;
    }

    h1 {
        color: blue;
        text-align: center;
    }

    nav ul {
        list-style-type: none;
        margin: 0;
        padding: 0;
        overflow: hidden;
        background-color: #333333;
    }

    nav ul li {
        float: left;
    }

    nav ul li a {
        display: block;
        color: white;
        text-align: center;
        padding: 14px 16px;
        text-decoration: none;
    }

    nav li a:hover {
        background-color: #111111;
    }

    /* Float four columns side by side */
    .column {
        float: left;
        width: 25%;
        padding: 0 10px;
        margin: 5px;
    }

    /* Remove extra left and right margins, due to padding in columns */
    .row {
        margin: 0, -5px;
        align-items: center;
    }

    /* Clear floats after the columns */
    .row:after {
        content: "";
        display: table;
        clear: both;
    }

    .card {
        box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2); /* this adds the "card" effect */
        padding: 16px;
        text-align: center;
        background-color: #f1f1f1;
    }

    .card:hover {
        box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2);
    }

    /* Responsive columns - one column layout (vertical) on small screens */
    @media screen and (max-width: 600px) {
    .column {
      width: 100%;
      display: block;
      margin-bottom: 20px;
    }
  }

  .title {
      color: #111111;
      font-size: 20px;
      font-weight: bold;
  }
    
  h2 { font-size: 3.0rem; }
  p { font-size: 3.0rem; }
  .units { font-size: 1.2rem; }
  .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
  }
)rawliteral";

//Replaces placeholder with the total books value
String processor(const String& var){
  Serial.println(var);
  if(var == "T_BOOKS"){
    return String(t_books);
    Serial.print("Total Books");
  }else if(var == "P_IN"){
    return String(p_in);
    Serial.println("PEOPLE IN");
  }else if(var == "P_OUT"){
    return String(p_out);
    Serial.println("PEOPLE OUT");
  }else if(var == "T_BOOKS_OUT"){
    return String(t_books_out);
    Serial.println("TOTAL BOOKS OUT");
  }else if(var == "T_SHELVED_BOOKS"){
    return String(t_shelved_books);
    Serial.println("TOTAL SHELVED BOOKS");
  }else if(var == "T_VISITORS"){
    return String(t_visitors);
    Serial.println("TOTAL VISITORS");
  }
  
  return String();
}

void setup() {
  //generating and receiving ultrasounds for Ultrasonic sensor_0
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  //generating and receiving ultrasounds for Ultrasonic sensor_1
  pinMode(trig_pin1, OUTPUT);
  pinMode(echo_pin1, INPUT);
  
  Serial.begin(115200);

  //Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println(".");
  }

  //Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

//Figure out how to have the a seperate method to handle just the rendering of the html page. 

  //Route for root / webpage (HTML handler)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  
   //CSS handler
   //Try to reduce to method to serve only its function if possible.
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", style_css);
    });
    
  //Route for distance
  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(distance).c_str());
    });

  //Route for to total books 
  server.on("/t_books", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t_books).c_str());
    });

  server.on("/p_in", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(p_in).c_str());
    });

  server.on("/p_out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(p_out).c_str());
    });

  server.on("/t_shelved_books", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t_shelved_books).c_str());
    });

  server.on("/t_visitors", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t_visitors).c_str());
    });

  server.on("/t_books_out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t_books_out).c_str());
    });
    
    //Start Server
    server.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    //save the last time you updated the DHT value
    previousMillis = currentMillis;

    //Read total time taken for ultrasound to travel to and fro using ultrasonic sensor_0
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    duration  = pulseIn(echo_pin, HIGH);

    //Read total time taken for ultrasound to travel to and fro using ultrasonic sensor_1
    digitalWrite(trig_pin1, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin1, LOW);
    duration1  = pulseIn(echo_pin1, HIGH);

    //calculating distance using ultrasonic sensor_0
    if(isnan(duration)){
      Serial.println("Failed to read from Ultrasonic sensor_1");
    }else{
      distance = (duration/2)*0.034;
      Serial.println(distance);
    }

    //calculating distance1 using ultrasonic sensor_1
    if(isnan(duration1)){
      Serial.println("Failed to read from Ultrasonic sensor_1");
    }else{
      distance1 = (duration1/2)*0.034;
      Serial.println(distance1);
    }

    //Calculating the total number of books on shelve
    if(distance>= 28 && distance <= 30){
      t_shelved_books = 0;
    }else if(distance >= 24 && distance <= 26){
      t_shelved_books = 1;
    }else if(distance >= 20 && distance <= 22){
      t_shelved_books = 2;
    }else if(distance >= 16 && distance <= 18){
      t_shelved_books = 3;
    }else if(distance >= 12 && distance <= 14){
      t_shelved_books = 4;
    }else if(distance >= 8 && distance <= 10){
      t_shelved_books = 5;
    }else if(distance >= 4 && distance <= 6){
      t_shelved_books = 6;
    }else{
      Serial.println("Book size out of range!");
    }

    //Calculating total books out
    t_books_out = t_books - t_shelved_books;

    //checking if calculation of total books on shelve was successful
    if(isnan(t_shelved_books)){
      Serial.println("Failed to Calculate Total Books!");
    }else{
      Serial.println(t_shelved_books);
    }

    //counting the number of visitors
    Serial.println("Distance from sensor_0");
    Serial.println(distance1);

    if(distance1 >= 40 && distance1 <= 100){
      counter = counter + 1;
      Serial.println(counter);
      
    }
    t_visitors = counter;
    Serial.println(t_visitors);
  }
}
