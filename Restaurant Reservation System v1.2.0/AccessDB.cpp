//
// Created by huang on 5/23/2024.
//

#include "AccessDB.h"

// CONSTRUCTOR AND DESTRUCTOR

AccessDB::AccessDB(const std::string& db_name) {
    std::cout<<"Trying to open database: "<<db_name<<" ..."<<std::endl;
    this->db_name = db_name;
    rc = sqlite3_open(db_name.c_str(), &db);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "open failed\n");
    }
    else
    {
        std::cout << "open success"<<std::endl;
    }
}

AccessDB::~AccessDB() {
    std::cout<<"Closing database "<<db_name<<" ..."<<std::endl;
    sqlite3_close(db);
}

// CREATE TABLE

bool AccessDB::create_administrator_table() {
    std::cout<<"Trying to create administrator table ..."<<std::endl;
    std::string sql = "CREATE TABLE administrator (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, password TEXT NOT NULL);";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "create administrator table failed\n");
        std::cout<<"create administrator table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "create administrator table success"<<std::endl;
    }
    return true;
}

bool AccessDB::create_user_table()
{
    std::cout<<"Trying to create user table ..."<<std::endl;
    std::string sql = "CREATE TABLE user (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, nickname TEXT NOT NULL, password TEXT NOT NULL, phone_number TEXT NOT NULL);";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "create user table failed\n");
        std::cout<<"create user table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "create user table success"<<std::endl;
    }
    return true;
}

bool AccessDB::create_reservation_table() {
    std::cout<<"Trying to create reservation table ..."<<std::endl;
    std::string sql = "CREATE TABLE reservation (id INTEGER PRIMARY KEY AUTOINCREMENT, user_name TEXT NOT NULL,"
                      "year INTEGER NOT NULL, month INTEGER NOT NULL, day INTEGER NOT NULL,"
                      "start_hour INTEGER NOT NULL, start_minute INTEGER NOT NULL,"
                      "end_hour INTEGER NOT NULL, end_minute INTEGER NOT NULL,"
                      " table_type TEXT NOT NULL, table_id INTEGER NOT NULL, deposit INTEGER NOT NULL);";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "create reservation table failed\n");
        std::cout<<"create reservation table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "create reservation table success"<<std::endl;
    }
    return true;
}

bool AccessDB::create_food_table() {
    std::cout<<"Trying to create food table ..."<<std::endl;
    std::string sql = "CREATE TABLE food (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, price INTEGER NOT NULL, description TEXT NOT NULL);";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "create food table failed\n");
        std::cout<<"create food table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "create food table success"<<std::endl;
    }
    return true;
}

bool AccessDB::create_pair_table() {
    std::cout<<"Trying to create pair table ..."<<std::endl;
    std::string sql = "CREATE TABLE pair (id INTEGER PRIMARY KEY AUTOINCREMENT, reservation_id INTEGER NOT NULL, food_id INTEGER NOT NULL);";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "create pair table failed\n");
        std::cout<<"create pair table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "create pair table success"<<std::endl;
    }
    return true;
}

bool AccessDB::reset_sqlite_sequence() {
    std::cout<<"Resetting sqlite_sequence ..."<<std::endl;
    std::string sql = "DELETE FROM sqlite_sequence;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "reset sqlite_sequence failed\n");
        std::cout<<"reset sqlite_sequence failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "reset sqlite_sequence success"<<std::endl;
    }
    return true;
}

// MANIPULATE ADMINISTRATOR TABLE

bool AccessDB::add_administrator(const std::string& name, const std::string& password) {
    std::cout<<"Trying to add administrator ..."<<std::endl;
    std::string sql = "INSERT INTO administrator (name, password) VALUES ('"+name+"', '"+password+"');";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "add administrator failed\n");
        std::cout<<"add administrator failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "add administrator success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_administrator(const std::string& name) {
    std::cout<<"Trying to delete user ..."<<std::endl;
    std::string sql = "DELETE FROM administrator WHERE name = '"+name+"';";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete administrator failed\n");
        std::cout<<"delete administrator failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete administrator success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_administrator(int id) {
    std::cout<<"Trying to delete administrator ..."<<std::endl;
    std::string sql = "DELETE FROM administrator WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete administrator failed\n");
        std::cout<<"delete administrator failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete administrator success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_administrator_name(int id, const std::string& target_name) {
    std::cout<<"Trying to modify administrator name ..."<<std::endl;
    std::string sql = "UPDATE administrator SET name = '"+target_name+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify administrator name failed\n");
        std::cout<<"modify administrator name failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify administrator name success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_administrator_password(int id, const std::string& target_password) {
    std::cout<<"Trying to administrator modify password ..."<<std::endl;
    std::string sql = "UPDATE administrator SET password = '"+target_password+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify administrator password failed\n");
        std::cout<<"modify administrator password failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify administrator password success"<<std::endl;
    }
    return true;
}

