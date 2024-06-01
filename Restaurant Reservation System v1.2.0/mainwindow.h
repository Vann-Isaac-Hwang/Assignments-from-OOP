#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "AccessDB.h"
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Assign value to variable current_user when logging in
    void set_current_user(const std::string username);

    // Refresh time label
    void refresh_time();

    // Acquire data
    void get_reservation_list();
    void get_reserve_list();

    // Functions for profile page
    void set_profile();
    void show_password_edit(bool state);

    // Beautify
    void set_theme(const std::string& s);
    void set_all_button_stylesheet(const QString& stylesheet);
    void set_side_button_stylesheet(const QString& stylesheet);
    void set_all_table_stylesheet(const QString& stylesheet);
    void set_all_label_stylesheet(const QString& stylesheet);

private slots:
    // Global
    void on_quitButton_clicked();

    // My reservation
    void on_deleteButton_clicked();
    void on_menuButton_clicked();

    // Reserve
    void on_reserveButton_clicked();

    // My profile
    void on_username_changeButton_clicked();
    void on_nickname_changeButton_clicked();
    void on_phone_changeButton_clicked();
    void on_password_changeButton_clicked();
    void on_password_modifyButton_clicked();

    // Table widget
    void on_my_reservation_tabButton_clicked();
    void on_reserve_tabButton_clicked();
    void on_my_profile_tabButton_clicked();
    void on_settings_tabButton_clicked();

    // ELSE
    void on_tabWidget_tabBarClicked(int index);
    void on_theme_selectBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    menu food_menu;

    QTimer *timer = new QTimer(this);

    AccessDB db;
    std::string current_user;
};
#endif // MAINWINDOW_H
