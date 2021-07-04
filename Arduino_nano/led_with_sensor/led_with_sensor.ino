int LED_sensor = A0;
int led = 13;

void setup() {
  pinMode(LED_sensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensor_val = analogRead(LED_sensor);
  Serial.println(sensor_val);

  if(sensor_val>=500){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