bool AccessDB::reset_administrator_id() {
    std::cout<<"Resetting id ..."<<std::endl;
    std::string sql = "DELETE FROM sqlite_sequence WHERE name = 'administrator';";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "reset administrator id failed\n");
        std::cout<<"reset administrator id failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "reset administrator id success"<<std::endl;
    }
    return true;
}

bool AccessDB::clear_administrator_table() {
    std::cout<<"Clearing administrator table ..."<<std::endl;
    std::string sql = "DELETE FROM administrator;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "clear administrator table failed\n");
        std::cout<<"clear administrator table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "clear administrator table success"<<std::endl;
    }
    return true;
}

// MANIPULATE USER TABLE

bool AccessDB::add_user(const std::string& name, const std::string& password, const std::string& nickname, const std::string& phone_number) {
    std::cout<<"Trying to add user ..."<<std::endl;
    std::string sql = "INSERT INTO user (name, nickname, password, phone_number) VALUES ('"+name+"', '"+nickname+"', '"+password+"', '"+phone_number+"');";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "add user failed\n");
        std::cout<<"add user failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "add user success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_user(const std::string& name) {
    std::cout<<"Trying to delete user ..."<<std::endl;
    std::string sql = "DELETE FROM user WHERE name = '"+name+"';";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete user failed\n");
        std::cout<<"delete user failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete user success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_user(int id) {
    std::cout<<"Trying to delete user ..."<<std::endl;
    std::string sql = "DELETE FROM user WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete user failed\n");
        std::cout<<"delete user failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete user success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_user_name(int id, const std::string& target_name) {
    std::cout<<"Trying to modify user name ..."<<std::endl;
    std::string sql = "UPDATE user SET name = '"+target_name+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify user name failed\n");
        std::cout<<"modify user name failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify user name success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_user_password(int id, const std::string& target_password) {
    std::cout<<"Trying to modify user password ..."<<std::endl;
    std::string sql = "UPDATE user SET password = '"+target_password+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify user password failed\n");
        std::cout<<"modify user password failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify user password success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_user_nickname(int id, const std::string& target_nickname) {
    std::cout<<"Trying to modify user nickname ..."<<std::endl;
    std::string sql = "UPDATE user SET nickname = '"+target_nickname+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify user nickname failed\n");
        std::cout<<"modify user nickname failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify user nickname success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_user_phone_number(int id, const std::string& target_phone_number) {
    std::cout<<"Trying to modify user phone number ..."<<std::endl;
    std::string sql = "UPDATE user SET phone_number = '"+target_phone_number+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify user phone number failed\n");
        std::cout<<"modify user phone number failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify user phone number success"<<std::endl;
    }
    return true;
}

bool AccessDB::reset_user_id() {
    std::cout << "Resetting id ..." << std::endl;

    // First, rename the old table
    std::string renameSql = "ALTER TABLE user RENAME TO old_user;";
    rc = sqlite3_exec(db, renameSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "rename old user table failed\n");
        std::cout << "rename old user table failed" << std::endl;
        return false;
    }

    // Then, create a new table
    std::string createSql = "CREATE TABLE user (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, nickname TEXT NOT NULL, password TEXT NOT NULL, phone_number TEXT NOT NULL);";
    rc = sqlite3_exec(db, createSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "create new user table failed\n");
        std::cout << "create new user table failed" << std::endl;
        return false;
    }

    // Finally, copy the old data to the new table
    std::string copySql = "INSERT INTO user SELECT NULL, name, nickname, password, phone_number FROM old_user;";
    rc = sqlite3_exec(db, copySql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "copy old data to new user table failed\n");
        std::cout << "copy old data to new user table failed" << std::endl;
        return false;
    }

    // And drop the old table
    std::string dropSql = "DROP TABLE old_user;";
    rc = sqlite3_exec(db, dropSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "drop old user table failed\n");
        std::cout << "drop old user table failed" << std::endl;
        return false;
    }

    std::cout << "reset user id success" << std::endl;
    return true;
}

bool AccessDB::clear_user_table() {
    std::cout<<"Clearing user table ..."<<std::endl;
    std::string sql = "DELETE FROM user;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "clear user table failed\n");
        std::cout<<"clear user table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "clear user table success"<<std::endl;
    }
    return true;
}

