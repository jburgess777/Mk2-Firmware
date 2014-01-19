/*
 TiLDA Mk2 button debounce tester (Native USB)
 
 Simple script to test button debounce and report preses over serial 
 
 This sekcth uses the USB serial port
 
 Debounce helper based on information form 
 http://forum.arduino.cc/index.php?topic=156474.0
 
 
 The MIT License (MIT)
 
 Copyright (c) 2014 Electromagnetic  Field LTD
 
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

#include <Debounce.h>

// intrupt flags
boolean buttonLight = 0;
boolean buttonScreenLeft = 0;
boolean buttonScreenRight = 0;
boolean buttonA = 0;
boolean buttonB = 0;
boolean buttonUp = 0;
boolean buttonRight = 0;
boolean buttonDown = 0;
boolean buttonLeft = 0;
boolean buttonCenter = 0;

void setup() {
    // set button pins to input
    pinMode(BUTTON_LIGHT, INPUT);
    pinMode(BUTTON_SCREEN_LEFT, INPUT);
    pinMode(BUTTON_SCREEN_RIGHT, INPUT);
    pinMode(BUTTON_A, INPUT);
    pinMode(BUTTON_B, INPUT);
    pinMode(BUTTON_UP, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);
    pinMode(BUTTON_DOWN, INPUT);
    pinMode(BUTTON_LEFT, INPUT);
    pinMode(BUTTON_CENTER, INPUT);
    
    // enable button pull up's
    digitalWrite(BUTTON_LIGHT, HIGH);
    digitalWrite(BUTTON_SCREEN_LEFT, HIGH);
    digitalWrite(BUTTON_SCREEN_RIGHT, HIGH);
    digitalWrite(BUTTON_A, HIGH);
    digitalWrite(BUTTON_B, HIGH);
    digitalWrite(BUTTON_UP, HIGH);
    digitalWrite(BUTTON_RIGHT, HIGH);
    digitalWrite(BUTTON_DOWN, HIGH);
    digitalWrite(BUTTON_LEFT, HIGH);
    digitalWrite(BUTTON_CENTER, HIGH);
    
    // attach button's to interrupt's
    attachInterrupt(BUTTON_LIGHT, buttonLightPress, FALLING);
    attachInterrupt(BUTTON_SCREEN_LEFT, buttonScreenLeftPress, FALLING);
    attachInterrupt(BUTTON_SCREEN_RIGHT, buttonScreenRightPress, FALLING);
    attachInterrupt(BUTTON_A, buttonAPress, FALLING);
    attachInterrupt(BUTTON_B, buttonBPress, FALLING);
    attachInterrupt(BUTTON_UP, buttonUpPress, FALLING);
    attachInterrupt(BUTTON_RIGHT, buttonRightPress, FALLING);
    attachInterrupt(BUTTON_DOWN, buttonDownPress, FALLING);
    attachInterrupt(BUTTON_LEFT, buttonLeftPress, FALLING);
    attachInterrupt(BUTTON_CENTER, buttonCenterPress, FALLING);
    
    // setup debpunce
    setDebounce(BUTTON_LIGHT);
    setDebounce(BUTTON_SCREEN_LEFT);
    setDebounce(BUTTON_SCREEN_RIGHT);
    setDebounce(BUTTON_A);
    setDebounce(BUTTON_B);
    setDebounce(BUTTON_UP);
    setDebounce(BUTTON_RIGHT);
    setDebounce(BUTTON_DOWN);
    setDebounce(BUTTON_LEFT);
    setDebounce(BUTTON_CENTER);
    
    // setup LED's
    
    // setup USB Serial
    SerialUSB.begin(115200);
    while (!SerialUSB) ;
    SerialUSB.println("TiLDA Mk2 button debounce tester");
}

void loop() {
    if (buttonLight) {
        SerialUSB.println("Light Pressed");
        buttonLight = 0;
    }
    if (buttonScreenLeft) {
        SerialUSB.println("Screen Left Pressed");
        buttonScreenLeft = 0;
    }
    if (buttonScreenRight) {
        SerialUSB.println("Screen Right Pressed");
        buttonScreenRight = 0;
    }
    if (buttonA) {
        SerialUSB.println("A Pressed");
        buttonA = 0;
    }
    if (buttonB) {
        SerialUSB.println("B Pressed");
        buttonB = 0;
    }
    if (buttonUp) {
        SerialUSB.println("Up Pressed");
        buttonUp = 0;
    }
    if (buttonRight) {
        SerialUSB.println("Right Pressed");
        buttonRight = 0;
    }
    if (buttonDown) {
        SerialUSB.println("Down Pressed");
        buttonDown = 0;
    }
    if (buttonLeft) {
        SerialUSB.println("Left Pressed");
        buttonLeft = 0;
    }
    if (buttonCenter) {
        SerialUSB.println("Center Pressed");
        buttonCenter = 0;
    }

}

void buttonLightPress(){
    buttonLight = 1;
}

void buttonScreenLeftPress(){
    buttonScreenLeft = 1;
}

void buttonScreenRightPress(){
    buttonScreenRight = 1;
}

void buttonAPress(){
    buttonA = 1;
}

void buttonBPress(){
    buttonB = 1;
}

void buttonUpPress(){
    buttonUp = 1;
}

void buttonRightPress(){
    buttonRight = 1;
}

void buttonDownPress(){
    buttonDown = 1;
}

void buttonLeftPress(){
    buttonLeft = 1;
}

void buttonCenterPress(){
    buttonCenter = 1;
}






