const int TRIG_PIN = 5;
const int ECHO_PIN = 4;
const int LED = 0;
const int BUZZER = 2;

long duration, distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2)*0.034;
  Serial.println("Duration: ");
  Serial.println(duration);
  Serial.println("Distance of the object in cm: ");
  Serial.println(distance);

  if(distance < 500){
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }else{
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
  }
}