// MANIPULATE RESERVATION TABLE

bool AccessDB::add_reservation(const std::string& user_name, const duration& dur, const std::string& table_type, int table_id, int deposit) {
    std::cout<<"Trying to add reservation ..."<<std::endl;
    std::string sql = "INSERT INTO reservation (user_name, year, month, day, start_hour, start_minute, end_hour, end_minute, table_type, table_id, deposit) VALUES ('"+user_name+"', "+std::to_string(dur.year)+", "+std::to_string(dur.month)+", "+std::to_string(dur.day)+", "+std::to_string(dur.hour_begin)+", "+std::to_string(dur.minute_begin)+", "+std::to_string(dur.hour_end)+", "+std::to_string(dur.minute_end)+", '"+table_type+"', "+std::to_string(table_id)+", "+std::to_string(deposit)+");";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "add reservation failed\n");
        std::cout<<"add reservation failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "add reservation success"<<std::endl;
    }
    return true;
}

bool AccessDB::add_reservation(const reservation &res) const {
    std::cout<<"Trying to add reservation ..."<<std::endl;
    std::string sql = "INSERT INTO reservation (user_name, year, month, day, start_hour, start_minute, end_hour, end_minute, table_type, table_id, deposit) VALUES ('"+res.user_name+"', "+std::to_string(res.dur.year)+", "+std::to_string(res.dur.month)+", "+std::to_string(res.dur.day)+", "+std::to_string(res.dur.hour_begin)+", "+std::to_string(res.dur.minute_begin)+", "+std::to_string(res.dur.hour_end)+", "+std::to_string(res.dur.minute_end)+", '"+res.table_type+"', "+std::to_string(res.table_id)+", "+std::to_string(res.deposit)+");";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "add reservation failed\n");
        std::cout<<"add reservation failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "add reservation success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_reservation(const std::string& user_name) {
    std::cout<<"Trying to delete reservation ..."<<std::endl;
    std::string sql = "DELETE FROM reservation WHERE user_name = '"+user_name+"';";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete reservation failed\n");
        std::cout<<"delete reservation failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete reservation success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_reservation(int id) {
    std::cout<<"Trying to delete reservation ..."<<std::endl;
    std::string sql = "DELETE FROM reservation WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete reservation failed\n");
        std::cout<<"delete reservation failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete reservation success"<<std::endl;
    }
    return true;
}

bool AccessDB::replace_all_username(const std::string& old_name, const std::string& new_name) {
    std::cout<<"Trying to replace all username ..."<<std::endl;
    std::string sql = "UPDATE reservation SET user_name = '"+new_name+"' WHERE user_name = '"+old_name+"';";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "replace all username failed\n");
        std::cout<<"replace all username failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "replace all username success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_reservation_user_name(int id, const std::string& target_user_name) {
    std::cout<<"Trying to modify reservation user name ..."<<std::endl;
    std::string sql = "UPDATE reservation SET user_name = '"+target_user_name+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify reservation user name failed\n");
        std::cout<<"modify reservation user name failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify reservation user name success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_reservation_duration(int id, const duration& dur) {
    std::cout<<"Trying to modify reservation duration ..."<<std::endl;
    std::string sql = "UPDATE reservation SET year = "+std::to_string(dur.year)+", month = "+std::to_string(dur.month)+", day = "+std::to_string(dur.day)+", start_hour = "+std::to_string(dur.hour_begin)+", start_minute = "+std::to_string(dur.minute_begin)+", end_hour = "+std::to_string(dur.hour_end)+", end_minute = "+std::to_string(dur.minute_end)+" WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify reservation duration failed\n");
        std::cout<<"modify reservation duration failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify reservation duration success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_reservation_table_type(int id, const std::string& target_table_type) {
    std::cout<<"Trying to modify reservation table type ..."<<std::endl;
    std::string sql = "UPDATE reservation SET table_type = '"+target_table_type+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify reservation table type failed\n");
        std::cout<<"modify reservation table type failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify reservation table type success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_reservation_table_id(int id, int target_table_id) {
    std::cout<<"Trying to modify reservation table id ..."<<std::endl;
    std::string sql = "UPDATE reservation SET table_id = "+std::to_string(target_table_id)+" WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify reservation table id failed\n");
        std::cout<<"modify reservation table id failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify reservation table id success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_reservation_deposit(int id, int target_deposit) {
    std::cout<<"Trying to modify reservation deposit ..."<<std::endl;
    std::string sql = "UPDATE reservation SET deposit = "+std::to_string(target_deposit)+" WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify reservation deposit failed\n");
        std::cout<<"modify reservation deposit failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify reservation deposit success"<<std::endl;
    }
    return true;
}

