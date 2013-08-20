//
// Example:
//   Display temperature of each connected channel
//

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
			//Serial.print("Ch=");
			//Serial.print(channel);
			//Serial.println(" Open Circuit");
		} else if (tc.get_error() & MAX31855_SHORT_GND) {
			//Serial.print("Ch=");
			//Serial.print(channel);
			//Serial.println(" Shorted to GND");
		} else if (tc.get_error() & MAX31855_SHORT_VCC) {
			//Serial.print("Ch=");
			//Serial.print(channel);
			//Serial.println(" Shorted to VCC");
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

