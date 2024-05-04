#include <iostream>
#include <thread>
#include <ctime>

class CDate
{
public:
    time_t display_current_date()
    {
        std::time_t current_time = std::time(nullptr);
        std::cout << "Current date: " << std::asctime(std::localtime(&current_time)) << std::endl;
    }
};