bool AccessDB::reset_reservation_id() {
    std::cout << "Resetting id ..." << std::endl;

    // First, rename the old table
    std::string renameSql = "ALTER TABLE reservation RENAME TO old_reservation;";
    rc = sqlite3_exec(db, renameSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "rename old reservation table failed\n");
        std::cout << "rename old reservation table failed" << std::endl;
        return false;
    }

    // Then, create a new table
    std::string createSql = "CREATE TABLE reservation (id INTEGER PRIMARY KEY AUTOINCREMENT, user_name TEXT NOT NULL,"
                            "year INTEGER NOT NULL, month INTEGER NOT NULL, day INTEGER NOT NULL,"
                            "start_hour INTEGER NOT NULL, start_minute INTEGER NOT NULL,"
                            "end_hour INTEGER NOT NULL, end_minute INTEGER NOT NULL,"
                            " table_type TEXT NOT NULL, table_id INTEGER NOT NULL, deposit INTEGER NOT NULL);";
    rc = sqlite3_exec(db, createSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "create new reservation table failed\n");
        std::cout << "create new reservation table failed" << std::endl;
        return false;
    }

    // Finally, copy the old data to the new table
    std::string copySql = "INSERT INTO reservation SELECT NULL, user_name, year, month, day, start_hour, start_minute, end_hour, end_minute, table_type, table_id, deposit FROM old_reservation;";
    rc = sqlite3_exec(db, copySql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "copy old data to new reservation table failed\n");
        std::cout << "copy old data to new reservation table failed" << std::endl;
        return false;
    }

    // And drop the old table
    std::string dropSql = "DROP TABLE old_reservation;";
    rc = sqlite3_exec(db, dropSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "drop old reservation table failed\n");
        std::cout << "drop old reservation table failed" << std::endl;
        return false;
    }

    std::cout << "reset reservation id success" << std::endl;
    return true;
}

bool AccessDB::clear_reservation_table() {
    std::cout<<"Clearing reservation table ..."<<std::endl;
    std::string sql = "DELETE FROM reservation;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "clear reservation table failed\n");
        std::cout<<"clear reservation table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "clear reservation table success"<<std::endl;
    }
    return true;
}

// MANIPULATE FOOD TABLE

bool AccessDB::add_food(const std::string& name, int price, const std::string& description) {
    std::cout<<"Trying to add food ..."<<std::endl;
    std::string sql = "INSERT INTO food (name, price, description) VALUES ('"+name+"', "+std::to_string(price)+", '"+description+"');";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "add food failed\n");
        std::cout<<"add food failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "add food success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_food(const std::string& name) {
    std::cout<<"Trying to delete food ..."<<std::endl;
    std::string sql = "DELETE FROM food WHERE name = '"+name+"';";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete food failed\n");
        std::cout<<"delete food failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete food success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_food(int id) {
    std::cout<<"Trying to delete food ..."<<std::endl;
    std::string sql = "DELETE FROM food WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete food failed\n");
        std::cout<<"delete food failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete food success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_food_name(int id, const std::string& target_name) {
    std::cout<<"Trying to modify food name ..."<<std::endl;
    std::string sql = "UPDATE food SET name = '"+target_name+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify food name failed\n");
        std::cout<<"modify food name failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify food name success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_food_price(int id, int target_price) {
    std::cout<<"Trying to modify food price ..."<<std::endl;
    std::string sql = "UPDATE food SET price = "+std::to_string(target_price)+" WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify food price failed\n");
        std::cout<<"modify food price failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify food price success"<<std::endl;
    }
    return true;
}

bool AccessDB::modify_food_description(int id, const std::string& target_description) {
    std::cout<<"Trying to modify food description ..."<<std::endl;
    std::string sql = "UPDATE food SET description = '"+target_description+"' WHERE id = "+std::to_string(id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "modify food description failed\n");
        std::cout<<"modify food description failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "modify food description success"<<std::endl;
    }
    return true;
}

