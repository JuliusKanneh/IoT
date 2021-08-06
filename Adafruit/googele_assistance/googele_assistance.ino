// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 5
int led_pin = 5;
int led1_pin = 4;

// set up the 'digital' feed
AdafruitIO_Feed *LED = io.feed("LED");

void setup() {

  // set button pin as an input
  pinMode(led_pin, OUTPUT);
  pinMode(led1_pin, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

   // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  LED->onMessage(handleMessage);
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  LED->get();
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

void handleMessage(AdafruitIO_Data *data) {
  
  Serial.print("received <- ");

  if(data->toPinLevel() == HIGH){
    Serial.println("HIGH");
    digitalWrite(led1_pin, HIGH);
  }else{
    Serial.println("LOW");
    digitalWrite(led1_pin, LOW); 
  }

  //Write the current state to the led
  digitalWrite(led_pin, data->toPinLevel());
}
