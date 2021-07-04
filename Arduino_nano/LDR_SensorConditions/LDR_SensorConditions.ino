97int LDR_Sensor = A0;
int led1 = 10;
int led2 = 11;
int led3 = 12;
void setup() {
  pinMode(LDR_Sensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensor_val = analogRead(LDR_Sensor);
  Serial.println(sensor_val);

  if(sensor_val<=300){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }else if(sensor_val<=600){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }else if(sensor_val<=1023){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
}
