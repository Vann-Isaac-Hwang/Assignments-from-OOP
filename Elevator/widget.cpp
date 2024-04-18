#include "widget.h"
#include "ui_widget.h"
#include <QProcess>

#define WAITING_TIME 2000

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);


    timer->setInterval(10);
    connect(timer, &QTimer::timeout, this, &Widget::updateUI);
    timer->start();
    //Connect signal and slot
    ui->Time_lcd->setDigitCount(14);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &Widget::on_pushButton_1_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::on_pushButton_2_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::on_pushButton_3_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::on_pushButton_4_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::on_pushButton_5_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::on_pushButton_6_clicked);
    connect(ui->start_button, &QPushButton::clicked, this, &Widget::let_go);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Widget::cancelButton_clicked);
    //Set digit counts
    ui->Floor_number->setDigitCount(4);
    ui->F1->setDigitCount(1);
    ui->F2->setDigitCount(1);
    ui->F3->setDigitCount(1);
    ui->F4->setDigitCount(1);
    ui->F5->setDigitCount(1);
    ui->F6->setDigitCount(1);
    Refresh();
    //ui->Floor_number->display(xx);
}

void Widget::let_go()
{
    ele.MoveOn();
    timenow=clock();
}

void Widget::updateUI()
{
    TimeShow();
    Refresh();
    if ((double)(clock()-timenow)>WAITING_TIME)
        let_go();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::TimeShow()
{
    std::time_t current_time = std::time(nullptr);
    //std::cout << "Current date: " << std::asctime(std::localtime(&current_time)) << std::endl;

    ui->Time_lcd->display(std::asctime(std::localtime(&current_time)));
}

void Widget::on_pushButton_1_clicked(){ele.Append(1);}
void Widget::on_pushButton_2_clicked(){ele.Append(2);}
void Widget::on_pushButton_3_clicked(){ele.Append(3);}
void Widget::on_pushButton_4_clicked(){ele.Append(4);}
void Widget::on_pushButton_5_clicked(){ele.Append(5);}
void Widget::on_pushButton_6_clicked(){ele.Append(6);}

void Widget::Refresh()
{
    char *fldis=new char[4];
    strcpy(fldis,"Fl.x");
    fldis[3]=ele.get_current_floor()+48;
    ui->Floor_number->display(fldis);
    delete [] fldis;
    if (ele.check(1)==1)
         ui->F1->display(1);
    else
         ui->F1->display(0);

    if (ele.check(2)==1)
         ui->F2->display(1);
    else
         ui->F2->display(0);

    if (ele.check(3)==1)
         ui->F3->display(1);
    else
         ui->F3->display(0);

    if (ele.check(4)==1)
         ui->F4->display(1);
    else
         ui->F4->display(0);

    if (ele.check(5)==1)
         ui->F5->display(1);
    else
         ui->F5->display(0);

    if (ele.check(6)==1)
         ui->F6->display(1);
    else
         ui->F6->display(0);

}

void Widget::mousePressEvent(QMouseEvent *event)
{

    if( (event->button() == Qt::LeftButton) ){
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
        //        event->accept();
    }
    else if(event->button() == Qt::RightButton){
        //如果是右键
        this->close();

    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{


    //    if(event->buttons() == Qt::LeftButton){  //如果这里写这行代码，拖动会有点问题
    if(mouse_press){
        move(event->globalPos() - mousePoint);
        //        event->accept();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void Widget::cancelButton_clicked()
{
    this->close();
}
