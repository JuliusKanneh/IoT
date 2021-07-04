int trig_pin = 2;
int echo_pin = 4;
int alarm = 6;
int led = 10;
long duration, cm;
void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(alarm, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  cm = (duration/2)*0.034;  

  Serial.println(cm);
  Serial.println("cm");
  Serial.println();

  delay(250);
    
  if(cm>0 && cm<=25){
    digitalWrite(alarm, HIGH);
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(alarm, LOW);
    digitalWrite(led, LOW);
    delay(200);
  }else{
    digitalWrite(alarm, LOW);
    digitalWrite(led, LOW);
  }
}
