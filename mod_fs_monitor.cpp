/** @file mod_fs_monitor.cpp
 *
 * @copyright (C) 2024
 * @date 2024.05.24
 * @version 1.0.0
 * @author Shreyas Nayak <shreyasnayak21@gmail.com>
 *
*/


#include <switch.h>

// switch_event_callback_t
static switch_status_t fs_event_handler(switch_event_t *event) {
    // Print the event name
    const char *event_name = switch_event_name(event->event_id);
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Received event: %s\n", event_name);
    return SWITCH_STATUS_SUCCESS;
}

extern "C"
{
    SWITCH_MODULE_LOAD_FUNCTION(mod_fs_monitor_load);
    SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_fs_monitor_shutdown);
    SWITCH_MODULE_DEFINITION(mod_fs_monitor, mod_fs_monitor_load, mod_fs_monitor_shutdown, NULL);
}

SWITCH_MODULE_LOAD_FUNCTION(mod_fs_monitor_load)
{
    // Registering event handler for all events
    switch_event_bind("mod_fs_monitor", SWITCH_EVENT_ALL, SWITCH_EVENT_SUBCLASS_ANY, fs_event_handler, NULL);

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor loaded.\n");
    return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_fs_monitor_shutdown)
{
    // Unregister event handler
    switch_event_unbind_callback(fs_event_handler);

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor shutting down.\n");
    return SWITCH_STATUS_SUCCESS;
}
