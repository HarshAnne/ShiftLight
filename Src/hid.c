#include "stm32f10x.h"

/* Maximum packet size */
#define MAX_PACKET_SIZE		8

/* USB Descriptors */
static const uint8_t USB_DeviceDescriptor[] = {
	0x12,			// bLength
	0x01,			// bDescriptorType (Device)
	0x10, 0x01,		// bcdUSB 1.10
	0x00,			// bDeviceClass (Use class information in the Interface Descriptors)
	0x00,			// bDeviceSubClass
	0x00,			// bDeviceProtocol
	MAX_PACKET_SIZE,	// bMaxPacketSize0 8
	0x09, 0x12,		// idVendor 0x1209
	0xBA, 0xBE,		// idProduct 0xBEBA
	0x00, 0x03,		// bcdDevice 3.00
	0x01,			// iManufacturer (String Index)
	0x02,			// iProduct (String Index)
	0x00,			// iSerialNumber (String Index)
	0x01 			// bNumConfigurations 1
};

static const uint8_t USB_ConfigurationDescriptor[] = {
	0x09,			// bLength
	0x02,			// bDescriptorType (Configuration)
	0x22, 0x00,		// wTotalLength 34
	0x01,			// bNumInterfaces 1
	0x01,			// bConfigurationValue
	0x00,			// iConfiguration (String Index)
	0xC0,			// bmAttributes Self Powered
	0x32,			// bMaxPower 100mA

	0x09,			// bLength
	0x04,			// bDescriptorType (Interface)
	0x00,			// bInterfaceNumber 0
	0x00,			// bAlternateSetting
	0x01,			// bNumEndpoints 1
	0x03,			// bInterfaceClass
	0x00,			// bInterfaceSubClass
	0x00,			// bInterfaceProtocol
	0x00,			// iInterface (String Index)

	0x09,			// bLength
	0x21,			// bDescriptorType (HID)
	0x11, 0x01,		// bcdHID 1.11
	0x00,			// bCountryCode
	0x01,			// bNumDescriptors
	0x22,			// bDescriptorType[0] (HID)
	0x20, 0x00,		// wDescriptorLength[0] 32

	0x07,			// bLength
	0x05,			// bDescriptorType (Endpoint)
	0x81,			// bEndpointAddress (IN/D2H)
	0x03,			// bmAttributes (Interrupt)
	MAX_PACKET_SIZE, 0x00,	// wMaxPacketSize 8
	0x05 			// bInterval 5 (2^(5-1)=16 micro-frames)
};

/* USB String Descriptors */
static const uint8_t USB_LangIDStringDescriptor[] = {
	0x04,			// bLength
	0x03,			// bDescriptorType (String)
	0x09, 0x04		// English (United States)
};

static const uint8_t USB_VendorStringDescriptor[] = {
	0x22,			// bLength
	0x03,			// bDescriptorType (String)
	'w', 0, 'w', 0, 'w', 0, '.', 0, 's', 0, 'e', 0, 'r', 0, 'a', 0, 's', 0,
	'i', 0, 'd', 0, 'i', 0, 's', 0, '.', 0, 'g', 0, 'r', 0
};

static const uint8_t USB_ProductStringDescriptor[] = {
	0x2C,			// bLength
	0x03,			// bDescriptorType (String)
	'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, 'F', 0, ' ', 0, 'H', 0, 'I', 0,
	'D', 0, ' ', 0, 'B', 0, 'o', 0, 'o', 0, 't', 0, 'l', 0, 'o', 0, 'a', 0,
	'd', 0, 'e', 0, 'r', 0
};