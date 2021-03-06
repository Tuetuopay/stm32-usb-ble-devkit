/**
 * Main entrypoint.
 *
 * Does not do much by itself, just initializes other modules;
 */

#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#include "logger.h"
#include "usb/arbiter.h"
#include "usb/host.h"
#include "usb/device.h"

int main(void) {
	// Chibios init stuff
	halInit();
	chSysInit();

	// Misc modules
	loggerInit();
	usbArbiterInit();
	usbHostInit();
	usbDeviceInit();

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
