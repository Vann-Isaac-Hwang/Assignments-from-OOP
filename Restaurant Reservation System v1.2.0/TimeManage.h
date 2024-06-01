//
// Created by huang on 5/25/2024.
//

#ifndef ACCESSDATABASE_TIMEMANEGE_H
#define ACCESSDATABASE_TIMEMANEGE_H

#include <ctime>
#include <iostream>

struct duration{
    int year, month, day;
    int hour_begin, minute_begin, second_begin;
    int hour_end, minute_end, second_end;
};

std::string str_time();
int get_year() ;
int get_month() ;
int get_day() ;
int get_hour();
int get_minute();


class TimeManage {
public:
    TimeManage();

private:

};


#endif //ACCESSDATABASE_TIMEMANEGE_H
