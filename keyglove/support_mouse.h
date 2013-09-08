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



#ifndef _SUPPORT_MOUSE_H_
#define _SUPPORT_MOUSE_H_

#ifndef NO_USB_SUPPORT
#endif

#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 2
#define MOUSE_RIGHT 4

#define MOUSE_ACTION_MOVE 0
#define MOUSE_ACTION_SCROLL 1

#define MOUSE_MODE_TILT_VELOCITY 1
#define MOUSE_MODE_TILT_POSITION 2
#define MOUSE_MODE_MOVEMENT_POSITION 3
#define MOUSE_MODE_3D 4

#define SCROLL_MODE_TILT_VELOCITY 1
#define SCROLL_MODE_TILT_POSITION 2
#define SCROLL_MODE_MOVEMENT_POSITION 3

// mouse measurements
int16_t mousedx, mousedy, mousedz, scrolldy;    // relative movement
// (note z is for 3D movement, scrolldy is for scrolling)

uint8_t opt_mouse_invert_x = 0;                 // invert mouse x movements
uint8_t opt_mouse_invert_y = 1;                 // invert mouse y movements
uint8_t opt_mouse_invert_z = 0;                 // invert mouse z movements

uint8_t opt_mouse_mode = 0;                     // which mouse move mode (0=disable, 1/2/3/4 as defined)
uint8_t opt_scroll_mode = 0;                    // which mouse scroll mode (0=disable, 1/2/3 as defined), uses mouse Y axis values

float opt_mouse_scale_mode1[] = { 1, 1 };       // speed scale [x,y] for mode 1 (tilt-velocity)
float opt_mouse_scale_mode2[] = { 1, 1 };       // speed scale [x,y] for mode 2 (tilt-position)
float opt_mouse_scale_mode3[] = { 1, 1 };       // speed scale [x,y] for mode 3 (movement-position)
float opt_mouse_scale_mode4[] = { 1, 1, 1 };    // speed scale [x,y,z] for mode 4 (3D)

bool activeMouse;
bool activeGestures;

void setup_mouse() {
    mousedx = mousedy = mousedz = 0;
    scrolldy = 0;
}

void update_mouse() {
    switch (opt_mouse_mode) {
        case MOUSE_MODE_TILT_VELOCITY:
            mousedx += ((gv.y < 0) ? -pow(-(float)gv.y/30, 1.3)*3 : pow((float)gv.y/30, 1.3)*3) - ((gv.z < 0) ? -pow(-(float)gv.z/30, 1.3)*3 : pow((float)gv.z/30, 1.3)*3);
            mousedy += (gv.x < 0) ? -pow(-(float)gv.x/30, 1.3)*3 : pow((float)gv.x/30, 1.3)*3;
            break;
        case MOUSE_MODE_TILT_POSITION:
            mousedx = ((gv.y < 0) ? -pow(-(float)gv.y/30, 1.3)*3 : pow((float)gv.y/30, 1.3)*3) - ((gv.z < 0) ? -pow(-(float)gv.z/30, 1.3)*3 : pow((float)gv.z/30, 1.3)*3);
            mousedy = (gv.x < 0) ? -pow(-(float)gv.x/30, 1.3)*3 : pow((float)gv.x/30, 1.3)*3;
            break;
        case MOUSE_MODE_MOVEMENT_POSITION:
            #if (KG_FUSION > 0)
                mousedx = apFrame.x * opt_mouse_scale_mode4[0];
                mousedy = apFrame.y * opt_mouse_scale_mode4[1];
            #else
                mousedx = aa.x * opt_mouse_scale_mode4[0];
                mousedy = aa.y * opt_mouse_scale_mode4[1];
            #endif
            break;
        case MOUSE_MODE_3D:
            #if (KG_FUSION > 0)
                mousedx = apFrame.x * opt_mouse_scale_mode4[0];
                mousedy = apFrame.y * opt_mouse_scale_mode4[1];
                mousedz = apFrame.z * opt_mouse_scale_mode4[2];
            #else
                mousedx = aa.x * opt_mouse_scale_mode4[0];
                mousedy = aa.y * opt_mouse_scale_mode4[1];
                mousedz = aa.z * opt_mouse_scale_mode4[2];
            #endif
            break;
    }
    switch (opt_scroll_mode) {
        case SCROLL_MODE_TILT_VELOCITY: // gyro
            break;
        case SCROLL_MODE_TILT_POSITION: // gyro
            scrolldy -= ((float)gv.y < 0) ? -sqrt(-(float)gv.y / 30) : sqrt((float)gv.y / 30);
            break;
        case SCROLL_MODE_MOVEMENT_POSITION: // accel
            break;
    }

    if (opt_mouse_mode > 0 && (mousedx != 0 || mousedy != 0 || mousedz != 0)) {
        if (opt_mouse_invert_x == 1) mousedx = -mousedx;
        if (opt_mouse_invert_y == 1) mousedy = -mousedy;
        if (opt_mouse_invert_z == 1) mousedz = -mousedz;
        #if KG_HOSTIF & KG_HOSTIF_USB_HID
            if (mousedz > 0) Mouse.move(mousedx, mousedy, mousedz);
            else Mouse.move(mousedx, mousedy);
        #endif /* KG_HOSTIF_USB_HID */
        #if KG_HOSTIF & KG_HOSTIF_BT2_HID
            if (mousedz > 0) BTMouse.move(mousedx, mousedy, mousedz, 0);
            else BTMouse.move(mousedx, mousedy);
        #endif /* KG_HOSTIF_BT2_HID */
        #if KG_HOSTIF & KG_HOSTIF_R400_HID
            if (mousedz > 0) RX400.move(mousedx, mousedy, mousedz);
            else RX400.move(mousedx, mousedy);
        #endif /* KG_HOSTIF_R400_HID */
        DEBUG_MOUSE(Serial.print("mouse "));
        DEBUG_MOUSE(Serial.print(mousedx)); DEBUG_MOUSE(Serial.print(" "));
        DEBUG_MOUSE(Serial.print(mousedy)); DEBUG_MOUSE(Serial.print(" "));
        DEBUG_MOUSE(Serial.println(mousedz));
    }
    if (opt_scroll_mode > 0 && scrolldy != 0) {
        if (opt_mouse_invert_y == 1) mousedy = -mousedy;
        #if KG_HOSTIF & KG_HOSTIF_USB_HID
            Mouse.scroll(scrolldy);
        #endif /* KG_HOSTIF_USB_HID */
        #if KG_HOSTIF & KG_HOSTIF_BT2_HID
            BTMouse.scroll(scrolldy, 0);
        #endif /* KG_HOSTIF_BT2_HID */
        #if KG_HOSTIF & KG_HOSTIF_R400_HID
            RX400.scroll(scrolldy);
        #endif /* KG_HOSTIF_R400_HID */
        DEBUG_MOUSE(Serial.print("scroll "));
        DEBUG_MOUSE(Serial.println(scrolldy));
    }
}

#endif // _SUPPORT_MOUSE_H_