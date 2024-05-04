#include "Course.h"

Course::Course(std::string na, int id, int cre_hour, int vol)
{
    name=na;
    ID=id;
    credit_hour=cre_hour;
    volumn=vol;
    stu_num=0;
}

std::string Course::get_name()
{
    return name;
}

int Course::get_id()
{
    return ID;
}

int Course::get_credit_hour()
{
    return credit_hour;
}

int Course::get_stu_num()
{
    return stu_num;
}
int Course::get_volumn()
{
    return volumn;
}

void Course::stu_plus()
{
    stu_num++;
}

void Course::stu_minus()
{
    stu_num--;
}
