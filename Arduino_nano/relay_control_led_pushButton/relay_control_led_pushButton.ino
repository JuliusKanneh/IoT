int relay_signal = 2;
int led = 10;
int push_button = 5;
void setup() {
  pinMode(relay_signal, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(push_button, INPUT);
}

void loop() {
  int button_signal = digitalRead(push_button);
  if(button_signal == 1){
    digitalWrite(relay_signal, HIGH);
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(relay_signal, LOW);
    digitalWrite(led, LOW);
  }
}
