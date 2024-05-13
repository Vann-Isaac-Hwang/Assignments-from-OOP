#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    int take_sign();
    void set_sen(std::string str);
    void show_text();

private slots:
    void on_cancelButton_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();

private:
    Ui::Form *ui;
    int sign=0;
    std::string sen;
};

#endif // FORM_H
