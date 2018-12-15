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

// Mutex to avoid mixing logs of separate threads
static mutex_t mutex;

void loggerInit(void) {
	// Configure pins
	palSetLineMode(LINE_TX, PAL_MODE_ALTERNATE(7U));
	palSetLineMode(LINE_RX, PAL_MODE_ALTERNATE(7U));

	// Start serial driver
	static SerialConfig serialConfig = {115200, 0, 0, 0};
	sdStart(&SD1, &serialConfig);

	chMtxObjectInit(&mutex);
}

void loggerHeader(void) {
	int now = stGetCounter();
	chprintf(chout, "[" YELLOW "%7d" RST "] ", now);
}

void loggerLock(void) {
	chMtxLock(&mutex);
}

void loggerUnlock(void) {
	chMtxUnlock(&mutex);
}
