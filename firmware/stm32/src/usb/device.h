#ifndef _USB_DEVICE_H
#define _USB_DEVICE_H

/**
 * Initialises the USB device subsystem
 */
void usbDeviceInit(void);

/**
 * Starts the device driver on either FS or HS
 * @param isFs     true for USB FS, false for USB HS
 */
void usbDeviceStart(bool isFs);

/**
 * Stops the device driver on either FS or HS
 * @param isFs     true for USB FS, false for USB HS
 */
void usbDeviceStop(bool isFs);

/**
 * Writes a report to all active HID keyboards
 * @param report   pointer to the report data buffer
 * @param n        size of the report data buffer
 */
void usbDeviceWriteReport(uint8_t *buf, size_t n);

#endif
