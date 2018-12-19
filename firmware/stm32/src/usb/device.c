/**
 * USB Device
 *
 * Driver to behave as a USB HID keyboard.
 */

#include <ch.h>
#include <hal.h>

#include "usb/host.h"
#include "usb/hid_dev_cfg.h"
#include "logger.h"

// Which USBs are active, i.e. which should we listen to?
static volatile bool fsActive = false, hsActive = false;

// OUT report polling thread
static THD_WORKING_AREA(waUsbDevPollThreadFs, 1024);
static THD_WORKING_AREA(waUsbDevPollThreadHs, 1024);
static THD_FUNCTION(usbDevPollThread, arg);

typedef struct poll_thread_arg {
	USBHIDDriver *hidp;
	volatile bool *active;
} poll_thread_arg_t;

void usbDeviceInit(void) {
	// Setup USB pins
	palSetLineMode(LINE_USB_FS_DP, PAL_MODE_ALTERNATE(10U));
	palSetLineMode(LINE_USB_FS_DM, PAL_MODE_ALTERNATE(10U));
	palSetLineMode(LINE_USB_HS_DP, PAL_MODE_ALTERNATE(12U));
	palSetLineMode(LINE_USB_HS_DM, PAL_MODE_ALTERNATE(12U));

	// Configure USB HID drivers
	hidObjectInit(&UHD1);
	hidObjectInit(&UHD2);

	static poll_thread_arg_t args[] = {
		{&UHD1, &fsActive}, {&UHD2, &hsActive}
	};
	chThdCreateStatic(waUsbDevPollThreadFs, sizeof(waUsbDevPollThreadFs),
	                  NORMALPRIO, usbDevPollThread, &args[0]);
	chThdCreateStatic(waUsbDevPollThreadHs, sizeof(waUsbDevPollThreadHs),
	                  NORMALPRIO, usbDevPollThread, &args[1]);
}

void usbDeviceStart(bool isFs) {
	// FS already active, nothing to see here
	if (isFs && fsActive) return;
	// Same for HS
	if (!isFs && hsActive) return;

	USBHIDDriver *hidp = isFs ? &UHD1 : &UHD2;
	const USBHIDConfig *hidcfg = &usbhidcfg[isFs ? 0 : 1];
	const USBConfig *ucfg = &usbcfg[isFs ? 0 : 1];

	lognl("Started USB %cS device", isFs ? 'F' : 'H');
	hidStart(hidp, hidcfg);
	usbDisconnectBus(hidcfg->usbp);
	chThdSleepMilliseconds(1000);
	usbStart(hidcfg->usbp, ucfg);
	usbConnectBus(hidcfg->usbp);

	if (isFs) fsActive = true;
	else      hsActive = true;
}

void usbDeviceStop(bool isFs) {
	// FS already inactive, nothing to see here
	if (isFs && !fsActive) return;
	// Same for HS
	if (!isFs && !hsActive) return;

	USBHIDDriver *hidp = isFs ? &UHD1 : &UHD2;
	const USBHIDConfig *hidcfg = &usbhidcfg[isFs ? 0 : 1];

	lognl("Stopped USB %cS device", isFs ? 'F' : 'H');
	usbStop(hidcfg->usbp);
	hidStop(hidp);

	if (isFs) fsActive = false;
	else      hsActive = false;
}

void usbDeviceWriteReport(uint8_t *buf, size_t n) {
	if (fsActive)
		hidWriteReport(&UHD1, buf, n);
	if (hsActive)
		hidWriteReport(&UHD2, buf, n);
}

static THD_FUNCTION(usbDevPollThread, arg) {
	poll_thread_arg_t *args = (poll_thread_arg_t *)arg;

	char threadName[] = "USB FS Device HID Thread";
	if (args->hidp == &UHD2)
		threadName[4] = 'H'; // Replace FS with HS
	chRegSetThreadName(threadName);

	USBH_DEFINE_BUFFER(uint8_t report);

	while (true) {
		// TODO switch to proper blocking events
		while (!*args->active)
			chThdSleepMilliseconds(1000);

		// Poll for a report to come
		// TODO use real thread waiters
		if (hidReadReportt(args->hidp, &report, 1, TIME_IMMEDIATE))
			// Forward it to host driver
			usbHostWriteReport(&report, 1);

		chThdSleepMilliseconds(10);
	}
}
