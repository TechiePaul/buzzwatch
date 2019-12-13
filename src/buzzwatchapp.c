#include "buzzwatchapp.h"
#include "device/haptic.h"
#include "vibHandler.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <app_alarm.h>

int alarm_id = 0;
app_control_h app_controller;

/*
	int random_number;
	srand((unsigned)time(NULL));
	random_number = rand() % 10;
	random_number++;

    For Charlie.
*/

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
    Evas_Object *box;
    Evas_Object *list;
} appdata_s;
typedef struct appdata appdata_s;

//Returns the delay in seconds that it randomly generated from min_delay to max_delay.
int timeDelay(int min_delay, int max_delay){
	srand((unsigned)time(NULL));
	int delay_in_mins = rand() % (max_delay + 1 - min_delay);
	int delay_in_seconds = delay_in_mins * 60;
	delay_in_seconds = delay_in_seconds + (min_delay * 60);
	return(delay_in_seconds);
}

static bool
app_create(void *data)
{
	app_control_create(&app_controller);
	app_control_set_operation(app_controller, APP_CONTROL_OPERATION_DEFAULT); //Sets the application operation (default is launch).
	app_control_set_app_id(app_controller, PACKAGE); //Sets the application ID to launch.

	//int error_handler = alarm_schedule_once_after_delay(app_controller, 10, &alarm_id);

	//alarm_schedule_once_after_delay(app_controller, 10, &alarm_id);

	VH_vibrate(3);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	int delay_one = timeDelay(1, 2);
	int error_handler_two = alarm_schedule_once_after_delay(app_controller, delay_one, &alarm_id);

	//dlog_print(DLOG_DEBUG, LOG_TAG, "app_resume  - delay: %d", delay_one);

	int random_number;
	srand((unsigned)time(NULL));
	random_number = rand() % 10;
	random_number++;
	VH_vibrate(random_number);
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	int delay_two = timeDelay(1, 2);
	int error_handler_three = alarm_schedule_once_after_delay(app_controller, delay_two, &alarm_id);

	//dlog_print(DLOG_DEBUG, LOG_TAG, "app_resume  - delay: %d", delay_two);

	int random_number;
	srand((unsigned)time(NULL));
	random_number = rand() % 10;
	random_number++;
	VH_vibrate(random_number);
	return;
}

static void
app_terminate(void *data)
{
	VH_kill();
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
