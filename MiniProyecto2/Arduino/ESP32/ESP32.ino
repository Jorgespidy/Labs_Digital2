// Adafruit IO Publish & Subscribe Example
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

// this int will hold the current count for our sketch
int count = 0;
uint8_t hora;
String cadena;


// Track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds.
//
// Because this sketch is publishing AND subscribing, we can't use a long
// delay() function call in the main loop since that would prevent io.run()
// from being called often enough to receive all incoming messages.
//
// Instead, we can use the millis() function to get the current time in
// milliseconds and avoid publishing until IO_LOOP_DELAY milliseconds have
// passed.
#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

// set up de los feeds feed
AdafruitIO_Feed *clocks = io.feed("clocks");
AdafruitIO_Feed *redled = io.feed("redled");
AdafruitIO_Feed *greenled = io.feed("greenled");

void setup() {

  // start the serial connection
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,16,17);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  
  //redled->onMessage(handleMessage);
  //greenled->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  //redled->get();
  //greenled->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
 while (1){
   if (Serial2.available()>0){
  Serial.println(Serial2.read());
   }
 }

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    // save count to the 'counter' feed on Adafruit IO
    Serial.print("sending -> ");
    Serial.println(cadena); //imprime con enter
    clocks->save(cadena);
    
   /* if (Serial2.available()>0){
      Serial2.write(1);
      cadena = "";
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      cadena = cadena + char(Serial2.read());
      Serial2.write(0);
    }*/
    
    // after publishing, store the current time
    lastUpdate = millis();
  }

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
