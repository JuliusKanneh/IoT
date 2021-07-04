int variable_pin = A0;
int led = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(variable_pin, INPUT);
  pinMode(led, OUTPUT);
  
  Serial.begin(9600); //setting baud rate 
}

void loop() {
  // put your main code here, to run repeatedly:
  int variable_resistor = analogRead(variable_pin);
  Serial.println(variable_resistor);

  //blink led if voltage is more than 500
  if(variable_resistor>500){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led,LOW);
  }
}
