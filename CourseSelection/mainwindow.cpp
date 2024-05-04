#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QProcess>
#include <QListWidget>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <QFile>

//#define COURSE_DATA_LOCATION "CourseData.txt"
//#define STUDENT_DATA_LOCATION "StudentData.txt"

#define RRFRESHING_INTERVAL_TIME 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_taddButton_clicked);

    ui->coursetable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->coursetable->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->coursetable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->mycoursetable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mycoursetable->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->mycoursetable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->coursetable->setShowGrid(true);
    //QFont Font = ui->coursetable->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->coursetable->horizontalHeader()->setDefaultSectionSize(80);
    ui->coursetable->setColumnWidth(0,120);
    ui->coursetable->setColumnWidth(1,60);
    ui->coursetable->setColumnWidth(2,80);
    ui->coursetable->setColumnWidth(3,60);
    ui->coursetable->setColumnWidth(4,60);

    ui->mycoursetable->setColumnWidth(0,140);
    ui->mycoursetable->setColumnWidth(1,60);
    ui->mycoursetable->setColumnWidth(2,80);

    get_course_list();
    get_student_list();

    //Set up the timer for refreshing
    timer->setInterval(RRFRESHING_INTERVAL_TIME);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateUI);
    timer->start();
}

void MainWindow::on_loginButton_clicked()
{
    d.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

void MainWindow::updateUI()
{
    if (d.get_logged_flag()==1) {ui->loginlabel->setText(QString::fromStdString(d.get_logged_user()));}
    else {ui->loginlabel->setText("Please login");}
    if (d.get_logged_flag()==1)
        ui->belowloginlabel->setText("");
    if (d.get_sign()==1)
    {
        LeftRefresh();
        d.set_sign();
        update_credit_LCD();
    }
    /*/
    std::vector<Course>::iterator it;
    std::cout<<"so:";
    for (it=course_list.begin();it!=course_list.end();it++)
    {
        std::cout<<it->get_stu_num();
    }std::cout<<std::endl;/*/
}

void MainWindow::update_credit_LCD()
{
    int total_credit_hour=0;
    for (int i=0;i<ui->mycoursetable->rowCount();i++)
    {
        total_credit_hour+=ui->mycoursetable->item(i,2)->text().toInt();
    }
    ui->creditlcdNumber->setDigitCount(3);
    ui->creditlcdNumber->display(total_credit_hour);
}

void MainWindow::get_course_list()
{
    std::cout<<"\nFetching course_list"<<std::endl;
    std::ifstream infile;
    infile.open("CourseData.txt",std::ios::in);
    if (!infile.is_open())
    {
        std::cout<<"cannot open the CourseData file"<<std::endl;
    }
    std::string buf;
    char name[64];
    int id, cre_hour, vn, vm;
    int i, pn;
    while (getline(infile,buf))
    {
        i=0, pn=0, id=0, cre_hour=0, vn=0, vm=0;
        while (buf[i]!=' ')
        {
            name[pn++]=buf[i];
            i++;
        }
        name[pn]='\0';
        i++;

        while (buf[i]!=' ')
        {
            id*=10;
            id+=buf[i]-'0';
            i++;
        }
        i++;

        while (buf[i]!=' ')
        {
            cre_hour*=10;
            cre_hour+=buf[i]-'0';
            i++;
        }
        i++;

        while (buf[i]!=' ')
        {
            vn*=10;
            vn+=buf[i]-'0';
            i++;
        }
        i++;

        while (buf[i]!=' '&&buf[i]!='\n'&&buf[i]!='\0')
        {
            vm*=10;
            vm+=buf[i]-'0';
            i++;
        }
        i++;

        std::string a=name;

        Course pco(a,id,cre_hour,vm);
        course_list.push_back(pco);
        std::cout<<"Course "<<"\""<<a<<"\""<<" added"<<std::endl;
    }
    infile.close();
    i=0;
    for (std::vector<Course>::iterator it=course_list.begin();it!=course_list.end();it++)
    {
        //插入数据
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(i));
        check->setCheckState(Qt::Unchecked);  //是否设置选中框
        ui->coursetable->insertRow(i);
        check->setText(QString::number(i));  //显示序号
        //ui->coursetable->setItem(i,0,check); //插入复选框
        ui->coursetable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(course_list[i].get_name())));
        ui->coursetable->setItem(i,1,new QTableWidgetItem(QString::number(course_list[i].get_id())));
        ui->coursetable->setItem(i,2,new QTableWidgetItem(QString::number(course_list[i].get_credit_hour())));
        ui->coursetable->setItem(i,3,new QTableWidgetItem(QString::number(course_list[i].get_stu_num())));
        ui->coursetable->setItem(i,4,new QTableWidgetItem(QString::number(course_list[i].get_volumn())));
        i++;
    }
    std::cout<<std::endl;
}

