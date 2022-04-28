#ifndef MODULE_LOADER_H
#define MODULE_LOADER_H

#include "pch.h"

#include "base_script.h"
#include "filewatcher.h"
#include "compile.h"

void* openLibrary(const char *libraryPath);
void* getFunction(void* handle, const char *functionName);
void closeLibrary(void *handle);
char* getError();

typedef BaseScript*(*create_t)(DataManager &dataManager);
typedef void(*remove_t)(BaseScript*);

class StaticModule
{
public:
    StaticModule(const char *filePath, DataManager &dataManager);
    ~StaticModule();

    void onUpdate(float deltaTime);

private:
    void load();

private:
    void* handle;
    BaseScript *script;
    create_t create;
    remove_t remove;
    std::string filePath;
    DataManager &dataManager;
};

class DynamicModule
{
public:
    DynamicModule(const char *srcPath, const char *filePath, DataManager &dataManager);
    ~DynamicModule();

    void onUpdate(float deltaTime);

    void onModuleReload();
private:
    void load();
    void terminate();

private:
    BaseScript *script;
    std::string filePath;
    std::string srcPath;
    create_t create;
    remove_t remove;
    DataManager &dataManager;
    FileWatcher fileWatcher;
    void* handle;
};

class DynamicModuleFileRecompileEvent : public Event
{
public: 
    DynamicModuleFileRecompileEvent(DynamicModule &module_);

    DynamicModule &module_;
};

#endif