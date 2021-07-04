#include <LiquidCrystal.h>

int value_set = 0;
int btn_state;
int sensor_value;
const int sensor_input = A0;
const int button = 12;
const int led1 = 10;
const int led2 = 11;
const int led3 = 9;

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  pinMode(button, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sensor_input, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  
}

void loop() {
  btn_state = digitalRead(button);
  sensor_value = analogRead(sensor_input);
  Serial.println(sensor_value);
  lcd.setCursor(0,0);
  lcd.print(sensor_value);
  
  lcd.setCursor(0,1);

  if(btn_state == HIGH){
    lcd.print(value_set += 10);
  }

  if(sensor_value >= value_set){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  delay(250);
}
