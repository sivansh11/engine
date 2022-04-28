#ifndef DEBUGMESSAGE_H
#define DEBUGMESSAGE_H

#include <iostream>

namespace debug
{
    void message(const char * m);
    
    class Log
    {
    public:
        Log(const char * name);
        ~Log();
    private:
        std::string name;
    };
} // namespace debug

#ifdef DEBUG_INFO

#pragma message("DEBUG INFO ENABLED")

#define DEBUG_MESSAGE(x) debug::message(x)

#define DEBUG_LOG(x) debug::Log(x)

#else

#define DEBUG_MESSAGE(x)
#define DEBUG_LOG(x)


#endif

#endif

