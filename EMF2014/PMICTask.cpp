/*
 TiLDA Mk2
 
 PMICTask
 
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

#include "PMICTask.h"

// EventGroup bita
#define PMIC_CHAREG_STATE_BIT   (1 << 0)
#define PMIC_SAMPLE_RATE_BIT    (1 << 1)


/**
 * PMIC Task class
 */

// Callbacks
static void PMICChargeStateInterrupt(void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    // set the Charge state bit to wake the PMIC Task
    xEventGroupSetBitsFromISR(PMIC.eventGroup,
                              PMIC_CHAREG_STATE_BIT,
                              &xHigherPriorityTaskWoken);
    
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}


// Public
String PMICTask::getName()
{
    return "PMICTask";
}

uint32_t PMICTask::getBatteryReading()
{
    return batteryReading;
}

float PMICTask::getBatteryVoltage()
{
    return (batteryReading * (3.3 /512));
}

uint8_t PMICTask::getBatteryPercent()
{
    return (batteryReading-PMIC_BATTERY_FLAT)*PMIC_BATTERY_PERCENT_RATIO;
    
}

uint8_t PMICTask::getChargeState()
{
    return chargeState;
}

int8_t PMICTask::setSampleRate(TickType_t ms)
{
    sampleRate = ms;
    xEventGroupSetBits(eventGroup, PMIC_SAMPLE_RATE_BIT);
}


// protected
void PMICTask::task()
{
    pinMode(MCP_STAT, INPUT_PULLUP);
    pinMode(VBATT_MON, INPUT);
    sampleRate = PMIC_DEFAULT_SAMPLE;
    
    eventGroup = xEventGroupCreate();
    if (eventGroup == NULL) {
        // bugger
    }
    
    attachInterrupt(MCP_STAT, PMICChargeStateInterrupt, CHANGE);
        
    
    while(true) {
        
        EventBits_t uxBits;
        
        /* Wait a maximum of 100ms for either bit 0 or bit 4 to be set within
         the event group.  Clear the bits before exiting. */
        uxBits = xEventGroupWaitBits(eventGroup,
                                     PMIC_CHAREG_STATE_BIT | PMIC_SAMPLE_RATE_BIT,
                                     pdFALSE,
                                     pdFALSE,
                                     (sampleRate/portTICK_PERIOD_MS) );
        
        if( ( uxBits & PMIC_SAMPLE_RATE_BIT ) != 0 ) {
            // new sample rate notting todo but clear the bit and re enter the wait
            xEventGroupClearBits(eventGroup,
                                 PMIC_SAMPLE_RATE_BIT);
            
        } else if( ( uxBits & PMIC_CHAREG_STATE_BIT ) != 0 ) {
            chargeState = digitalRead(MCP_STAT);
            xEventGroupClearBits(eventGroup,
                                 PMIC_SAMPLE_RATE_BIT);
            
            // TODO: notify others that want to know about state change
            
            
        } else {
            // wait timed out, time to sample the battery voltage
            batteryReading = analogRead(VBATT_MON);
            chargeState = digitalRead(MCP_STAT);
            
            // check battery state and notify others
            if (batteryReading <= PMIC_BATTERY_VERYLOW) {
                // TODO: Panic and Charge now notifications
            } else if (batteryReading <= PMIC_BATTERY_LOW) {
                // TODO: Low battery notification
            }
        }
        
    }
}


// only once instance
PMICTask PMIC;