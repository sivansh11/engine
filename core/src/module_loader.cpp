#include "module_loader.h"

#include <cassert>

#ifdef LINUX
#pragma message("LINUX BUILD")

#include <dlfcn.h>
void* openLibrary(const char *libraryPath)
{
    return dlopen(libraryPath, RTLD_LAZY);
}

void* getFunction(void* handle, const char *functionName)
{
    return dlsym(handle, functionName);
}

void closeLibrary(void *handle)
{
    dlclose(handle);
}
char* getError()
{
    return dlerror();
}

#elif WINDOW


#endif

#include <unistd.h>


StaticModule::StaticModule(const char *filePath, DataManager &dataManager) : filePath(filePath), dataManager(dataManager)
{
    handle = openLibrary(filePath);
    load();
}

StaticModule::~StaticModule()
{
    remove(script);
    closeLibrary(handle);
}

void StaticModule::load()
{
    create = (create_t)getFunction(handle, "create_");
    remove = (remove_t)getFunction(handle, "remove_");
    // std::cout << getError() << '\n';
    script = create(dataManager);

}

void StaticModule::onUpdate(float deltaTime)
{
    script->onUpdate(deltaTime);
}

DynamicModuleFileRecompileEvent::DynamicModuleFileRecompileEvent(DynamicModule &module_) : Event("FILE_RECOMPILE"), module_(module_)
{

}


DynamicModule::DynamicModule(const char *srcPath, const char *filePath, DataManager &dataManager) :
    filePath(filePath), srcPath(srcPath), fileWatcher(srcPath), dataManager(dataManager)
{    
    compile(srcPath, filePath);
    handle = openLibrary(filePath);
    load();
}

DynamicModule::~DynamicModule()
{
    terminate();
}

void DynamicModule::load()
{
    create = (create_t)getFunction(handle, "create_");
    remove = (remove_t)getFunction(handle, "remove_");
    script = create(dataManager);
    assert(script);
}

void DynamicModule::terminate()
{
    remove(script);
    closeLibrary(handle);
}

void DynamicModule::onModuleReload()
{
    terminate();
    compile(srcPath.c_str(), filePath.c_str());
    handle = openLibrary(filePath.c_str());
    load();
}

void DynamicModule::onUpdate(float deltaTime)
{
    if (fileWatcher.hasChanged())
    {
        onModuleReload();
    }
    script->onUpdate(deltaTime);

}