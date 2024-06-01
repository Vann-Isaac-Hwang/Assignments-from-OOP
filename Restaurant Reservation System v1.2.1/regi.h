#ifndef REGI_H
#define REGI_H

#include <QWidget>
#include <QMouseEvent>

#include "AccessDB.h"

#define PHONE_NUMBER_LENGTH 11

namespace Ui {
class regi;
}

class regi : public QWidget
{
    Q_OBJECT

public:
    explicit regi(QWidget *parent = nullptr);
    ~regi();

    void set_theme(const std::string& s);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_cancelButton_clicked();
    void on_confirmButton_clicked();

private:
    Ui::regi *ui;
    AccessDB db;

    QPoint mousePoint;
    bool mouse_press;
};

#endif // REGI_H
