/** @file mod_fs_monitor.cpp
 *
 * @copyright (C) 2024
 * @date 2024.05.24
 * @version 1.0.0
 * @author Shreyas Nayak <shreyasnayak21@gmail.com>
 *
*/


#include <switch.h>

static void event_handler(switch_event_t *event)
{
    const char *event_name = switch_event_name(event->event_id);
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "::::::::::::::::::::::::::::::::::::::::::::::::::::::: Received event: %s\n", event_name);
}

extern "C"
{
    SWITCH_MODULE_LOAD_FUNCTION(mod_fs_monitor_load);
    SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_fs_monitor_shutdown);
    SWITCH_MODULE_RUNTIME_FUNCTION(mod_fs_monitor_runtime);
    SWITCH_MODULE_DEFINITION(mod_fs_monitor, mod_fs_monitor_load, mod_fs_monitor_shutdown, NULL);
}

SWITCH_MODULE_LOAD_FUNCTION(mod_fs_monitor_load)
{
    *module_interface = switch_loadable_module_create_module_interface(pool, modname);

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor loaded.\n");
    return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_fs_monitor_shutdown)
{
    // Unregister event handler
    if (switch_event_bind(modname, SWITCH_EVENT_ALL, SWITCH_EVENT_SUBCLASS_ANY, event_handler, NULL) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Couldn't bind!\n");
        return SWITCH_STATUS_GENERR;
    }

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor shutting down.\n");
    return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_RUNTIME_FUNCTION(mod_fs_monitor_runtime)
{
    return SWITCH_STATUS_TERM;
}
