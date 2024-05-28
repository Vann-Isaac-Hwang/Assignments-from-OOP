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

    void set_current_user(const std::string& username);
    void refresh_time();
    void get_reservation_list();
    void get_user_list();
    void set_default_date_edit();
    void log(const std::string& s);
    void log();
    void set_theme(const std::string s);
    void set_all_button_stylesheet(const QString& stylesheet);
    void set_all_table_stylesheet(const QString& stylesheet);

private slots:
    void on_deleteButton_clicked();

    void on_addButton_clicked();

    void on_quitButton_clicked();

    void on_user_deleteButton_clicked();

    void on_reservation_id_resetButton_clicked();

    void on_user_id_resetButton_clicked();

    void on_administrator_id_resetButton_clicked();

    void on_reservation_table_clearButton_clicked();

    void on_user_table_clearButton_clicked();

    void on_administrator_table_clearButton_clicked();

    void on_reservation_table_createButton_clicked();

    void on_user_table_createButton_clicked();

    void on_administrator_table_createButton_clicked();

    void on_theme_selectBox_currentIndexChanged(int index);

private:
    Ui::MainWindowAdmin *ui;
    QTimer *timer = new QTimer(this);

    AccessDB db;
    std::fstream log_file;
    std::string current_user;
};

#endif // MAINWINDOWADMIN_H
