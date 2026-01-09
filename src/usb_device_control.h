/*
* Copyright (c) 2025 ArqAlice 
*
* Released under the MIT license
* https://opensource.org/licenses/mit-license.php
*/

#ifndef _USB_DEVICE_CONTROL_H_
#define _USB_DEVICE_CONTROL_H_

#include "pico/stdlib.h"
#include "pico/usb_device.h"
#include "lufa/HIDClassCommon.h"
#include "lufa/AudioClassCommon.h"

#define CONSUMER_PREVIOUS   0xb6
#define CONSUMER_NEXT       0xb5
#define CONSUMER_PLAY_PAUSE 0xcd
#define CONSUMER_STOP       0xb7
#define CONSUMER_VOL_UP     0xe9
#define CONSUMER_VOL_DOWN   0xea

#define HID_PACKET_SIZE 8
#define HID_BLANK_COUNT (HID_PACKET_SIZE - 2)

// USB descriptor for HiRes Audio
struct audio_device_config
{
	struct usb_configuration_descriptor descriptor;
	struct usb_interface_descriptor ac_interface;
	struct __packed
	{
		USB_Audio_StdDescriptor_Interface_AC_t core;
		USB_Audio_StdDescriptor_InputTerminal_t input_terminal;
		USB_Audio_StdDescriptor_FeatureUnit_t feature_unit;
		USB_Audio_StdDescriptor_OutputTerminal_t output_terminal;
	} ac_audio;
	struct usb_interface_descriptor as_zero_interface;

	struct usb_interface_descriptor as_op_interface;
	struct __packed
	{
		USB_Audio_StdDescriptor_Interface_AS_t streaming;
		struct
		{
			USB_Audio_StdDescriptor_Format_t core;
			USB_Audio_SampleFreq_t freqs[4]; // 44.1/48/88.2/96kHz対応のため配列数を2->4に増やす
		} format;
	} as_audio;
	struct __packed
	{
		struct usb_endpoint_descriptor_long core;
		USB_Audio_StdDescriptor_StreamEndpoint_Spc_t audio;
	} ep1;
	struct usb_endpoint_descriptor_long ep2;

	// Alternate2 : 24bit再生用の定義
	struct usb_interface_descriptor as_op_interface_2;
	struct __packed
	{
		USB_Audio_StdDescriptor_Interface_AS_t streaming;
		struct __packed
		{
			USB_Audio_StdDescriptor_Format_t core;
			USB_Audio_SampleFreq_t freqs[4]; // <- 44.1/48/88.2/96kHz対応のため配列数を4とする
		} format;
	} as_audio_2;
	struct __packed
	{
		struct usb_endpoint_descriptor_long core;
		USB_Audio_StdDescriptor_StreamEndpoint_Spc_t audio;
	} ep1_2;
	struct usb_endpoint_descriptor_long ep2_2;
	
	// usb hid
	struct usb_interface_descriptor hid_interface;
    struct __packed
    {
        USB_HID_StdDescriptor_HID_t hid;
        struct usb_endpoint_descriptor ep;
    } hid_descriptor;
};

extern void usb_sound_card_init();
void hid_send_report(uint8_t* report, uint8_t len);

#endif /* _USB_DEVICE_CONTROL_H_ */