bool AccessDB::reset_food_id() {
    std::cout << "Resetting id ..." << std::endl;

    // First, rename the old table
    std::string renameSql = "ALTER TABLE food RENAME TO old_food;";
    rc = sqlite3_exec(db, renameSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "rename old food table failed\n");
        std::cout << "rename old food table failed" << std::endl;
        return false;
    }

    // Then, create a new table
    std::string createSql = "CREATE TABLE food (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, price INTEGER NOT NULL, description TEXT NOT NULL);";
    rc = sqlite3_exec(db, createSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "create new food table failed\n");
        std::cout << "create new food table failed" << std::endl;
        return false;
    }

    // Finally, copy the old data to the new table
    std::string copySql = "INSERT INTO food SELECT NULL, name, price, description FROM old_food;";
    rc = sqlite3_exec(db, copySql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "copy old data to new food table failed\n");
        std::cout << "copy old data to new food table failed" << std::endl;
        return false;
    }

    // And drop the old table
    std::string dropSql = "DROP TABLE old_food;";
    rc = sqlite3_exec(db, dropSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "drop old food table failed\n");
        std::cout << "drop old food table failed" << std::endl;
        return false;
    }

    std::cout << "reset food id success" << std::endl;
    return true;
}

bool AccessDB::clear_food_table() {
    std::cout<<"Clearing food table ..."<<std::endl;
    std::string sql = "DELETE FROM food;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "clear food table failed\n");
        std::cout<<"clear food table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "clear food table success"<<std::endl;
    }
    return true;
}

// MANIPULATE PAIR TABLE

bool AccessDB::add_pair(int reservation_id, int food_id) {
    std::cout<<"Trying to add pair ..."<<std::endl;
    std::string sql = "INSERT INTO pair (reservation_id, food_id) VALUES ("+std::to_string(reservation_id)+", "+std::to_string(food_id)+");";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "add pair failed\n");
        std::cout<<"add pair failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "add pair success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_pair(int reservation_id, int food_id) {
    std::cout<<"Trying to delete pair ..."<<std::endl;
    std::string sql = "DELETE FROM pair WHERE reservation_id = "+std::to_string(reservation_id)+" AND food_id = "+std::to_string(food_id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete pair failed\n");
        std::cout<<"delete pair failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete pair success"<<std::endl;
    }
    return true;
}

bool AccessDB::delete_pair(int reservation_id) {
    std::cout<<"Trying to delete pair ..."<<std::endl;
    std::string sql = "DELETE FROM pair WHERE reservation_id = "+std::to_string(reservation_id)+";";
    int rc_local = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc_local == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "delete pair failed\n");
        std::cout<<"delete pair failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "delete pair success"<<std::endl;
    }
    return true;
}

bool AccessDB::reset_pair_id() {
    std::cout << "Resetting id ..." << std::endl;

    // First, rename the old table
    std::string renameSql = "ALTER TABLE pair RENAME TO old_pair;";
    rc = sqlite3_exec(db, renameSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "rename old pair table failed\n");
        std::cout << "rename old pair table failed" << std::endl;
        return false;
    }

    // Then, create a new table
    std::string createSql = "CREATE TABLE pair (reservation_id INTEGER NOT NULL, food_id INTEGER NOT NULL);";
    rc = sqlite3_exec(db, createSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "create new pair table failed\n");
        std::cout << "create new pair table failed" << std::endl;
        return false;
    }

    // Finally, copy the old data to the new table
    std::string copySql = "INSERT INTO pair SELECT reservation_id, food_id FROM old_pair;";
    rc = sqlite3_exec(db, copySql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "copy old data to new pair table failed\n");
        std::cout << "copy old data to new pair table failed" << std::endl;
        return false;
    }

    // And drop the old table
    std::string dropSql = "DROP TABLE old_pair;";
    rc = sqlite3_exec(db, dropSql.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "drop old pair table failed\n");
        std::cout << "drop old pair table failed" << std::endl;
        return false;
    }

    std::cout << "reset pair id success" << std::endl;
    return true;
}

bool AccessDB::clear_pair_table() {
    std::cout<<"Clearing pair table ..."<<std::endl;
    std::string sql = "DELETE FROM pair;";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if (rc == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "clear pair table failed\n");
        std::cout<<"clear pair table failed"<<std::endl;
        return false;
    }
    else
    {
        std::cout << "clear pair table success"<<std::endl;
    }
    return true;
}

// ACQUIRE INFORMATION

bool AccessDB::check_exist(int id, const std::string& table) const {
    std::string sql = "SELECT * FROM "+table+" WHERE id = "+std::to_string(id)+";";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK)
    {
        sqlite3_log(sqlite3_errcode(db), "check exist failed\n");
        std::cout<<"check exist failed"<<std::endl;
        return false;
    }
    sign = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (sign == SQLITE_ROW)
    {
        std::cout << "check exist success"<<std::endl;
        return true;
    }
    return false;
}

