KTA-259v3 Arduino Library
=========================

Library for Ocean Controls KTA-259v3 Thermocouple Shield

New Installation
----------------

To install in Arduino 1.x, go to your workspace directory, open "libraries" and create a new directory
'KTA259V3". Copy the files from this library into there.

Update Existing Installation
----------------------------

Copy files from this repository into directory 'KTA259V3" in your workspace's "libraries"
directory.

Install using git
-----------------

To install in Arduino 1.x, go to your workspace directory, open "libraries". Run command:

	git clone https://github.com/andygock/KTA259V3.git

Quick Example
-------------

	#include <SPI.h>
	#include "MAX31855.h"
	#include "KTA259V3.h"

	// We can reduce enabled channels for faster operation
	#define CHANNELS_ENABLED 8

	KTA259V3 tc = KTA259V3(9); // Init with chip select on pin 9

	void setup()
	{
		Serial.begin(115200);
	}

	void loop() {
		uint8_t channel;

		for (channel=1; channel<=CHANNELS_ENABLED; channel++) {
			tc.select_channel(channel);
			delay(200);
			tc.update();

			if (tc.get_error() & MAX31855_OPEN_CIRCUIT) {
				Serial.print("Ch=");
				Serial.print(channel);
				Serial.println(" Open Circuit");
			} else if (tc.get_error() & MAX31855_SHORT_GND) {
				Serial.print("Ch=");
				Serial.print(channel);
				Serial.println(" Shorted to GND");
			} else if (tc.get_error() & MAX31855_SHORT_VCC) {
				Serial.print("Ch=");
				Serial.print(channel);
				Serial.println(" Shorted to VCC");
			} else {
				// No errors
				Serial.print("Ch=");
				Serial.print(channel);			
				Serial.print(" Temp=");
				Serial.print(tc.get_temperature());
				Serial.print(" Ref=");
				Serial.println(tc.get_cold_junction_temperature());		
			}
		}
	}  
	