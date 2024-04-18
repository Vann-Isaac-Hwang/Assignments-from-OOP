#include <QWidget>
#include <QTimer>
#include "Elevator.h"
#include <iostream>
#include <thread>
#include <ctime>
#include <cstring>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Refresh();
    void TimeShow();
    void updateUI();
    void let_go();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

    void cancelButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    Elevator ele;
    QTimer *timer = new QTimer(this);
    time_t timenow;

    QPoint mousePoint;
    bool mouse_press;
};
