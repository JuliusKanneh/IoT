int LED = 10;
int BUZZER = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);
  delay(1000);
}
