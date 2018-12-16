/**
 * USB Host
 *
 * This implements a host USB system. It only recognizes HID class devices.
 */

#include <ch.h>
#include <hal.h>
#include <string.h>

#include <usbh/dev/hid.h>

#include "usb/host.h"
#include "logger.h"

// Which USBs are active, i.e. which should we poll?
static volatile bool fsActive = false, hsActive = false;

// Poller thread
static THD_WORKING_AREA(waUsbHostPollThread, 1024);
static THD_FUNCTION(usbHostPollThread, arg);

// HID Thread
static THD_WORKING_AREA(waHidThread, 1024);
static THD_FUNCTION(hidThread, arg);

// HID Callback
static void hidReportCallback(USBHHIDDriver *hidp, uint16_t len);

// HID Data
#define HID_REPORT_LEN       8
static USBH_DEFINE_BUFFER(
		uint8_t report[HAL_USBHHID_MAX_INSTANCES][HID_REPORT_LEN]);
static USBHHIDConfig hidcfg[HAL_USBHHID_MAX_INSTANCES];

// Report queue
static uint8_t reports[32][8];
static int reportStart = 0, reportEnd = 0;

void usbHostInit(void) {
	// Setup USB pins
	palSetLineMode(LINE_USB_FS_DP, PAL_MODE_ALTERNATE(10U));
	palSetLineMode(LINE_USB_FS_DM, PAL_MODE_ALTERNATE(10U));
	palSetLineMode(LINE_USB_HS_DP, PAL_MODE_ALTERNATE(12U));
	palSetLineMode(LINE_USB_HS_DM, PAL_MODE_ALTERNATE(12U));

	// Start host polling thread
	chThdCreateStatic(waUsbHostPollThread, sizeof(waUsbHostPollThread),
	                  NORMALPRIO, usbHostPollThread, NULL);

	// Configure HID driver
	for (int i = 0; i < HAL_USBHHID_MAX_INSTANCES; i++) {
		hidcfg[i].cb_report = hidReportCallback;
		hidcfg[i].protocol = USBHHID_PROTOCOL_BOOT;
		hidcfg[i].report_buffer = report[i];
		hidcfg[i].report_len = HID_REPORT_LEN;
	}

	// Start HID driver
	chThdCreateStatic(waHidThread, sizeof(waHidThread), NORMALPRIO,
	                  hidThread, NULL);
}

void usbHostStart(bool isFs) {
	// FS already active, nothing to see here
	if (isFs && fsActive) return;
	// Same for HS
	if (!isFs && hsActive) return;

	lognl("Started USB %cS host", isFs ? 'F' : 'H');
	usbhStart(isFs ? &USBHD1 : &USBHD2);

	if (isFs) fsActive = true;
	else      hsActive = true;
}

void usbHostStop(bool isFs) {
	// FS already inactive, nothing to see here
	if (isFs && !fsActive) return;
	// Same for HS
	if (!isFs && !hsActive) return;

	lognl("Stopped USB %cS host", isFs ? 'F' : 'H');
	usbhStop(isFs ? &USBHD1 : &USBHD2);

	if (isFs) fsActive = false;
	else      hsActive = false;
}

static THD_FUNCTION(usbHostPollThread, arg) {
	(void)arg;

	chRegSetThreadName("USB Host Poller");

	while (true) {
		// TODO switch to proper blocking events
		while (!fsActive && !hsActive)
			chThdSleepMilliseconds(1000);

		if (fsActive) usbhMainLoop(&USBHD1);
		if (hsActive) usbhMainLoop(&USBHD2);

		while (reportStart != reportEnd) {
			uint8_t *report = reports[reportStart];
			if (++reportStart >= 32) reportStart = 0;

			lognl("HID report: modifier = %2x, ??? = %2x, "
			      "keys = %2x %2x %2x %2x %2x %2x",
				  report[0], report[1], report[2], report[3],
				  report[4], report[5], report[6], report[7]);
		}

		chThdSleepMilliseconds(10);
	}
}

static THD_FUNCTION(hidThread, arg) {
	(void)arg;

	chRegSetThreadName("USB HID Thread");

	while (true) {
		// TODO switch to proper blocking events
		while (!fsActive && !hsActive)
			chThdSleepMilliseconds(1000);

		for (int i = 0; i < HAL_USBHHID_MAX_INSTANCES; i++)
			switch (usbhhidGetState(&USBHHIDD[i])) {
			case USBHHID_STATE_ACTIVE:
				// Start one HID instance
				usbhhidStart(&USBHHIDD[i], &hidcfg[i]);
				lognl("Started HID %d", i);
				if (usbhhidGetType(&USBHHIDD[i]) != USBHHID_DEVTYPE_GENERIC)
					usbhhidSetIdle(&USBHHIDD[i], 0, 0);
				break;

			default:
				break;
			}

		chThdSleepMilliseconds(200);
	}
}

static void hidReportCallback(USBHHIDDriver *hidp, uint16_t len) {
	(void)len;

	uint8_t *report = (uint8_t *)hidp->config->report_buffer;

	if (hidp->type == USBHHID_DEVTYPE_BOOT_KEYBOARD) {
		if (++reportEnd >= 32) reportEnd = 0;
		if (reportEnd == reportStart) return; // Drop report

		memcpy(&reports[reportEnd], report, HID_REPORT_LEN);
	}
}
