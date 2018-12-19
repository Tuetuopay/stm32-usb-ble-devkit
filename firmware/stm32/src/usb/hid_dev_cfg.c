/**
 * USB HID Device Config
 */

#include <ch.h>
#include <hal.h>

#include "usb/hid_dev_cfg.h"

// Endpoints to be used for USBD1
#define USB_DATA_REQUEST_EP           1
#define USB_DATA_AVAILABLE_EP         1

// USB HID Driver structure
USBHIDDriver UHD1, UHD2;

// USB Device Descriptor
static const uint8_t hidDeviceDescData[] = {
	USB_DESC_DEVICE(0x0200, // bcdUSB (2.0)
	                0,      // bDeviceClass (HID) TODO
	                0,      // bDeviceSubClass    TODO
	                0,      // bDeviceProtocol   TODO
	                64,     // bMaxPacketSize
	                0xb1ac, // idVendor (random)
	                0xcafe, // idProduct
	                0xbabe, // bcdDevice
	                1,      // iManufacturer
	                2,      // iProduct
	                3,      // iSerialNumber
	                1)      // bNumConfigurations
};

// Device Descriptor wrapper.
static const USBDescriptor hidDeviceDesc = {
	sizeof(hidDeviceDescData), hidDeviceDescData
};

/**
 * HID Report Descriptor
 *
 * This is the description of the format ant the content of the different IN
 * or/and OUT reports that your application can receive/send
 *
 * See "Device Class Definition for Human Interface Devices (HID)"
 * (http://www.usb.org/developers/hidpage/HID1_11.pdf) for the detailed
 * description of all the fields
 */
#define KBD_ENDPOINT_SIZE  8
#define KBD_REPORT_KEYS    (KBD_ENDPOINT_SIZE - 2)
static const uint8_t hidKbdReportDescData[] = {
	HID_USAGE_PAGE_B(HID_USAGE_PAGE_GENERIC_DESKTOP),
	HID_USAGE_B(HID_USAGE_KEYBOARD),

	HID_COLLECTION_B(HID_COLLECTION_APPLICATION),     // Collection: Application
	HID_REPORT_SIZE_B(0x01),     //   Report size: 1
	HID_REPORT_COUNT_B(0x08),    //   Report Count: 8
	HID_USAGE_PAGE_B(HID_USAGE_PAGE_KEYBOARD_KEYPAD), //   Usage Page: Key Codes
	HID_USAGE_MINIMUM_B(0xE0),   //   Usage Minimum: 224
	HID_USAGE_MAXIMUM_B(0xE7),   //   Usage Maximum: 231
	HID_LOGICAL_MINIMUM_B(0x00), //   Logical Minimum: 0
	HID_LOGICAL_MAXIMUM_B(0x01), //   Logical Maximum: 1
	HID_INPUT_B(0x02),           //   Input: Data, Variable, Absolute (Modifier byte)
	HID_REPORT_COUNT_B(0x01),    //   Report Count: 1
	HID_REPORT_SIZE_B(0x08),     //   Report Size: 8
	HID_INPUT_B(0x03),           //   Input: Constant (Reserved byte)
	HID_REPORT_COUNT_B(0x05),    //   Report Count: 5
	HID_REPORT_SIZE_B(0x01),     //   Report Size: 1
	HID_USAGE_PAGE_B(HID_USAGE_PAGE_LEDS), //   Usage Page: LEDs
	HID_USAGE_MINIMUM_B(0x01),   //   Usage Minimum: 1
	HID_USAGE_MAXIMUM_B(0x05),   //   Usage Maximum: 5
	HID_OUTPUT_B(0x02),          //   Output: Data, Variable, Absolute (LED report)
	HID_REPORT_COUNT_B(0x01),    //   Report Count: 1
	HID_REPORT_SIZE_B(0x03),     //   Report Size: 3
	HID_OUTPUT_B(0x03),          //   Output: Constant (LED report padding)
	HID_REPORT_COUNT_B(KBD_REPORT_KEYS),   //   Report Count (),
	HID_REPORT_SIZE_B(0x08),     //   Report Size: 8
	HID_LOGICAL_MINIMUM_B(0x00), //   Logical Minimum: 0
	HID_LOGICAL_MAXIMUM_B(0xFF), //   Logical Maximum(255),
	HID_USAGE_PAGE_B(HID_USAGE_PAGE_KEYBOARD_KEYPAD), //   Usage Page: Key Codes
	HID_USAGE_MINIMUM_B(0x00),   //   Usage Minimum: 0
	HID_USAGE_MAXIMUM_B(0xFF),   //   Usage Maximum: 255
	HID_INPUT_B(0x00),           //   Input: Data, Array
	HID_END_COLLECTION           // End Collection
};

