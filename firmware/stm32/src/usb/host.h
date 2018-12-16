#ifndef _USB_HOST_H
#define _USB_HOST_H

/**
 * Initializes the USB host driver on both USB HS and USB FS.
 */
void usbHostInit(void);

/**
 * Starts the host driver on either FS or HS
 * @param isFs     true for USB FS, false for USB HS
 */
void usbHostStart(bool isFs);

/**
 * Stops the host driver on either FS or HS
 * @param isFs     true for USB FS, false for USB HS
 */
void usbHostStop(bool isFs);

#endif
