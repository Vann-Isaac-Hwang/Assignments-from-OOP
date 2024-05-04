#include <iostream>

class Student
{
public:
    Student(std::string na, int id, std::string pw);
    std::string get_name();
    int get_id();
    int check_password(const std::string &pw) const;

    void add_course(int id);

    void remove_course(int id);

    int get_cll();

    int check_course_in(int id);

    int get_course_id(int n);

private:
    std::string name, password;
    int ID, cll=0;
    int courselist[50];
};
