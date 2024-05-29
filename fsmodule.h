#ifndef FSMODULE_H
#define FSMODULE_H

#include <QThread>
#include <QObject>
#include <switch.h>
#include <QTimer>

class FSModule : public QThread
{
    QTimer *m_timer;
    static FSModule* m_Instance;
    static void eventHandler(switch_event_t *event);
    static void apiRequest(switch_core_session_t *session, const char *data);
    FSModule();
    ~FSModule();
public:
    static FSModule* GetInstance();
    bool initialize(const char* modname,switch_loadable_module_interface_t **module_interface);
    void shutdown();
protected:
    void run() override;
};

#endif // FSMODULE_H
