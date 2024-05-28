#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "AccessDB.h"

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

    void set_current_user(const std::string username);
    void set_profile();
    void refresh_time();
    void get_reservation_list();
    void get_reserve_list();
    void set_theme(const std::string s);
    void set_all_button_stylesheet(const QString& stylesheet);
    void set_all_table_stylesheet(const QString& stylesheet);
    void set_all_label_stylesheet(const QString& stylesheet);
    void show_password_edit(bool state);

private slots:
    void on_quitButton_clicked();

    void on_deleteButton_clicked();

    void on_reserveButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_theme_selectBox_currentIndexChanged(int index);

    void on_password_modifyButton_clicked();

    void on_password_changeButton_clicked();

    void on_username_changeButton_clicked();

    void on_nickname_changeButton_clicked();

    void on_phone_changeButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer(this);

    AccessDB db;
    std::string current_user;
};
#endif // MAINWINDOW_H
