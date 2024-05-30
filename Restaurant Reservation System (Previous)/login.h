#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMouseEvent>
#include "AccessDB.h"
#include "mainwindow.h"
#include "mainwindowadmin.h"
#include "regi.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void set_theme(const std::string s);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:

    void on_sign_upButton_clicked();

    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

    void on_theme_selectBox_currentIndexChanged(int index);

private:
    Ui::login *ui;

    regi r;
    std::string theme_name;

    MainWindow *w = nullptr;
    MainWindowAdmin *wa = nullptr;

    AccessDB db;

    QPoint mousePoint;
    bool mouse_press;

};

#endif // LOGIN_H
