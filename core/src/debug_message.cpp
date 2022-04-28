#include "debug_message.h"

namespace debug
{
    Log::Log(const char *name) : name(name)
    {
        std::cout << "entered " << name << '\n';
    }
    Log::~Log()
    {
        std::cout << "exited " << name << '\n';
    }
    void message(const char * m)
    {
        std::cout << m << '\n';
    }
} // namespace debug

    