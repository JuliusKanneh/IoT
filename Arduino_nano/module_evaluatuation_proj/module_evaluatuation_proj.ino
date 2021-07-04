#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int trig_pin = 8;
int echo_pin = 9;
long duration, distance_cm;
int led = 12;
int alarm = 10;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(alarm, OUTPUT);
  lcd.begin(16,2);
  digitalWrite(alarm, HIGH);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  distance_cm = (duration/2) * 0.034;

  lcd.setCursor(0,0);
  
  lcd.print(distance_cm);
  lcd.print("cm");

//power on led if distance of obstacle is greatert than or equal to 50cm.
  if(distance_cm >= 50){
    lcd.setCursor(0,1);
    digitalWrite(led, HIGH);
    digitalWrite(alarm, HIGH);
    lcd.print("LED ON!");
  }else{
    lcd.setCursor(0,1);
    digitalWrite(led, LOW);
    digitalWrite(alarm, LOW);
    lcd.println("LED OFF!");
  }
  delay(250);
  //Serial.println(distance_cm);
}
