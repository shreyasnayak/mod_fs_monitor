/** @file mod_fs_monitor.cpp
 *
 * @brief FreeSWITCH Call Event Monitor Module Implementation
 *
 * This file contains the implementation of the FreeSWITCH Call Event Monitor 
 * module, which provides functionality to monitor call events within the 
 * FreeSWITCH telephony platform. The module listens for call events such as 
 * call creation, termination, and state changes, and prints relevant information
 * to the console or a log file.
 *
 * @date 2024.05.24
 * @version 1.0.0
 * @author
 * Shreyas Nayak <shreyasnayak21@gmail.com>
 *
 */

#include <switch.h>
#include "fsmodule.h"

FSModule* instance = nullptr;

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
    instance = FSModule::GetInstance();
    if (!instance->initialize(modname,module_interface)) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "mod_fs_monitor initialize failed.\n");
        instance->shutdown();
        instance = nullptr;
        return SWITCH_STATUS_FALSE;
    }

    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor loaded.\n");
    return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_fs_monitor_shutdown)
{
    if(instance!=nullptr)
    {
        instance->shutdown();
    }
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor shutting down.\n");
    return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_RUNTIME_FUNCTION(mod_fs_monitor_runtime)
{
    return SWITCH_STATUS_TERM;
}
