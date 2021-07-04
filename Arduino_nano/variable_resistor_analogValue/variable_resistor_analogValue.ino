int analog_pin = A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(analog_pin, INPUT); //set modeo of pin Analog0 (A0) as INPUT.
  Serial.begin(9600); //baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  int variable_resistor = analogRead(analog_pin); //reads the value from the pin of the potential meter and store it variable_resitor 
  Serial.println(variable_resistor); //print out the variable resistor read from the potentiometer.
}
