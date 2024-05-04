#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindlg.h"
#include <QTimer>
#include "Course.h"
#include "Student.h"
#include <vector>

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

    friend Logindlg;
private slots:
    void on_loginButton_clicked();//

    void on_quitButton_clicked();

    void on_taddButton_clicked();

    void updateUI();

    void update_credit_LCD();

    void update_stu_num();

    void LeftRefresh();

    void get_course_list();

    void get_student_list();

    int add_Course(Student &s, Course &c);

    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;
    Logindlg d;
    QTimer *timer = new QTimer(this);
    std::vector<Course> course_list;
    std::vector<Student> student_list;
};
#endif // MAINWINDOW_H
