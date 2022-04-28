#include "app.h"

#include <exception>

int main(int argc, char ** argv)
{
    App::init(argc, argv);
    try
    {
        App::run();
    }
    catch (...)
    {
        std::cout << "Something Went Wrong\n";
    }
    App::shutdown();
    return 0;
}