bool AccessDB::check_exist(const std::string& name, const std::string& table) const {
    std::string sql = "SELECT * FROM "+table+" WHERE name = '"+name+"';";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK)
    {
        sqlite3_log(sqlite3_errcode(db), "check exist failed\n");
        std::cout<<"check exist failed"<<std::endl;
        return false;
    }
    sign = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (sign == SQLITE_ROW)
    {
        std::cout << "check exist success"<<std::endl;
        return true;
    }
    return false;
}

user AccessDB::get_user_info(int id) const {
    std::string sql = "SELECT * FROM user WHERE id = "+std::to_string(id)+";";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "get user info failed\n");
        std::cout<<"get user info failed"<<std::endl;
    }
    else
    {
        std::cout << "get user info success"<<std::endl;
    }
    user u;
    u.id = sqlite3_column_int(stmt, 0);
    u.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    u.nickname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    u.password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    u.phone_number = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    return u;
}

user AccessDB::get_user_info(const std::string& name) const {
    std::string sql = "SELECT * FROM user WHERE name = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "Failed to prepare SQL statement\n");
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_log(sqlite3_errcode(db), "Failed to execute SQL statement\n");
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Retrieve the data
    user u;
    u.id = sqlite3_column_int(stmt, 0);
    u.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    u.nickname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    u.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    u.phone_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return u;
}

admin AccessDB::get_administrator_info(int id) const {
    std::string sql = "SELECT * FROM administrator WHERE id = "+std::to_string(id)+";";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "get admin info failed\n");
        std::cout<<"get admin info failed"<<std::endl;
    }
    else
    {
        std::cout << "get admin info success"<<std::endl;
    }
    admin a;
    a.id = sqlite3_column_int(stmt, 0);
    a.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    a.password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    return a;
}

admin AccessDB::get_administrator_info(const std::string &name) const {
    std::string sql = "SELECT * FROM administrator WHERE name = '"+name+"';";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "get admin info failed\n");
        std::cout<<"get admin info failed"<<std::endl;
    }
    else
    {
        std::cout << "get admin info success"<<std::endl;
    }
    admin a;
    a.id = sqlite3_column_int(stmt, 0);
    a.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    a.password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    return a;
}

reservation AccessDB::get_reservation_info(int id) const {
    std::string sql = "SELECT * FROM reservation WHERE id = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "Failed to prepare SQL statement\n");
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the parameters
    sqlite3_bind_int(stmt, 1, id);

    // Execute the SQL statement
    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_log(sqlite3_errcode(db), "Failed to execute SQL statement\n");
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Retrieve the data
    reservation r;
    r.id = sqlite3_column_int(stmt, 0);
    r.user_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    r.dur.year = sqlite3_column_int(stmt, 2);
    r.dur.month = sqlite3_column_int(stmt, 3);
    r.dur.day = sqlite3_column_int(stmt, 4);
    r.dur.hour_begin = sqlite3_column_int(stmt, 5);
    r.dur.minute_begin = sqlite3_column_int(stmt, 6);
    r.dur.hour_end = sqlite3_column_int(stmt, 7);
    r.dur.minute_end = sqlite3_column_int(stmt, 8);
    r.table_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
    r.table_id = sqlite3_column_int(stmt, 10);
    r.deposit = sqlite3_column_int(stmt, 11);

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return r;
}

reservation AccessDB::get_reservation_info(const std::string& user_name) const {
    std::string sql = "SELECT * FROM reservation WHERE user_name = '"+user_name+"';";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "get reservation info failed\n");
        std::cout<<"get reservation info failed"<<std::endl;
    }
    else
    {
        std::cout << "get reservation info success"<<std::endl;
    }
    reservation r;
    r.id = sqlite3_column_int(stmt, 0);
    r.user_name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    r.dur.year = sqlite3_column_int(stmt, 2);
    r.dur.month = sqlite3_column_int(stmt, 3);
    r.dur.day = sqlite3_column_int(stmt, 4);
    r.dur.hour_begin = sqlite3_column_int(stmt, 5);
    r.dur.minute_begin = sqlite3_column_int(stmt, 6);
    r.dur.hour_end = sqlite3_column_int(stmt, 7);
    r.dur.minute_end = sqlite3_column_int(stmt, 8);
    r.table_type = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
    r.table_id = sqlite3_column_int(stmt, 10);
    r.deposit = sqlite3_column_int(stmt, 11);
    return r;
}

food AccessDB::get_food_info(int id) const {
    std::string sql = "SELECT * FROM food WHERE id = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "Failed to prepare SQL statement\n");
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the parameters
    sqlite3_bind_int(stmt, 1, id);

    // Execute the SQL statement
    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_log(sqlite3_errcode(db), "Failed to execute SQL statement\n");
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Retrieve the data
    food f;
    f.id = sqlite3_column_int(stmt, 0);
    f.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    f.price = sqlite3_column_int(stmt, 2);
    f.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return f;
}

