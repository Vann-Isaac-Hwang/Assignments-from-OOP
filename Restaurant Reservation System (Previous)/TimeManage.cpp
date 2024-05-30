//
// Created by huang on 5/25/2024.
//

#include "TimeManage.h"

TimeManage::TimeManage()
{

}

std::string str_time()
{
    std::time_t current_time = std::time(nullptr);
    //std::cout << "Current date: " << std::asctime(std::localtime(&current_time)) << std::endl;

    std::string str_time=std::asctime(std::localtime(&current_time));
    str_time.pop_back(); //Avoid '\n' at the end of the string
    return str_time;
}

int get_year()
{
    std::time_t current_time = std::time(nullptr);
    return std::localtime(&current_time)->tm_year+1900;
}

int get_month()
{
    std::time_t current_time = std::time(nullptr);
    return std::localtime(&current_time)->tm_mon+1;
}

int get_day()
{
    std::time_t current_time = std::time(nullptr);
    return std::localtime(&current_time)->tm_mday;
}

int get_hour()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_hour;
}

int get_minute()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_min;
}
