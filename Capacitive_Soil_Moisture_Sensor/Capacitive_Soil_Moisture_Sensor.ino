//int soil_pin = A0;

//Censor Calibration for accuracy
const int constant_in_AirValue = 1023;
const int constant_in_waterValue = 0;

int soilMoistureValue = 0;
int soilMoisuturePercent = 0;
float sensor_voltage = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  soilMoistureValue = analogRead(A0);
  Serial.print("Soil Moisture Sensor Value: ");
  Serial.println(soilMoistureValue);

  sensor_voltage = (soilMoistureValue / 1023.0) * 3.3;
  Serial.print("Sensor Voltage: ");
  Serial.print(sensor_voltage);
  Serial.println(" V");
  
  soilMoisuturePercent = map(soilMoistureValue, constant_in_AirValue, constant_in_waterValue, 0, 100);
  if(soilMoisuturePercent >= 100){
    Serial.println("100 %");
  }else if(soilMoisuturePercent <= 0){
    Serial.println("0 %");
  }else if(soilMoisuturePercent >0 && soilMoisuturePercent < 100){
    Serial.println(soilMoisuturePercent);
    Serial.println("%");
  }
  
  delay(250); //slight delay between readings
}
