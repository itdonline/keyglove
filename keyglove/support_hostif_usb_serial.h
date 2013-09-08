// Keyglove controller source code - Special hardware setup file
// 7/17/2011 by Jeff Rowberg <jeff@rowberg.net>

/* ============================================
Controller code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/



#ifndef _SUPPORT_HOSTIF_USB_SERIAL_H_
#define _SUPPORT_HOSTIF_USB_SERIAL_H_

#include "support_hostif_usb.h"

bool interfaceUSBSerialReady = false;
uint8_t interfaceUSBSerialMode = KG_INTERFACE_MODE_INCOMING_PACKET | KG_INTERFACE_MODE_OUTGOING_PACKET | KG_INTERFACE_MODE_OUTGOING_INFO;

void setup_hostif_usb_serial() {
    Serial.begin(KG_HOSTIF_SERIAL_BAUD);
}

void update_hostif_usb_serial() {
    interfaceUSBSerialReady = interfaceUSBReady;
    if ((interfaceUSBSerialMode & KG_INTERFACE_MODE_INCOMING_PACKET) != 0 && Serial.available()) hostif_protocol_parse(Serial.read());
}

#endif // _SUPPORT_HOSTIF_USB_SERIAL_H_


