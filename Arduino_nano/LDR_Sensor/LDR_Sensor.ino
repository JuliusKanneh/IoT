int ldr_sensor = A0;
void setup() {
  pinMode(ldr_sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensor_val = analogRead(ldr_sensor); //reading the intensity of light from the LDR sensor and storing values in the variable, sensor_val.
  Serial.println(sensor_val); //printing out the value from the read from the sensor to the digital monitor.
  delay(100);
}
