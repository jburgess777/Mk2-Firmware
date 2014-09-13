/*
 TiLDA Mk2

 EMF2014Config
 This files contains all the initial configuration details for the badge firmware and any compli time defines that might be used by any of the task


 The MIT License (MIT)

 Copyright (c) 2014 Electromagnetic Field LTD

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once

// This defines how many subscription each button can handle
#define MAX_BUTTON_SUBSCRIPTIONS 10
// maximum amount of apps the AppManager can handle
#define MAX_APPS 10
// pin used for seeding the random number generator
#define RANDOM_SEED_PIN 5

// duration that center has to be pressed to go back to the homescreen
#define CENTER_BUTTON_PRESS_DURATION_FOR_HOME_SCREEN 500
// time before the backlight goes out
#define BACKLIGHT_TIMEOUT 15 * 1000
// time before the current app gets killed and the badge goes back to the homescreen
#define APP_KILL_TIMEOUT 90 * 1000
// backlight light level speed in ms
#define BACKLIGHT_BRIGHTNESS_UPDATE_TIME 50

// Radio serial port
#define RADIO_SERIAL Serial
#define RADIO_SERIAL_BAUD 115200
// Packet length
#define RADIO_PACKET_LENGTH 58
#define RADIO_PACKET_WITH_RSSI_LENGTH 58 + 1 + 4
// Radio message buffer length
#define RADIO_MAX_MESSAGE_BUFFER_LENGTH 40960
// Radio discovery channel (in hex)
#define RADIO_DISCOVERY_CHANNEL "02"
// Discovery time in ticks
#define RADIO_DISCOVERY_TIME 3000
// Sleep between unsuccessful discoverys
#define RADIO_UNSUCCESSFUL_DISCOVERY_SLEEP 60000
// Time spend without incoming messages before badge goes back into
// discovery mode (in ticks)
#define RADIO_RECEIVE_TIMEOUT 10000
// Sleep time for the receiver task when no serial data is available
#define RADIO_NO_DATA_SLEEP_DURATION 5
// This is how long we'll wait before sending after waking up the radio
#define RADIO_WAKEUP_TIME 400
// This is a sanity check. Make sure no transmit window is longer than this
#define RADIO_MAX_TRANSMIT_WINDOW_LENGTH 3 * 60 * 1000
// Another sanity check. Minimum/Maximum current time
#define RADIO_MINIMUM_CURRENT_TIME 1408879302
#define RADIO_MAXIMUM_CURRENT_TIME 1440415302

// EMF Camp 2014 will be in Britain during British Summer Time
#define TIMEZONE_OFFSET 3600

#define BOOT_SCREEN_TIME 2000

//#define RADIO_DEBUG_MODE
//#define RADIO_DEBUG_MODE_EXTENDED


#if 0
// EMF2014 Public Key
const uint8_t EMF_PUBLIC_KEY[40] = {0x2b, 0xaf, 0x24, 0xb9, 0x9e, 0x0a, 0xc6, 0x20, 0x64, 0xbe,
                                    0x7e, 0xf6, 0x9a, 0xad, 0x86, 0xff, 0x41, 0x60, 0x74, 0x2c,
                                    0xe2, 0x5b, 0xc2, 0xef, 0xa6, 0xb6, 0x62, 0x24, 0x0b, 0xb2,
                                    0xf8, 0x82, 0x3f, 0x92, 0x9e, 0x1e, 0x91, 0x3a, 0xb9, 0xfd};
#else
// locally generated key pair
const uint8_t EMF_PUBLIC_KEY[40] = {0xb8, 0xf0, 0x58, 0x34, 0xd8, 0x43, 0x15, 0x34, 0x9a, 0x1d,
                                    0x17, 0xdb, 0x8d, 0x2e, 0x31, 0x34, 0xb2, 0x1f, 0x54, 0xb6,
                                    0xf7, 0x52, 0x96, 0x8b, 0x1d, 0x8d, 0x83, 0x22, 0x80, 0x4a,
                                    0xa5, 0xf1, 0x2d, 0x36, 0xf2, 0x94, 0x36, 0xdb, 0x56, 0x09};
#endif

enum Button {
    NONE         = 0,
    LIGHT        = 1,
    A            = 2,
    B            = 4,
    UP           = 8,
    DOWN         = 16,
    LEFT         = 32,
    RIGHT        = 64,
    CENTER       = 128
};

enum Orientation_t{
    ORIENTATION_HELD,
    ORIENTATION_RIGHT,  // joystick to the right of the screen
    ORIENTATION_HUNG,
    ORIENTATION_LEFT    // joystick to the left of the screen,
};
