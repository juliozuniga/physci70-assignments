/*
* Simple sketch for nRF24L01+ radios.  Transmit side.
*
*For Huzzah ESP32 from adafruit
* CE:  pin 32
* CSN os SS: pin 14 
* Updated: Dec 2014 by TMRh20. Simplified Mar 2019 RMH.
*/

#include <SPI.h>
#include "RF24.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus CE and CS */
RF24 radio(7,8);      //CE and CS pins.  This is the change needed when you change to another board.

byte addresses[][6] = {"1Node","2Node"};
byte data = 0; 

void setup() {
 Serial.begin(115200);
 Serial.println("RF24example:  Simple tx");
  
  radio.begin();

 // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
 
}

void loop() {
  
Serial.println("Now sending");

  
                           
  if (!radio.write( &data, 1 )){
  Serial.println(F("failed"));
   }
        
data = (analogRead(A2))/16;   //default is 12 bits for ESP32 ADC, so divide by 16 to map to one byte.
  //data++;
Serial.print("Sent ");
Serial.println(data);
   


delay(5);

} // loop end
