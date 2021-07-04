int relay_signal = 11;
int led = 12;
void setup() {
  pinMode(relay_signal, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(relay_signal, HIGH); //set relay signal to HIGH
  digitalWrite(led, HIGH);
  delay(1000);
  
  digitalWrite(relay_signal, LOW);
  digitalWrite(led, LOW);
  delay(1000);
}  
