#include "relaunch.h"

void launchUIapp(const char *AppID)
{
    app_control_h app_control = NULL; //app_control handle
	app_control_create(&app_control);
	app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT); //sets the app operation (default is launch)
	app_control_set_app_id(app_control, AppID); //sets the app ID to launch

	// Requests a launch of the application, Logs if the application launched correctly or not
	if(app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE)
	{
	    dlog_print(DLOG_INFO, "TEST LAUNCH", "Succeeded to launch Buzz Watch app UI.");
		// app launched successfully
	}
	else
	{
	    dlog_print(DLOG_ERROR, "TEST LAUNCH", "Failed to launch Buzz Watch app UI.");
	    // app launched unsuccessfully
	}

	app_control_destroy(app_control); // Releases resources back to the OS
}
