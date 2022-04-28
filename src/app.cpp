#include "app.h"

#include "pch.h"

#include "module_loader.h"
#include "compile.h"

#include <unistd.h>
#include <thread>

bool App::shouldClose = false;
SubscriberID App::engineEvents;
DataManager App::dataManager;

void App::init(int argc, char ** argv)
{
    dataManager.allocate<Dispatcher>("dispatcher");
    Dispatcher &dispatcher = dataManager.get<Dispatcher>("dispatcher");

    engineEvents = dispatcher.createSubscriber();

    dispatcher.subscribe(engineEvents, "APP_CLOSE", [&](const Event &e)
    {
        App::shouldClose = true;
    });
}
void App::shutdown()
{

}

void App::run()
{
    DynamicModule dm("../script/src/window_script.cpp", "../script/out/window_script.so", dataManager);
    while (!App::shouldClose)
    {
        dm.onUpdate(0.01);
    }
    
}
