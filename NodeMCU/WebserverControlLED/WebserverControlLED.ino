//Include ESP8266 Wifi libray into the project
#include <ESP8266WiFi.h>

//My network credentials
const char* ssid = "CANALBOX-BA81";
const char* password = "8955819532";

//Set Digital pin for the LED
int LED = 5; //GPIO 5 meaning D1 pins 

//Set webserver port to 80, it is the default port
WiFiServer server(80);
  
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.println("Connecting to Wifi:");
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("Wifi Connected");
  server.begin(); //Starts the server
  Serial.println("Server Started:");
  Serial.print("Server IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
}

void loop() {
  
  WiFiClient client = server.available();
  if(!client){
    return;
  }

  //Waiting for client to connect to server
  Serial.println("Waiting for client");
  if(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');  
  Serial.println(request);
  client.flush();

  int value = LOW;
  if(request.indexOf("/LED=ON") != -1){
    digitalWrite(LED, HIGH); //Turn on LED

    value = HIGH;
    
  }

  if(request.indexOf("/LED=OFF") != -1){
    digitalWrite(LED, LOW);

    value = LOW;
  }

  /*----------HTML PAGE CODE ---------- */

  client.println("HTTP/1.1 200 ok");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
    client.println("<center>");
    client.println("<h2>Menya IOT LED Control</h2>");
    
    client.println("<br><br>");

    client.println("<a href=\"/LED=ON\"><button><h2>ON</h2></button></a>");
    client.println("<a href=\"/LED=OFF\"\"><button><h2>OFF</h2></button></a><br />");

    if(value == HIGH){
      client.print("<h2>LED ON</h2>");
    }else{
      client.print("<h2>LED OFF</h2>");
    }
    
    client.println("</center>");
  client.println("</html>");

  delay(1);
  Serial.println("client disconnected");
  Serial.println("");
}
