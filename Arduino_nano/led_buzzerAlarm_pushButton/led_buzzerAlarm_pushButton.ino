int push_button = 10;
int led1 = 13;
int led2 = 6;
int buzzer =8;

void setup() {
  pinMode(push_button, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); //baud rate to read value from serial monitor(optional)
}

void loop() {
  int button_status = digitalRead(push_button);
  Serial.println(button_status);
  if(button_status==HIGH){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);
  }else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(buzzer, LOW);
  }
}
