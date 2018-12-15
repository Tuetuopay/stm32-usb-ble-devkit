/**
 * Logger
 *
 * Utilities to log stuff to the serial port going to the JTAG probe
 */

#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#include "logger.h"
#include "ansi.h"

extern SerialDriver SD1;
BaseSequentialStream * const chout = (BaseSequentialStream*)&SD1;

void loggerInit(void) {
	// Configure pins
	palSetLineMode(LINE_TX, PAL_MODE_ALTERNATE(7U));
	palSetLineMode(LINE_RX, PAL_MODE_ALTERNATE(7U));

	// Start serial driver
	static SerialConfig serialConfig = {115200, 0, 0, 0};
	sdStart(&SD1, &serialConfig);
}

void loggerHeader(void) {
	int now = stGetCounter(), n = 0;

	chprintf(chout, "[" YELLOW);
	if (now < 10)
		n = 6;
	else if (now < 100)
		n = 5;
	else if (now < 1000)
		n = 4;
	else if (now < 10000)
		n = 3;
	else if (now < 100000)
		n = 2;
	else if (now < 1000000)
		n = 1;

	for (int i = 0; i < n; i++)
		chprintf(chout, " ");
	chprintf(chout, "%d" RST "] ", now);
}
