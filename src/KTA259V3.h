// Library for Ocean Controls KTA-259v3 Thermocouple Shield
// Requires Andy's MAX31855 Library
// by Andy Gock

#ifndef KTA259V3_H
#define KTA259V3_H

#if ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <wiring.h>
	#include "pins_arduino.h"
#endif

#include <SPI.h>
#include "MAX31855.h"

// Time to wait in milliseconds for signal to settle after switching channels on MUX
#define KTA259V3_MUX_WAIT 250

// Pins for ADG608R Multiplexer
#define KTA259V3_PIN_A0 4
#define KTA259V3_PIN_A1 5
#define KTA259V3_PIN_A2 6
#define KTA259V3_PIN_EN 7

class KTA259V3 : public Max31855 {
	private:
		uint8_t samples;

	public:
		/** Constructor */
		KTA259V3(uint8_t pin);

		/** Set amount of oversampling **/
		void set_oversampling(uint16_t samples);

		/** Select channel on MUX, use numbers 1 to 8 (not 0 to 7).
		  * PCB is has channels 1 to 8 marked on it. User must wait
		  * for signal to settle before reading it.
		  */
		void select_channel(uint8_t ch);
		
		/** Calls update() on parent class */
		void update(void);

		/** Selects channel, waits KTA259V3_MUX_WAIT, then updates _info */
		void update(uint8_t ch);

		/** Returns _info structure from last update */
		Max31855_Info get_info(void);

		/** Selects channel and update, then return _info structure */
		Max31855_Info get_info(uint8_t ch);
};

#endif
