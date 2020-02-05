/***********************************************************************************
 *  @file vibHandler.c
 ***********************************************************************************
 *  ╦ ╦╔═╗╔╦╗  ┌─┐┌─┐┌┬┐┌─┐  ┌─┐┬  ┬ ┬┌┐
 *  ║║║╠═╣║║║  │  │ │ ││├┤   │  │  │ │├┴┐
 *  ╚╩╝╩ ╩╩ ╩  └─┘└─┘─┴┘└─┘  └─┘┴─┘└─┘└─┘
 ***********************************************************************************
 *  Copyright (c) 2020 WAM code club
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 ***********************************************************************************
 * This code is invoked by the buzzwatch application in order to perform the random
 * buzzes of the haptic device.
 ***********************************************************************************/

#include "vibHandler.h"
#include "buzzwatchapp.h"
#include "device/haptic.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>

bool vibEnabled = true;

haptic_device_h myVibratingThing;
/*
 *
 * The delays are measured microseconds, not milliseconds.
 *
 * This is because sleep() takes an integer, not a float/double.
 * To compensate for this, I use usleep().
 * To use this, put the time in milliseconds + 3 zeros.
 * E.g. usleep(1000000) - One second.
 */
void VH_vibrate(vibPattern)
{
	int usleep(useconds_t useconds);

	 //'device_haptic_vibrate' turns on the vibration motor for a specified time in ms and intensity 1-100.

 	int returnedVal;
 	returnedVal = device_haptic_open(0, &myVibratingThing);

 	//Enables the device handler for vibrations.
 	haptic_effect_h effect_handle;

 	//Takes 'vibPattern' to pick the correct vibration pattern.
	switch(vibPattern)
	{
	case 0:
		vibEnabled = false;
		usleep(200000);
		device_haptic_vibrate(myVibratingThing, 400, 100, &effect_handle);
		usleep(430000);
		device_haptic_vibrate(myVibratingThing, 400, 100, &effect_handle);
		break;

	case 1:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 400, 100, &effect_handle);
		usleep(500000);
		device_haptic_vibrate(myVibratingThing, 400, 50, &effect_handle);
		usleep(500000);
		device_haptic_vibrate(myVibratingThing, 400, 100, &effect_handle);
		usleep(800000);
		break;

	case 2:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 1000, 100, &effect_handle);
		usleep(1000000);
		device_haptic_vibrate(myVibratingThing, 1000, 50, &effect_handle);
		usleep(1000000);
		device_haptic_vibrate(myVibratingThing, 1000, 20, &effect_handle);
		usleep(1000000);
		break;

	case 3:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 1000, 100, &effect_handle);
		usleep(1300000);
		device_haptic_vibrate(myVibratingThing, 1000, 50, &effect_handle);
		usleep(1300000);
		device_haptic_vibrate(myVibratingThing, 1000, 20, &effect_handle);
		usleep(1300000);
		break;

	case 4:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(320000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		break;

	case 5:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 400, 100, &effect_handle);
		usleep(430000);
		device_haptic_vibrate(myVibratingThing, 400, 100, &effect_handle);
		usleep(430000);
		device_haptic_vibrate(myVibratingThing, 400, 50, &effect_handle);
		usleep(430000);
		device_haptic_vibrate(myVibratingThing, 400, 50, &effect_handle);
		usleep(430000);
		device_haptic_vibrate(myVibratingThing, 400, 20, &effect_handle);
		usleep(430000);
		device_haptic_vibrate(myVibratingThing, 400, 20, &effect_handle);
		usleep(430000);
		break;

	case 6:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 1800, 100, &effect_handle);
		usleep(2100000);
		device_haptic_vibrate(myVibratingThing, 1800, 50, &effect_handle);
		usleep(2100000);
		device_haptic_vibrate(myVibratingThing, 100, 100, &effect_handle);
		usleep(110000);
		device_haptic_vibrate(myVibratingThing, 100, 100, &effect_handle);
		usleep(110000);
		device_haptic_vibrate(myVibratingThing, 100, 100, &effect_handle);
		usleep(2100000);
		break;

	case 7:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(165000);
		device_haptic_vibrate(myVibratingThing, 150, 20, &effect_handle);
		usleep(165000);
		break;

	case 8:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 100, 100, &effect_handle);
		usleep(120000);
		break;

	case 9:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 150, 20, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 20, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 20, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 20, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 50, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(180000);
		device_haptic_vibrate(myVibratingThing, 150, 100, &effect_handle);
		usleep(700000);
		break;

	case 10:
		vibEnabled = true;
		device_haptic_vibrate(myVibratingThing, 500, 100, &effect_handle);
		usleep(650000);
		device_haptic_vibrate(myVibratingThing, 500, 50, &effect_handle);
		usleep(650000);
		device_haptic_vibrate(myVibratingThing, 500, 75, &effect_handle);
		usleep(900000);
		break;

	default:
		//Gives an error if the 'vibrate()' function is used incorrectly.
		dlog_print(DLOG_WARN, "vibrate() error", "Error in function vibrate(). Pattern is not valid. (1 to 10, 0 to cancel).");
		break;
	}

}

void VH_kill(){
	device_haptic_close(myVibratingThing);
}
