#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class Logindlg;
}

class Logindlg : public QDialog
{
    Q_OBJECT

public:
    explicit Logindlg(QWidget *parent = nullptr);
    ~Logindlg();
    int get_logged_flag();
    std::string get_logged_user();
    int get_logged_user_id();
    int get_sign();
    void set_sign();
private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Logindlg *ui;
    std::string logged_user;
    int logged_user_id;
    int logged_flag=0;
    int sign=0;
};

#endif // LOGINDLG_H
