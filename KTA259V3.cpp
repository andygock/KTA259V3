// Library for Ocean Controls KTA-259v3 Thermocouple Shield
// Requires Andy's MAX31855 Library
// by Andy Gock

#include "KTA259V3.h"

// Constructor
KTA259V3::KTA259V3(uint8_t pin) : Max31855(pin) {

	// Set up multiplexer
	pinMode(KTA259V3_PIN_A0, OUTPUT);
	pinMode(KTA259V3_PIN_A1, OUTPUT);
	pinMode(KTA259V3_PIN_A2, OUTPUT);
	pinMode(KTA259V3_PIN_EN, OUTPUT);

	digitalWrite(KTA259V3_PIN_A0, 0);
	digitalWrite(KTA259V3_PIN_A1, 0);
	digitalWrite(KTA259V3_PIN_A2, 0);
	digitalWrite(KTA259V3_PIN_EN, 0); // Multiplexer off on start up
}

// Select channel on multiplexer, channel 1 to 8 (not 0 to 7)
// PCB is marked with 1 to 8, so we'll use that
void KTA259V3::select_channel(uint8_t ch) {
	// Turn MUX off (probably don't need to do this)
	digitalWrite(KTA259V3_PIN_EN, 0);

	if ((ch-1) & 0x01) {
		digitalWrite(KTA259V3_PIN_A0, 1);
	} else {
		digitalWrite(KTA259V3_PIN_A0, 0);
	}
	if ((ch-1) & 0x02) {
		digitalWrite(KTA259V3_PIN_A1, 1);
	} else {
		digitalWrite(KTA259V3_PIN_A1, 0);
	}
	if ((ch-1) & 0x04) {
		digitalWrite(KTA259V3_PIN_A2, 1);
	} else {
		digitalWrite(KTA259V3_PIN_A2, 0);
	}

	// Turn MUX on
	digitalWrite(KTA259V3_PIN_EN, 1);
}

// Update reading now
void KTA259V3::update(void) {
	Max31855::update();
}

// Select channel number and update reading
void KTA259V3::update(uint8_t ch) {
	select_channel(ch);
	delay(KTA259V3_MUX_WAIT);
	Max31855::update();
}

// Return the info structure as-is (from last update)
Max31855_Info KTA259V3::get_info(void) {
	return Max31855::get_info();
}

// Take a new reading on selected channel and return the info structure
Max31855_Info KTA259V3::get_info(uint8_t ch) {
	update(ch);
	return Max31855::get_info();
}