#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <ctime>
#include <QMouseEvent>
#include "elevatoradvanced.h"
#include "form.h"

#define RRFRESHING_INTERVAL_TIME 500

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

    void updateUI();
    void Refresh();
    void let_go();
    void TimeShow();

    void func();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void cancelButton_clicked();
    //Buttons to active different floors
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

    void form_1_triggered();
    void form_2_triggered();
    void form_3_triggered();
    void form_4_triggered();
    void form_5_triggered();
    void form_6_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer(this);
    time_t timenow;

    Form form[6];

    ElevatorAdvanced ele;

    QPoint mousePoint;
    bool mouse_press;
};
#endif // MAINWINDOW_H
