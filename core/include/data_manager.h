#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "pch.h"

class DataManager
{
public:
    DataManager()
    {

    }
    ~DataManager()
    {
        for (auto kv: dataMap)
        {
            delete[] dataMap[kv.first];
        }
    }

    template <typename T, typename... Args>
    T& allocate(const char *name, Args&&... args)
    {
        size_t bytes = sizeof(T);
        char* data = new char[bytes];
        new (data)T(std::forward<Args>(args)...);
        dataMap[name] = data;
        return *((T*)data);
    }
    template <typename T>
    T& get(const char *name)
    {
        auto data = dataMap.find(name);
        ASSERT(data != dataMap.end(), (std::string() + "data not there in map :" + name));
        return *((T*)(data->second));
    }

    void showContents()
    {
        for (auto kv: dataMap)
        {
            std::cout << kv.first << '\n';
        }
        std::cout << "----------------------------------------------------------------------------------------\n";
    }

private:
    std::unordered_map<std::string, char*> dataMap;
};

#endif