/**
 * Main entrypoint.
 *
 * Does not do much by itself, just initializes other modules;
 */

#include <ch.h>
#include <hal.h>

int main(void) {
	// Chibios init stuff
	halInit();
	chSysInit();

	// Heartbeat
	palSetLineMode(LINE_LED0, PAL_MODE_OUTPUT_OPENDRAIN);
	palSetLine(LINE_LED0);

	while (true) {
		palClearLine(LINE_LED0);
		chThdSleepMilliseconds(50);
		palSetLine(LINE_LED0);
		chThdSleepMilliseconds(1000);
	}
}