// HID Report Descriptor wrapper
static const USBDescriptor hidKbdReportDesc = {
	sizeof(hidKbdReportDescData), hidKbdReportDescData
};

/**
 * Configuration Descriptor tree for a HID device
 *
 * The HID specifications version 1.11 require the following order:
 * - Configuration Descriptor
 * - Interface Descriptor
 * - HID Descriptor
 * - Endpoints Descriptors
 */
#define HID_DESCRIPTOR_OFFSET    18
#define HID_DESCRIPTOR_SIZE      USB_DESC_HID_SIZE

static const uint8_t hidConfigurationDescData[41] = {
	// Configuration Descriptor (9 bytes) USB spec 9.6.3, page 264-266,
	// Table 9-10
	USB_DESC_CONFIGURATION(41,   // wTotalLength
	                       0x01, // bNumInterfaces
	                       0x01, // bConfigurationValue
	                       0,    // iConfiguration
	                       0xC0, // bmAttributes (self powered)
	                       250), // bMaxPower (500mA)
	// Interface Descriptor (9 bytes) USB spec 9.6.5, page 267-269, table 9-12
	USB_DESC_INTERFACE(0,    // bInterfaceNumber
	                   0,    // bAlternateSetting
	                   2,    // bNumEndpoints
	                   0x03, // bInterfaceClass (HID)
	                   0x01, // bInterfaceSubClass (Boot)
	                   0x01, // bInterfaceProtocol (Keyboard)
	                   0),   // iInterface
	// HID Descriptor (9 bytes) HID 1.11 spec, section 6.2.1
	USB_DESC_HID(0x110, // bcdHID (HID 1.11)
	             0,     // bCountryCode
	             1,     // bNumDescriptors
	             0x22,  // bDescriptorType (Resport descriptor)
	             sizeof(hidKbdReportDescData)), // wDescriptorLength
	// Endpoint descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13
	USB_DESC_ENDPOINT(USB_DATA_AVAILABLE_EP,    // bEndpointAddress
	                  0x03,              // bmAttributes (Interrupt)
	                  KBD_ENDPOINT_SIZE, // wMaxPacketSize
	                  10),               // bInterval (10ms)
	// Endpoint descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13
	USB_DESC_ENDPOINT(USB_DATA_REQUEST_EP | 0x80, // bEndpointAddress
	                  0x03,              // bmAttributes (Interrupt)
	                  KBD_ENDPOINT_SIZE, // wMaxPacketSize
	                  10)                // bInterval (10ms)
};

// Configuration Descriptor wrapper
static const USBDescriptor hidConfigurationDesc = {
	sizeof(hidConfigurationDescData), hidConfigurationDescData
};

// HID KBD Wrapper
static const USBDescriptor hidKbdDesc = {
	HID_DESCRIPTOR_SIZE, &hidConfigurationDescData[HID_DESCRIPTOR_OFFSET]
};

// U.S. English language identifier
static const uint8_t hidStrLang[] = {
	USB_DESC_BYTE(4),                     // bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // bDescriptorType
	USB_DESC_WORD(0x0409)                 // wLANGID (U.S. English)
};

// Vendor string
static const uint8_t hidStrVen[] = {
	USB_DESC_BYTE(54),                    // bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // bDescriptorType
	'T', 0, 'u', 0, 'e', 0, 't', 0, 'u', 0, 'o', 0, 'p', 0, 'a', 0, 'y', 0,
	' ', 0, 'O', 0, 'S', 0, 'S', 0, ' ', 0, 'T', 0, 'e', 0, 'c', 0, 'h', 0,
	'n', 0, 'o', 0, 'l', 0, 'o', 0, 'g', 0, 'i', 0, 'e', 0, 's', 0
};

// Device Description string.
static const uint8_t hidStrDev[] = {
	USB_DESC_BYTE(74),                    // bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // bDescriptorType
	'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '+', 0, 'n', 0, 'R', 0, 'F', 0,
	'5', 0, '1', 0, ' ', 0, 'U', 0, 'S', 0, 'B', 0, '+', 0, 'B', 0, 'L', 0,
	'E', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'k', 0, 'i', 0, 't', 0, ' ', 0,
	'(', 0, 'H', 0, 'I', 0, 'D', 0, ' ', 0, 'K', 0, 'B', 0, 'D', 0, ')', 0
};

// Serial Number string.
static const uint8_t hidStrSer[] = {
	USB_DESC_BYTE(32),                    // bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // bDescriptorType
	't', 0, 'h', 0, 'e', 0, 'r', 0, 'e', 0, 'i', 0, 's', 0, 'n', 0, 'o', 0,
	's', 0, 'e', 0, 'r', 0, 'i', 0, 'a', 0, 'l', 0
};

