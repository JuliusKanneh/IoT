const int relay_switch=2;

void setup() {
  pinMode(relay_switch, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(relay_switch, HIGH);
  delay(1000);
  digitalWrite(relay_switch, LOW);
}
