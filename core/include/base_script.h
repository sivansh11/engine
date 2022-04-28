#ifndef ENGINE_SCRIPT_H
#define ENGINE_SCRIPT_H

#include "event.h"
#include "data_manager.h"

#define add_include_dir(x)
#define add_src_path(x)
#define add_option(x)
#define add_o_file(x)
#define add_link_libraries(x)
#define add_link_library_path(x)

class AppShouldClose : public Event
{
public:
    AppShouldClose() : Event("APP_CLOSE") {}

};


class BaseScript
{
public:
    virtual ~BaseScript();
    virtual void onCreate();
    virtual void onDelete();
    virtual void onUpdate(float deltaTime);

private:

};

#endif