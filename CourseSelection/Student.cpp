#include "Student.h"

Student::Student(std::string na, int id, std::string pw)
{
    name=na;
    ID=id;
    password=pw;
}

std::string Student::get_name()
{
    return name;
}

int Student::get_id()
{
    return ID;
}

int Student::get_cll()
{
    return cll;
}

int Student::get_course_id(int n)
{
    return courselist[n];
}

int Student::check_password(const std::string &pw) const
{
    if (pw==password) return 1;
    else return 0;
}

void Student::add_course(int id)
{
    courselist[cll++]=id;
}

void Student::remove_course(int id)
{
    int p;
    for (int i=0;i<cll;i++)
    {
        if (courselist[i]==id)
            p=i;
    }
    for (int i=p;i<cll-1;i++)
        courselist[i]=courselist[i+1];
    cll--;
}

int Student::check_course_in(int id)
{
    int f=0;
    for (int i=0;i<cll;i++)
    {
        if (courselist[i]==id)
            f=1;
    }
    return f;
}
