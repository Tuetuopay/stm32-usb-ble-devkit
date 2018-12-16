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
#include "util/hid_keys.h"
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

	uint8_t lastReport[HID_REPORT_LEN] = {0};

	while (true) {
		// TODO switch to proper blocking events
		while (!fsActive && !hsActive)
			chThdSleepMilliseconds(1000);

		if (fsActive) usbhMainLoop(&USBHD1);
		if (hsActive) usbhMainLoop(&USBHD2);

		while (reportStart != reportEnd) {
			uint8_t *report = reports[reportStart];
			if (++reportStart >= 32) reportStart = 0;

			for (int i = 2; i < HID_REPORT_LEN; i++) {
				bool found = false;

				if (report[i] == 0) break;

				for (int j = 2; j < HID_REPORT_LEN; j++) {
					if (lastReport[j] == 0) break;
					if (lastReport[j] == report[i]) found = true;
				}

				if (!found)
					lognl("Key: %c", code2char(report[i], report[0]));
			}

			memcpy(lastReport, report, HID_REPORT_LEN);
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
		if (reportEnd == reportStart - 1 || (reportEnd == 31 && reportStart == 0))
			return; // Drop report
		memcpy(&reports[reportEnd], report, HID_REPORT_LEN);
		if (++reportEnd >= 32) reportEnd = 0;
	}
}