void MainWindow::get_student_list()
{
    std::cout<<"\nFetching student_list"<<std::endl;
    std::ifstream infile;
    infile.open("StudentData.txt",std::ios::in);
    if (!infile.is_open())
    {
        std::cout<<"cannot open the StudentData file"<<std::endl;
    }
    std::string buf;
    char name[64], pw[64];
    int id, pp;
    int i, pn;
    while (getline(infile,buf))
    {
        i=0, pn=0, id=0, pp=0;
        while (buf[i]!=' ')
        {
            name[pn++]=buf[i];
            i++;
        }
        name[pn]='\0';
        i++;

        while (buf[i]!=' ')
        {
            id*=10;
            id+=buf[i]-'0';
            i++;
        }
        i++;

        while (buf[i]!=' '&&buf[i]!='\n'&&buf[i]!='\0')
        {
            pw[pp++]=buf[i];
            i++;
        }
        pw[pp]='\0';
        i++;

        std::string a=name;

        Student pst(a,id,pw);
        student_list.push_back(pst);
        std::cout<<"Student "<<"\""<<a<<"\""<<" added"<<std::endl;
    }
    infile.close();
    std::cout<<std::endl;
}

void MainWindow::on_taddButton_clicked()
{
    if (d.get_logged_flag()==0)
    {
        std::cout<<"Please login first!"<<std::endl;
        ui->belowloginlabel->setText("Please login first!");
        return;
    }
    std::cout<<"Add Course"<<std::endl;
    QModelIndex cur = ui->coursetable->selectionModel()->currentIndex();
    int row = cur.row();
    std::cout<<"Row "<<row<<std::endl;
    if (add_Course(student_list[d.get_logged_user_id()-1],course_list[row]))
    {
        course_list[row].stu_plus();
        update_stu_num();
    }
}

void MainWindow::LeftRefresh()
{
    Student &ps = student_list[d.get_logged_user_id()-1];
    //Clear
    //QModelIndex cur = ui->mycoursetable->selectionModel()->currentIndex();
    //int row = cur.row();
    std::cout<<"Starting to clear "<<ui->mycoursetable->rowCount()<<" rows in mycoursetable."<<std::endl;
    for (int i=ui->mycoursetable->rowCount()-1;i>=0;i--)//Notice: When the first row is deleted, the second row will replace it.
    {
        ui->mycoursetable->removeRow(i);
    }
    //Add
    int cid;
    for (int i=0;i<ps.get_cll();i++)
    {
        cid=ps.get_course_id(i);
        //Add courses to mylist according to cid(course id).
        //if (ps.check_course_in(cid)) continue;
        std::vector<Course>::iterator it;
        for (it=course_list.begin();it!=course_list.end();it++)
        {
            if (it->get_id()==cid) break;
        }

        QTableWidgetItem *check=new QTableWidgetItem(QString::number(i));
        //check->setCheckState(Qt::Unchecked);  //是否设置选中框
        ui->mycoursetable->insertRow(i);
        check->setText(QString::number(i));  //显示序号
        //ui->coursetable->setItem(s.get_cll(),0,check); //插入复选框
        ui->mycoursetable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(it->get_name())));
        ui->mycoursetable->setItem(i,1,new QTableWidgetItem(QString::number(it->get_id())));
        ui->mycoursetable->setItem(i,2,new QTableWidgetItem(QString::number(it->get_credit_hour())));
    }
}

int MainWindow::add_Course(Student &s, Course &c)
{
    if (s.check_course_in(c.get_id())==1)
    {
        std::cout<<"The course is already existed!"<<std::endl;
        return 0;
    }
    QTableWidgetItem *check=new QTableWidgetItem(QString::number(s.get_cll()));
    //check->setCheckState(Qt::Unchecked);  //是否设置选中框
    ui->mycoursetable->insertRow(s.get_cll());
    Sleep(100);
    check->setText(QString::number(s.get_cll()));  //显示序号
    //ui->coursetable->setItem(s.get_cll(),0,check); //插入复选框
    ui->mycoursetable->setItem(s.get_cll(),0,new QTableWidgetItem(QString::fromStdString(c.get_name())));
    ui->mycoursetable->setItem(s.get_cll(),1,new QTableWidgetItem(QString::number(c.get_id())));
    ui->mycoursetable->setItem(s.get_cll(),2,new QTableWidgetItem(QString::number(c.get_credit_hour())));
    s.add_course(c.get_id());
    update_credit_LCD();
    return 1;
}

void MainWindow::on_removeButton_clicked()
{
    if (d.get_logged_flag()==0)
    {
        std::cout<<"Please login first!"<<std::endl;
        ui->belowloginlabel->setText("Please login first!");
        return;
    }
    std::cout<<"Remove Course"<<std::endl;
    QModelIndex cur = ui->mycoursetable->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->coursetable->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;
    student_list[d.get_logged_user_id()-1].remove_course(ui->mycoursetable->item(row,1)->text().toInt());
    course_list[ui->mycoursetable->item(row,1)->text().toInt()-1].stu_minus();
    //refresh
    update_stu_num();
    ui->mycoursetable->removeRow(row);

    update_credit_LCD();
}

void MainWindow::update_stu_num()
{
    std::vector<Course>::iterator it;
    for (it=course_list.begin();it!=course_list.end();it++)
    {
        for (int i=0;i<ui->coursetable->rowCount();i++)
            if (ui->coursetable->item(i,1)->text().toInt()==it->get_id())
            {
                ui->coursetable->setItem(i,3,new QTableWidgetItem(QString::number(it->get_stu_num())));
                break;
            }
    }
}
