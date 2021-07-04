//int push_button = A0; //used with anolog input
int push_button = 10; //used with digital input
int led=13;
void setup() {
  pinMode(push_button, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600); //set the baud rate (this is the speed of data transmission in a system)
}

void loop() {
  
 /* //using analog to read value from push button
  int button_status = analogRead(push_button); //reading the value from analog input(used to read values with variable resistors)
  Serial.println(button_status); //print the value from the input using serial monitor
 */

 //using digital input to read value from push button
  int button_status = digitalRead(push_button); //read digital value fromt he push button(either 0 or 1) and save it in variable button_status
  Serial.println(button_status); //printout the value of variable button_status to serial monitor.
}
