//
// Created by huang on 4/11/2024.
//

#include "CDate.h"

void CDate::display_current_date()
{
    std::time_t current_time = std::time(nullptr);
    std::cout << "Current date: " << std::asctime(std::localtime(&current_time)) << std::endl;
}