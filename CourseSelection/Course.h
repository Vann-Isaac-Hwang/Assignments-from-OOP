#include <iostream>

class Course
{
public:
    Course(std::string na, int id, int credit_hour, int vol);
    std::string get_name();
    int get_id();
    int get_credit_hour();
    int get_stu_num();
    int get_volumn();
    void stu_plus();
    void stu_minus();
private:
    std::string name;
    int ID, credit_hour, stu_num, volumn;
};
