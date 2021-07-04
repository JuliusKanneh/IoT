int trig_pin = 2; //Trig
int echo_pin = 4; //Echo
long duration, cm; 
void setup() {
  pinMode(trig_pin, OUTPUT); //Set trig to OUTPUT
  pinMode(echo_pin, INPUT); //Set Echo to INPUT
  Serial.begin(9600); //Serial port begins at this baud rate 
}

void loop() {
  //The sensor is trigger by a HIGH pulse of 10 or more microseconds.
  //Give a short LOW inpuls beforehand to ensure a clean HIGH pulse.
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  //Read the signal from the sensor: a HIGH pulse whose duration is a time (in microseconds) 
  //from the sending of the pin to the reception of its echo off an object.
  duration = pulseIn(echo_pin, HIGH);

  //Convert the time into a distance 
  cm = (duration/2)*0.0343;

  if(cm>=0 && cm<=400){
    Serial.println(cm);
    Serial.println("cm");
    Serial.println();

    delay(250);
  }else{
    Serial.println("Object out of range!");
  }
  
}
