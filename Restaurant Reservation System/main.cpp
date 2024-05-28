#include "login.h"

#include <QApplication>

void pioneer();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login lw;
    pioneer(); // Used to initialize or test.
    lw.show();
    return a.exec();
}

void pioneer()
{
    AccessDB db("data.db");


    db.clear_administrator_table();
    db.reset_administrator_id();
    db.create_administrator_table();

    db.create_user_table();
    db.create_reservation_table();

    db.add_administrator("admin", "123456");/*
    db.add_administrator("admin2", "123455");
    db.add_administrator("admin3", "123456");
    db.add_administrator("admin4", "123456");
    db.print_all("administrator");*/

    /*
    db.clear_user_table();
    db.reset_user_id();
    */

    /*
    db.create_user_table();
    db.add_user("huang", "123456", "isk", "13867762244");
    db.add_user("zhang", "123456", "isk", "13867762244");
    db.add_user("li", "123456", "pjsk", "13867762244");*/
/*/
    db.clear_reservation_table();
    db.reset_reservation_id();
    db.create_reservation_table();
    duration d1;
    d1.year=2024, d1.month=9,d1.day=9,d1.hour_begin=16,d1.minute_begin=0,d1.second_begin=0,d1.hour_end=18,d1.minute_end=0,d1.second_end=0;
    reservation r1;
    r1.deposit=1000,r1.dur=d1,r1.id=1,r1.table_id=1,r1.table_type="A",r1.user_name="Isaac";
    db.add_reservation(r1);

    //db.create_reservation_table();
    //duration d1;
    d1.year=2024, d1.month=9,d1.day=9,d1.hour_begin=16,d1.minute_begin=0,d1.second_begin=0,d1.hour_end=18,d1.minute_end=0,d1.second_end=0;
    //reservation r1;
    r1.deposit=100,r1.dur=d1,r1.id=1,r1.table_id=1,r1.table_type="A",r1.user_name="aan";
    db.add_reservation(r1);

    //db.create_reservation_table();
    //duration d1;
    d1.year=2024, d1.month=9,d1.day=9,d1.hour_begin=16,d1.minute_begin=0,d1.second_begin=0,d1.hour_end=18,d1.minute_end=0,d1.second_end=0;
    //reservation r1;
    r1.deposit=100,r1.dur=d1,r1.id=1,r1.table_id=1,r1.table_type="A",r1.user_name="Van";
    db.add_reservation(r1);
/*/
}