food AccessDB::get_food_info(const std::string &name) const {
    std::string sql = "SELECT * FROM food WHERE name = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "Failed to prepare SQL statement\n");
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_log(sqlite3_errcode(db), "Failed to execute SQL statement\n");
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Retrieve the data
    food f;
    f.id = sqlite3_column_int(stmt, 0);
    f.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    f.price = sqlite3_column_int(stmt, 2);
    f.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return f;
}

pair AccessDB::get_pair_info(int id) const {
    std::string sql = "SELECT * FROM pair WHERE id = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "Failed to prepare SQL statement\n");
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the parameters
    sqlite3_bind_int(stmt, 1, id);

    // Execute the SQL statement
    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_log(sqlite3_errcode(db), "Failed to execute SQL statement\n");
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Retrieve the data
    pair p;
    p.id = sqlite3_column_int(stmt, 0);
    p.reservation_id = sqlite3_column_int(stmt, 1);
    p.food_id = sqlite3_column_int(stmt, 2);

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return p;
}

pair AccessDB::get_pair_info(int reservation_id, int food_id) const {
    std::string sql = "SELECT * FROM pair WHERE reservation_id = ? AND food_id = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "Failed to prepare SQL statement\n");
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the parameters
    sqlite3_bind_int(stmt, 1, reservation_id);
    sqlite3_bind_int(stmt, 2, food_id);

    // Execute the SQL statement
    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_log(sqlite3_errcode(db), "Failed to execute SQL statement\n");
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Retrieve the data
    pair p;
    p.id = sqlite3_column_int(stmt, 0);
    p.reservation_id = sqlite3_column_int(stmt, 1);
    p.food_id = sqlite3_column_int(stmt, 2);

    // Finalize the SQL statement
    sqlite3_finalize(stmt);

    return p;
}

int AccessDB::get_table_length(const std::string& table) const {
    std::string sql = "SELECT COUNT(*) FROM "+table+";";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "get table length failed\n");
        std::cout<<"get table length failed"<<std::endl;
    }
    else
    {
        std::cout << "get table length success"<<std::endl;
    }
    sign = sqlite3_step(stmt);
    int length = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return length;
}

reservation AccessDB::getReservationInfo(int index) const {
    std::string sqlQuery = "SELECT * FROM reservation LIMIT 1 OFFSET " + std::to_string(index) + ";";
    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to retrieve reservation info" << std::endl;
        throw std::runtime_error("Failed to retrieve reservation info");
    }

    reservation res;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        res.id = sqlite3_column_int(statement, 0);
        res.user_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        res.dur.year = sqlite3_column_int(statement, 2);
        res.dur.month = sqlite3_column_int(statement, 3);
        res.dur.day = sqlite3_column_int(statement, 4);
        res.dur.hour_begin = sqlite3_column_int(statement, 5);
        res.dur.minute_begin = sqlite3_column_int(statement, 6);
        res.dur.hour_end = sqlite3_column_int(statement, 7);
        res.dur.minute_end = sqlite3_column_int(statement, 8);
        res.table_type = reinterpret_cast<const char*>(sqlite3_column_text(statement, 9));
        res.table_id = sqlite3_column_int(statement, 10);
        res.deposit = sqlite3_column_int(statement, 11);
    }

    sqlite3_finalize(statement);
    return res;
}

user AccessDB::getUserInfo(int index) const {
    std::string sqlQuery = "SELECT * FROM user LIMIT 1 OFFSET " + std::to_string(index) + ";";
    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to retrieve user info" << std::endl;
        throw std::runtime_error("Failed to retrieve user info");
    }

    user u;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        u.id = sqlite3_column_int(statement, 0);
        u.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        u.nickname = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
        u.password = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
        u.phone_number = reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
    }

    sqlite3_finalize(statement);
    return u;
}

food AccessDB::getFoodInfo(int index) const {
    std::string sqlQuery = "SELECT * FROM food LIMIT 1 OFFSET " + std::to_string(index) + ";";
    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to retrieve food info" << std::endl;
        throw std::runtime_error("Failed to retrieve food info");
    }

    food f;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        f.id = sqlite3_column_int(statement, 0);
        f.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        f.price = sqlite3_column_int(statement, 2);
        f.description = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
    }

    sqlite3_finalize(statement);
    return f;
}

