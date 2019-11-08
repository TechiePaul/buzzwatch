#include "buzzwatchapp.h"
#include "device/haptic.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
    Evas_Object *box;
    Evas_Object *list;
} appdata_s;
typedef struct appdata appdata_s;

bool vibEnabled = true;

haptic_device_h myVibratingThing;

void vibrate();
void vibrate(vibPattern){

	/*
	 * The delays are measured microseconds, not milliseconds.
	 *
	 * This is because sleep() takes an integer, not a float/double.
	 * To compensate for this, I use usleep().
	 * To use this, put the time in milliseconds + 3 zeros.
	 * E.g. usleep(1000000) - One second.
	 */

	int usleep(useconds_t useconds);

 	int returnedVal;

	haptic_effect_h effect_handle;
	returnedVal = device_haptic_open(0, &myVibratingThing);

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
		dlog_print(DLOG_WARN, "vibrate() error", "Error in function vibrate(). Pattern is not valid. (1 to 10, 0 to cancel).");
		break;
	}

}

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static bool
app_create(void *data)
{
	device_haptic_close(myVibratingThing);
	while(true)
	{
		int random_number;
		srand((unsigned)time(NULL));
		random_number = rand() % 10;
		random_number++;
		vibrate(random_number);
	}

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	device_haptic_close(myVibratingThing);
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
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
