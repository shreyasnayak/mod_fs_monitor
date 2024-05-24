/** @file mod_fs_monitor.cpp
 *
 * @copyright (C) 2024
 * @date 2024.05.24
 * @version 1.0.0
 * @author Shreyas Nayak <shreyasnayak21@gmail.com>
 *
*/


extern "C" {
#include <switch.h>
}

#include <QCoreApplication>
#include <QTimer>

class QtExample : public QObject {
    Q_OBJECT

public:
    QtExample() {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &QtExample::onTimeout);
        timer->start(1000); // 1-second interval
    }

public slots:
    void onTimeout() {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "QtExample timer timeout.\n");
    }
};

int qt_example_main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QtExample example;
    return app.exec();
}

extern "C" {

// Module load function
SWITCH_MODULE_LOAD_FUNCTION(mod_fs_monitor_load) {
    int argc = 0;
    char *argv[] = {};
    // std::thread qtThread(qt_example_main, argc, argv);
    // qtThread.detach();
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor loaded.\n");
    return SWITCH_STATUS_SUCCESS;
}

// Module shutdown function
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_fs_monitor_shutdown) {
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "mod_fs_monitor shutting down.\n");
    return SWITCH_STATUS_SUCCESS;
}

// Module definition
SWITCH_MODULE_DEFINITION(mod_fs_monitor, mod_fs_monitor_load, mod_fs_monitor_shutdown, NULL);

}
