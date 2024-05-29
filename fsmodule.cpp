#include "fsmodule.h"

FSModule* FSModule::m_Instance = nullptr;

FSModule::FSModule() : QThread()
{

}

FSModule::~FSModule()
{
    if(m_timer != nullptr)
    {
        m_timer->stop();
        delete m_timer;
    }
    switch_event_unbind_callback(eventHandler);
    quit();
    wait();
}

FSModule *FSModule::GetInstance()
{
    if(FSModule::m_Instance == nullptr)
    {
        FSModule::m_Instance = new FSModule();
    }
    return FSModule::m_Instance;
}

void FSModule::eventHandler(switch_event_t *event)
{
    const char *event_name = switch_event_name(event->event_id);
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "::::::::::::::::::::::::::::::::::::::::::::::::::::::: Received event: %s\n", event_name);

    // Print the event headers
    switch_event_header_t *header = NULL;
    for (header = event->headers; header; header = header->next) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Header: %s: %s\n", header->name, header->value);
    }

    // Print the body if it exists
    if (event->body) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Body: %s\n", event->body);
    }
}

void FSModule::apiRequest(switch_core_session_t *session, const char *data)
{
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Example application executed\n");
}

bool FSModule::initialize(const char* modname, switch_loadable_module_interface_t **module_interface)
{
    // Set event handler
    if (switch_event_bind(modname, SWITCH_EVENT_ALL, SWITCH_EVENT_SUBCLASS_ANY, eventHandler, NULL) != SWITCH_STATUS_SUCCESS) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Couldn't bind!\n");
        return SWITCH_STATUS_GENERR;
    }

    // Set API Handler
    switch_application_interface_t *app_interface;
    SWITCH_ADD_APP(app_interface, "fs_monitor", "FreeSWITCH Monitor", "FreeSWITCH event listener application", apiRequest, "<arguments>", SAF_NONE);

    // Start event loop
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "Timer callback executed");
    });
    m_timer->setSingleShot(false);
    m_timer->start(1000); // Emit log every 10 seconds
    m_timer->moveToThread(this);
    start();
    return true;
}

void FSModule::shutdown()
{
    if(FSModule::m_Instance != nullptr)
    {
        delete FSModule::m_Instance;
    }
}

void FSModule::run()
{
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, ":::::::::::::::::::run()");
    exec();
}