// Strings wrappers array
static const USBDescriptor hidStrings[] = {
	{sizeof(hidStrLang), hidStrLang},
	{sizeof(hidStrVen), hidStrVen},
	{sizeof(hidStrDev), hidStrDev},
	{sizeof(hidStrSer), hidStrSer}
};

/**
 * Handles the GET_DESCRIPTOR callback. All required descriptors mus be handled
 * here.
 */
static const USBDescriptor *usbGetDescriptor(USBDriver *usbp, uint8_t dtype,
                                             uint8_t dindex, uint16_t lang) {
	(void)usbp;
	(void)lang;

	switch (dtype) {
	// Generic descriptors
	case USB_DESCRIPTOR_DEVICE:
		return &hidDeviceDesc;
	case USB_DESCRIPTOR_CONFIGURATION:
		return &hidConfigurationDesc;
	case USB_DESCRIPTOR_STRING:
		if (dindex < 4)
			return &hidStrings[dindex];
		break;

	// HID specific descriptors
	case USB_DESCRIPTOR_HID:
		if (lang == 0) // Actually interface index from the setup packet
			return &hidKbdDesc;
		break;
	case HID_REPORT:
		if (lang == 0)
			return &hidKbdReportDesc;

	default:
		break;
	}

	return NULL;
}

// Keyboard endpoint state structure
static USBInEndpointState kbdEpInState[2];
static USBOutEndpointState kbdEpOutState[2];
// Keyboard endpoint initialization structure (IN)
static const USBEndpointConfig kbdEpCfg[2] = {{
	USB_EP_MODE_TYPE_BULK,                // Interrupt endpoint
	NULL,                                 // Setup packet callback
	hidDataTransmitted, hidDataReceived,  // IN/OUT callback
	KBD_ENDPOINT_SIZE, KBD_ENDPOINT_SIZE, // IN/OUT maximum packet size
	&kbdEpInState[0], &kbdEpOutState[0],  // IN/OUT endpoint state
	2,                                    // In multiplier
	NULL                                  // SETUP buffer (not a SETUP endpoint)
}, {
	USB_EP_MODE_TYPE_BULK,                // Interrupt endpoint
	NULL,                                 // Setup packet callback
	hidDataTransmitted, hidDataReceived,  // IN/OUT callback
	KBD_ENDPOINT_SIZE, KBD_ENDPOINT_SIZE, // IN/OUT maximum packet size
	&kbdEpInState[1], &kbdEpOutState[1],  // IN/OUT endpoint state
	2,                                    // In multiplier
	NULL                                  // SETUP buffer (not a SETUP endpoint)
}};

/**
 * Handles the USB driver global events
 */
static void usbEventCb(USBDriver *usbp, usbevent_t event,
                       USBHIDDriver *hidp, int confNo) {
	switch (event) {
	case USB_EVENT_RESET:
	case USB_EVENT_ADDRESS:
		break;

	case USB_EVENT_CONFIGURED:
		osalSysLockFromISR();
		// Enables the endpoints specified into the config
		usbInitEndpointI(usbp, USB_DATA_REQUEST_EP, &kbdEpCfg[confNo]);
		// Reset the state of the HID subsystem
		hidConfigureHookI(hidp);
		osalSysUnlockFromISR();
		break;

	case USB_EVENT_UNCONFIGURED:
	case USB_EVENT_SUSPEND:
	case USB_EVENT_WAKEUP:
	case USB_EVENT_STALLED:
		break;
	}
}
static void usbEventCb1(USBDriver *usbp, usbevent_t event) {
	usbEventCb(usbp, event, &UHD1, 0);
}
static void usbEventCb2(USBDriver *usbp, usbevent_t event) {
	usbEventCb(usbp, event, &UHD2, 1);
}

/**
 * A boot keyboard (what we are implementing) needs to support the following
 * requests:
 *  - GetReport
 *  - GetIdle
 *  - SetIdle
 *  - GetProtocol
 *  - SetProtocol
 * The following are optional:
 *  - SetReport
 *
 * Most of it is already handled by hidRequestsHook
 */

// USB Drivers configurations
const USBConfig usbcfg[2] = {
	{usbEventCb1, usbGetDescriptor, hidRequestsHook, NULL},
	{usbEventCb2, usbGetDescriptor, hidRequestsHook, NULL}
};

// USB HID driver configuration
const USBHIDConfig usbhidcfg[2] = {
	{&USBD1, USB_DATA_REQUEST_EP, USB_DATA_AVAILABLE_EP},
	{&USBD2, USB_DATA_REQUEST_EP, USB_DATA_AVAILABLE_EP}
};
