/**
 * USB HID device config
 */

#ifndef _USB_HID_DEV_CFG_H
#define _USB_HID_DEV_CFG_H

// All things are doubled for USB FS and HS
extern const USBConfig usbcfg[2];
extern const USBHIDConfig usbhidcfg[2];
extern USBHIDDriver UHD1, UHD2;

#endif