pair AccessDB::getPairInfo(int index) const {
    std::string sqlQuery = "SELECT * FROM pair LIMIT 1 OFFSET " + std::to_string(index) + ";";
    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to retrieve pair info" << std::endl;
        throw std::runtime_error("Failed to retrieve pair info");
    }

    pair p;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        p.id = sqlite3_column_int(statement, 0);
        p.reservation_id = sqlite3_column_int(statement, 1);
        p.food_id = sqlite3_column_int(statement, 2);
    }

    sqlite3_finalize(statement);
    return p;
}

// VERIFY PASSWORD

bool AccessDB::verify_password(const std::string& name, const std::string& password, const std::string& table) const {
    std::string sql = "SELECT password FROM " + table + " WHERE name = ?;";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "verify password failed\n");
        std::cout << "verify password failed" << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    std::string retrieved_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);

    return password == retrieved_password;
}

bool AccessDB::verify_password(int id, const std::string& password, const std::string& table) const {
    std::string sql = "SELECT password FROM " + table + " WHERE id = ?;";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "verify password failed\n");
        std::cout << "verify password failed" << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    std::string retrieved_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);

    return password == retrieved_password;
}

bool AccessDB::verify_password_phone(const std::string &phone_number, const std::string &password) const {
    std::string sql = "SELECT password FROM user WHERE phone_number = ?;";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign != SQLITE_OK) {
        sqlite3_log(sqlite3_errcode(db), "verify password failed\n");
        std::cout << "verify password failed" << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, phone_number.c_str(), -1, SQLITE_STATIC);

    sign = sqlite3_step(stmt);
    if (sign != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    std::string retrieved_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);

    return password == retrieved_password;
}

// PRINT INFORMATION

void AccessDB::print_all(const std::string& table) const // Print different tables.
{
    std::string sql = "SELECT * FROM "+table+";";
    sqlite3_stmt* stmt;
    int sign = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (sign == SQLITE_ERROR)
    {
        sqlite3_log(sqlite3_errcode(db), "failed to fetch data\n");
        std::cout<<"print all: failed to fetch data from "<<table<<std::endl;
    }
    else
    {
        std::cout << "print all: succeeded to fetch data from "<<table<<std::endl;
    }
    if (table == "administrator")
    {
        std::cout<<"administrator table:"<<std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout<<"id: "<<sqlite3_column_int(stmt, 0)<<std::endl;
            std::cout<<"name: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))<<std::endl;
            std::cout<<"password: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)))<<std::endl;
        }
    }
    else if (table == "user")
    {
        std::cout<<"user table:"<<std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout<<"id: "<<sqlite3_column_int(stmt, 0)<<std::endl;
            std::cout<<"name: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))<<std::endl;
            std::cout<<"nickname: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)))<<std::endl;
            std::cout<<"password: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)))<<std::endl;
            std::cout<<"phone number: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)))<<std::endl;
        }
    }
    else if (table == "reservation")
    {
        std::cout<<"reservation table:"<<std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout<<"id: "<<sqlite3_column_int(stmt, 0)<<std::endl;
            std::cout<<"user name: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))<<std::endl;
            std::cout<<"year: "<<sqlite3_column_int(stmt, 2)<<std::endl;
            std::cout<<"month: "<<sqlite3_column_int(stmt, 3)<<std::endl;
            std::cout<<"day: "<<sqlite3_column_int(stmt, 4)<<std::endl;
            std::cout<<"start hour: "<<sqlite3_column_int(stmt, 5)<<std::endl;
            std::cout<<"start minute: "<<sqlite3_column_int(stmt, 6)<<std::endl;
            std::cout<<"end hour: "<<sqlite3_column_int(stmt, 7)<<std::endl;
            std::cout<<"end minute: "<<sqlite3_column_int(stmt, 8)<<std::endl;
        }
    }
    else if (table == "food")
    {
        std::cout<<"food table:"<<std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout<<"id: "<<sqlite3_column_int(stmt, 0)<<std::endl;
            std::cout<<"name: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))<<std::endl;
            std::cout<<"price: "<<sqlite3_column_int(stmt, 2)<<std::endl;
            std::cout<<"description: "<<std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)))<<std::endl;
        }
    }
    else if (table == "pair")
    {
        std::cout<<"pair table:"<<std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout<<"id: "<<sqlite3_column_int(stmt, 0)<<std::endl;
            std::cout<<"reservation id: "<<sqlite3_column_int(stmt, 1)<<std::endl;
            std::cout<<"food id: "<<sqlite3_column_int(stmt, 2)<<std::endl;
        }
    }
}

void AccessDB::print_all() const // Print all tables.
{
    print_all("administrator");
    print_all("user");
    print_all("reservation");
    print_all("food");
    print_all("pair");
}
