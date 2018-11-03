#include "ch.h"
#include "hal.h"

// Blinker thread
static THD_WORKING_AREA(blinker_wa, 128);
static THD_FUNCTION(blinker, arg) {
	(void)arg;
	chRegSetThreadName("blinker");

	uint32_t lines[] = {LINE_LED0, LINE_LED1, LINE_LED2, LINE_LED3};

	const int delay = 150;

	while (true) {
		for (int j = 0; j < 0xf; j++) {
			for (int i = 0; i < 4; i++) {
				if ((1 << i) & j)
					palClearLine(lines[i]);
				else
					palSetLine(lines[i]);
			}
			chThdSleepMilliseconds(delay);
		}

		for (int i = 0; i < 4; i++)
			palSetLine(lines[i]);

		for (int i = 0; i < 4; i++) {
			palClearLine(lines[i]);
			chThdSleepMilliseconds(delay);
			palSetLine(lines[i]);
		}
		for (int i = 3; i >= 0; i--) {
			palClearLine(lines[i]);
			chThdSleepMilliseconds(delay);
			palSetLine(lines[i]);
		}
	}
}

int main(void) {
	halInit();
	chSysInit();

	chThdCreateStatic(blinker_wa, sizeof(blinker_wa),
	                  NORMALPRIO-1, blinker, NULL);

	while (true)
		chThdSleepMilliseconds(500);
	return 0;
}
