/***********************************************************************************
 *  @file buzzwatchapp.c
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
 * This code is invoked by Tizen when controlling the buzzwatch app.
 * Buzzwatch can be used by those who need reminding to perform rehab
 * exercises that are necessary to aid the recovery from a number of conditions
 * including strokes, broken bones etc.
 ***********************************************************************************/

#include "buzzwatchapp.h"
#include "device/haptic.h"
#include "vibHandler.h"
#include "BT_BaseTypes.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <app_alarm.h>

/**
 * This is an OS handle to an alarm object, the app uses a regular alarm to trigger the app
 */
tINT32 iBWA_AlarmId = 0;

/**
 * This is an OS handle to an app controller, this app control function is invoked following app
 * startup and following the alarm defined by BWA_AlarmId
 */
app_control_h tsBWA_AppController;


/**
 * This boolean is used to indicate if the app should be vibrating the watch or not.
 */
bool bBWA_Vibrate = TRUE;

/**
 * This is a structure used to hold the data for the app, the OS holds on to this data
 * between OS invocations of the app.
 */
typedef struct tsBWA_AppData
{
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
    Evas_Object *box;
    Evas_Object *list;
} tsBWA_AppData;

/**
 * Called from the task manager when there is a request to kill the app
 */
static void win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	// TODO: needs to kill all the resources including alarms and control objects.
	ui_app_exit();
}

/**
 * Some kind of callback for setting the background properties
 */
static void win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	tsBWA_AppData *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

/**
 * This function returns a random delay in seconds between min_delay minutes and max_delay minutes
 * @return the number of seconds to delay
 * @param MinDelay (tINT32): this is the minimum delay in minutes
 * @param MaxDelay (tINT32): this is the maximum delay in minutes
 */
tINT32 timeDelay(tINT32 iMinDelay, tINT32 iMaxDelay)
{
	// set the seed for the random number generator to the current time... this makes it more
	// random.
	srand((unsigned)time(NULL));

	// create a random number in minutes in the range MinDelay to MaxDelay
    tINT32 iDelayInMins = rand() % (iMaxDelay + 1 - iMinDelay);

    // convert to seconds
	tINT32 iDelayInSecs = iDelayInMins * 60;

	// offset by MinDelay minutes
	iDelayInSecs = iDelayInSecs + (iMinDelay * 60);

	return(iDelayInSecs);
}

/**
 * This function is called when the user clicks the button displayed at the center of the app.
 */
static void buttonClickCallback(void *data, Evas_Object *button, void *ev)
{
   // if the button has been clicked to deactive then
   if (bBWA_Vibrate == TRUE)
   {
	   // toggle the message on the screen.
	   elm_object_text_set(button, "Click to activate");
	   // toggle the boolean.
	   bBWA_Vibrate = FALSE;
   }
   else
   {
	   // toggle the message on the screen.
	   elm_object_text_set(button, "Click to deactivate");
	   // toggle the boolean.
	   bBWA_Vibrate = TRUE;
   }
}

/**
 * Called when the app starts up. Creates the control app callback, the alarm, sets the
 * alarm time and puts the activate/deactivate button on the screen.
 * @param data (void*) this is a pointer to the application specific data maintained by the OS.
 */
static bool app_create(void *data)
{
	tsBWA_AppData *ad = data;
	Evas_Object* button;

	// create the control app callback
	app_control_create(&tsBWA_AppController);
	app_control_set_operation(tsBWA_AppController, APP_CONTROL_OPERATION_DEFAULT); //Sets the application operation (default is launch).
	app_control_set_app_id(tsBWA_AppController, PACKAGE); //Sets the application ID to launch.

	dlog_print(DLOG_ERROR, "setting_delay", "app_create");

    // create a window.
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);
	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}
	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	ad->conform = elm_conformant_add(ad->win);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	/* Label */
	/* Create an actual view of the base gui.
	   Modify this part to change the view. */
	ad->label = elm_label_add(ad->conform);

	evas_object_size_hint_weight_set(ad->label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(ad->conform, ad->label);

	ad->box = elm_box_add(ad->win);
	evas_object_size_hint_weight_set(ad->box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(ad->box);
	elm_win_resize_object_add(ad->win, ad->box);

	// create the button, the alarm is on by default, therefore the initial message is
	// "Click to deactivate"
	button = elm_button_add(ad->box);
	elm_object_text_set(button, "Click to deactivate");
	evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 0.5);
	elm_box_pack_end(ad->box, button);
	evas_object_show(button);

	// assign the callback function when the button is clicked.
	evas_object_smart_callback_add(button, "clicked", buttonClickCallback, NULL);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);

	return true;
}

// This function is triggered by an alarm after a random delay.
// It then retriggers itself after a further random delay.
static void app_control(app_control_h app_control, void *data)
{
	// get a random delay in seconds.
	// TODO: currently hardcoded between 1 and 3 minutes.
	int iDelayOne = timeDelay(1, 3);

	// retrigger itself after the random delay
    alarm_schedule_once_after_delay(tsBWA_AppController, iDelayOne, &iBWA_AlarmId);

	tsBWA_AppData *ad = data;

	// generate a random number between 0 and 10
	int random_number;
	srand((unsigned)time(NULL));
	random_number = rand() % 10;
	random_number++;

	// only vibrate if the user has enabled vibration.
	if (bBWA_Vibrate == TRUE)
	{
		// vibrate in a random vibration pattern
		VH_vibrate(random_number);
	}

    // display the message to the screen
	// TODO: alter this to the time till next buzz
	elm_object_text_set(ad->label, "<align=center>Hello WAM guys</align>");
	evas_object_show(ad->win);
}

static void app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void app_resume(void *data)
{
	return;
}

static void app_terminate(void *data)
{
	VH_kill();
	/* Release all resources. */
}


static void ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}


// This main function assigns all the callbacks for the application that the OS
// triggers.
int main(int argc, char *argv[])
{
	tsBWA_AppData ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
