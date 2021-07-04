int variable_pin = A0;
int led1 = 10;
int led2 = 13;
int led3 = 12;
int buzzer = 8;
void setup() {
  pinMode(variable_pin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600); //baud rate
}

void loop() {
  int voltage =analogRead(variable_pin);  //read voltage from the potentiometer(variable resistor)
  Serial.println(voltage); //display or print the voltage from the analog read.

  //turn on buzzer and led as alarm when the voltage reaches 1000 or more
  if(voltage>=1000){

    for(int interval = 200; interval <=600; interval+=100){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(buzzer, HIGH);
      delay(interval);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(buzzer, HIGH);
      delay(interval);
      digitalWrite(led1, LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(interval);
      digitalWrite(led1, LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(buzzer, LOW);
      delay(100);
    }

  }else{
    digitalWrite(led1, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(led2, LOW);
  }
}
