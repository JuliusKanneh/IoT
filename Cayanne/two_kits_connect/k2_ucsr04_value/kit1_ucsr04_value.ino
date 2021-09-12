#define CAYENNE_PRINT Serial
            #include <CayenneMQTTESP8266.h>
                    
            
            //WiFi network info.
            char ssid[] = "ssid"; //Replace with your network name
            char wifiPassword[] = "wifiPassword"; //Replace with your Password network
            
            
            // Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
            char username[] = "MQTT_USERNAME"; //Replace with MQTT Username
            char password[] = "MQTT_PASSWORD"; //Replace with MQTT Password
            char clientID[] = "CLIENT_ID"; //Replace with CLIENT ID
            
            
            
            //Variables for DHT11 values
            
            int Potentiometer = A0; 
            int Potentiometer_data;
            
            void setup() {
            
            Serial.begin(9600);
            Cayenne.begin(username, password, clientID, ssid, wifiPassword);
            
            pinMode(A0,INPUT);
            }
            
            void loop() {
            
            Cayenne.loop();
            
            
             Potentiometer_data = analogRead(Potentiometer);
            //virtualWrite(channel_number, value, "type value", "unit value")
            Cayenne.virtualWrite(4, Potentiometer_data);
            
             delay(1000);
            }
