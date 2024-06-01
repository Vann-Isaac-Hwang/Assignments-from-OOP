#ifndef MAINWINDOWADMIN_H
#define MAINWINDOWADMIN_H

#include <QMainWindow>
#include <QTimer>
#include <fstream>
#include "AccessDB.h"
#include "log2txt.h"

namespace Ui {
class MainWindowAdmin;
}

class MainWindowAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowAdmin(QWidget *parent = nullptr);
    ~MainWindowAdmin();

    // Assign value to variable current_user when logging in
    void set_current_user(const std::string& username);

    // Refresh time label
    void refresh_time();

    // Acquire data
    void get_reservation_list();
    void get_food_reservation_list();
    void get_food_list();
    void get_user_list();

    // Set the initial value of date editor
    void set_default_date_edit();

    // Beautify
    void set_theme(const std::string s);
    void set_all_button_stylesheet(const QString& stylesheet);
    void set_all_table_stylesheet(const QString& stylesheet);

    // Write log to page Log and file log.txt
    void log(const std::string& s);
    void log();

private slots:
    // Global
    void on_quitButton_clicked();

    // Reservation
    void on_deleteButton_clicked();
    void on_addButton_clicked();

    // Food reservation
    void on_pair_deleteButton_clicked();

    // Food
    void on_food_deleteButton_clicked();
    void on_food_addButton_clicked();

    // User
    void on_user_deleteButton_clicked();

    // Other
    void on_reservation_id_resetButton_clicked();
    void on_reservation_table_clearButton_clicked();
    void on_reservation_table_createButton_clicked();

    void on_user_id_resetButton_clicked();
    void on_user_table_clearButton_clicked();
    void on_user_table_createButton_clicked();

    void on_administrator_id_resetButton_clicked();
    void on_administrator_table_clearButton_clicked();
    void on_administrator_table_createButton_clicked();

    void on_food_id_resetButton_clicked();
    void on_food_table_clearButton_clicked();
    void on_food_table_createButton_clicked();

    void on_pair_id_resetButton_clicked();
    void on_pair_table_clearButton_clicked();
    void on_pair_table_createButton_clicked();

    // ELSE
    void on_theme_selectBox_currentIndexChanged(int index);
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindowAdmin *ui;
    QTimer *timer = new QTimer(this);

    AccessDB db;
    std::fstream log_file;
    std::string current_user;
};

#endif // MAINWINDOWADMIN_H
