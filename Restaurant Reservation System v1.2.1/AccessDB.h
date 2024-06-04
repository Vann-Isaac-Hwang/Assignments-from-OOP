//
// Created by huang on 5/23/2024.
//

#ifndef ACCESSDATABASE_ACCESSDB_H
#define ACCESSDATABASE_ACCESSDB_H

#include <iostream>
#include "sqlite3.h"
#include "TimeManage.h"

struct admin{
    int id;
    std::string name;
    std::string password;
};

struct user{
    int id;
    std::string name, nickname;
    std::string password, phone_number;
    void print() const{
        std::cout<<"id: "<<id<<std::endl;
        std::cout<<"name: "<<name<<std::endl;
        std::cout<<"nickname: "<<nickname<<std::endl;
        std::cout<<"password: "<<password<<std::endl;
        std::cout<<"phone_number: "<<phone_number<<std::endl;
    }
};

struct reservation{
    int id;
    std::string user_name;
    duration dur;
    std::string table_type;
    int table_id;
    int deposit;
};

struct food{
    int id;
    std::string name;
    int price;
    std::string description;
};

struct pair{
    int id;
    int reservation_id;
    int food_id;
};

class AccessDB{
private:
    sqlite3* db = nullptr;
    int rc;
    std::string db_name;

public:
    // CONSTRUCTOR AND DESTRUCTOR
    explicit AccessDB(const std::string& db_name); // Open the database according to the name.
    ~AccessDB(); // Close the database.
    
    // CREATE TABLE
    bool create_administrator_table(); // Create the administrator table.
    bool create_user_table(); // Create the user table.
    bool create_reservation_table(); // Create the reservation table.
    bool create_food_table(); // Create the food table.
    bool create_pair_table(); // Create the pair table.
    bool reset_sqlite_sequence(); // Reset the sqlite_sequence.
    
    // MANIPULATE ADMINISTRATOR TABLE
    bool add_administrator(const std::string& name, const std::string& password);
    bool delete_administrator(const std::string& name);
    bool delete_administrator(int id);
    bool modify_administrator_name(int id, const std::string& target_name);
    bool modify_administrator_password(int id, const std::string& target_password);
    bool reset_administrator_id();
    bool clear_administrator_table();

    // MANIPULATE USER TABLE
    bool add_user(const std::string& name, const std::string& password, const std::string& nickname, const std::string& phone_number);
    bool delete_user(const std::string& name);
    bool delete_user(int id);
    bool modify_user_name(int id, const std::string& target_name);
    bool modify_user_password(int id, const std::string& target_password);
    bool modify_user_nickname(int id, const std::string& target_nickname);
    bool modify_user_phone_number(int id, const std::string& target_phone_number);
    bool reset_user_id();
    bool clear_user_table();

    // MANIPULATE RESERVATION TABLE
    bool add_reservation(const std::string& user_name, const duration& dur, const std::string& table_type, int table_id, int deposit);
    bool add_reservation(const reservation& res) const;
    bool delete_reservation(const std::string& user_name);
    bool delete_reservation(int id);
    bool replace_all_username(const std::string& old_name, const std::string& new_name);
    bool modify_reservation_user_name(int id, const std::string& target_user_name);
    bool modify_reservation_duration(int id, const duration& target_dur);
    bool modify_reservation_table_type(int id, const std::string& target_table_type);
    bool modify_reservation_table_id(int id, int target_table_id);
    bool modify_reservation_deposit(int id, int target_deposit);
    bool reset_reservation_id();
    bool clear_reservation_table();

    // MANIPULATE FOOD TABLE
    bool add_food(const std::string& name, int price, const std::string& description);
    bool delete_food(const std::string& name);
    bool delete_food(int id);
    bool modify_food_name(int id, const std::string& target_name);
    bool modify_food_price(int id, int target_price);
    bool modify_food_description(int id, const std::string& target_description);
    bool reset_food_id();
    bool clear_food_table();

    // MANIPULATE PAIR TABLE
    bool add_pair(int reservation_id, int food_id);
    bool delete_pair(int reservation_id, int food_id);
    bool delete_pair(int reservation_id);
    bool delete_pair_by_id(int pair_id);
    bool reset_pair_id();
    bool clear_pair_table();

    // ACQUIRE INFORMATION
    [[nodiscard]] bool check_exist(int id, const std::string& table) const;
    [[nodiscard]] bool check_exist(const std::string& name, const std::string& table) const;
    [[nodiscard]] user get_user_info(int id) const;
    [[nodiscard]] user get_user_info(const std::string& name) const;
    [[nodiscard]] admin get_administrator_info(int id) const;
    [[nodiscard]] admin get_administrator_info(const std::string& name) const;
    [[nodiscard]] reservation get_reservation_info(int id) const;
    [[nodiscard]] reservation get_reservation_info(const std::string& user_name) const;
    [[nodiscard]] food get_food_info(int id) const;
    [[nodiscard]] food get_food_info(const std::string& name) const;
    [[nodiscard]] pair get_pair_info(int id) const;
    [[nodiscard]] pair get_pair_info(int reservation_id, int food_id) const;
    [[nodiscard]] int get_table_length(const std::string& table) const;
    [[nodiscard]] reservation getReservationInfo(int index) const;
    [[nodiscard]] user getUserInfo(int index) const;
    [[nodiscard]] food getFoodInfo(int index) const;
    [[nodiscard]] pair getPairInfo(int index) const;

    // VERIFY PASSWORD
    [[nodiscard]] bool verify_password(const std::string& name, const std::string& password,const std::string& table) const;
    [[nodiscard]] bool verify_password(int id, const std::string& password, const std::string& table) const;
    [[nodiscard]] bool verify_password_phone(const std::string& phone_number, const std::string& password) const;

    // PRINT INFORMATION
    void print_all(const std::string& table) const; //UPDATE
    void print_all() const; //UPDATE

};


#endif //ACCESSDATABASE_ACCESSDB_H
