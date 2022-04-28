#ifndef APP_H
#define APP_H

#include "event.h"
#include "data_manager.h"
// #include "ecs.h"

class App
{
public:
    static void init(int argc, char ** argv);
    static void shutdown();

    static void run();
private:
    static bool shouldClose;
    static SubscriberID engineEvents;
    static DataManager dataManager;
};

#endif