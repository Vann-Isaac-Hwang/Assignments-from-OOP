#ifndef MENU_H
#define MENU_H

#define DEPOSIT_RATE 0.3

#include <QWidget>
#include "AccessDB.h"

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

    void set_reservation_id(int reservation_id);

    void get_food_list();
    void get_this_food_list();

    void set_theme(const std::string& s);
    void set_all_button_stylesheet(const QString& stylesheet);
    void set_all_table_stylesheet(const QString& stylesheet);
    void set_all_label_stylesheet(const QString& stylesheet);

private slots:
    void on_doneButton_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::menu *ui;
    AccessDB db;
    int reservation_id;
};

#endif // MENU_H
