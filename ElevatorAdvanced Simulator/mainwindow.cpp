#include "mainwindow.h"
#include "ui_mainwindow.h"

#define WAITING_TIME 700

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    //Set up the timer for refreshing
    timer->setInterval(RRFRESHING_INTERVAL_TIME);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateUI);
    timer->start();

    //Connect signal and slot

    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::on_pushButton_1_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);

    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::cancelButton_clicked);
    connect(ui->start_button, &QPushButton::clicked, this, &MainWindow::let_go);

    connect(ui->actionFloor1, &QAction::triggered, this, &MainWindow::form_1_triggered);
    connect(ui->actionFloor2, &QAction::triggered, this, &MainWindow::form_2_triggered);
    connect(ui->actionFloor3, &QAction::triggered, this, &MainWindow::form_3_triggered);
    connect(ui->actionFloor4, &QAction::triggered, this, &MainWindow::form_4_triggered);
    connect(ui->actionFloor5, &QAction::triggered, this, &MainWindow::form_5_triggered);
    connect(ui->actionFloor6, &QAction::triggered, this, &MainWindow::form_6_triggered);

    //Set digit counts
    ui->Time_lcd->setDigitCount(14);
    ui->Floor_number->setDigitCount(4);
    ui->F1->setDigitCount(1);
    ui->F2->setDigitCount(1);
    ui->F3->setDigitCount(1);
    ui->F4->setDigitCount(1);
    ui->F5->setDigitCount(1);
    ui->F6->setDigitCount(1);
    std::string a="Floor x";
    for (int i=0;i<6;i++)
    {
        a[6]=i+1+'0';
        form[i].set_sen(a);
        form[i].show_text();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cancelButton_clicked()
{
    for (int i=0;i<6;i++)
    {
        form[i].close();
    }
    this->close();
}

void MainWindow::mousePressEvent(QMouseEvent *event)//This function makes the window draggable
{

    if( (event->button() == Qt::LeftButton) ){
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
        //event->accept();
    }
    else if(event->button() == Qt::RightButton)
    {
        //Right click to close
        //this->close();
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        move(event->globalPos() - mousePoint);
        //event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void MainWindow::on_pushButton_1_clicked(){ele.Append(1);}
void MainWindow::on_pushButton_2_clicked(){ele.Append(2);}
void MainWindow::on_pushButton_3_clicked(){ele.Append(3);}
void MainWindow::on_pushButton_4_clicked(){ele.Append(4);}
void MainWindow::on_pushButton_5_clicked(){ele.Append(5);}
void MainWindow::on_pushButton_6_clicked(){ele.Append(6);}

void MainWindow::form_1_triggered(){form[0].show();}
void MainWindow::form_2_triggered(){form[1].show();}
void MainWindow::form_3_triggered(){form[2].show();}
void MainWindow::form_4_triggered(){form[3].show();}
void MainWindow::form_5_triggered(){form[4].show();}
void MainWindow::form_6_triggered(){form[5].show();}

void MainWindow::updateUI()
{
    //ele.test_show_tarlist();
    //ele.test_show_tardirelist();
    //std::cout<<ele.get_current_direction()<<std::endl;
    TimeShow();
    Refresh();
    if ((double)(clock()-timenow)>WAITING_TIME)
        let_go();//TEST
}

void MainWindow::Refresh()
{
    //Refresh the number of current floor
    char *fldis=new char[4];
    strcpy_s(fldis,5,"Fl.x");
    fldis[3]=ele.get_current_floor()+48;
    ui->Floor_number->display(fldis);
    delete [] fldis;

    //Refresh the display of floors in the target list
    ui->F1->display(ele.check(1));
    ui->F2->display(ele.check(2));
    ui->F3->display(ele.check(3));
    ui->F4->display(ele.check(4));
    ui->F5->display(ele.check(5));
    ui->F6->display(ele.check(6));

    //NEW
    int temp;
    for (int i=1;i<=6;i++)
    {
        temp=form[i-1].take_sign();
        if (temp==1)
        {
            ele.Append(i,0);
        }
        else if(temp==2)
        {
            ele.Append(i,1);
        }
    }
}

void MainWindow::let_go()
{
    timenow=clock();
    //ele.set_dtime(1);
    //ele.set_direction();
    ele.MoveOn_s();
}

void MainWindow::TimeShow()
{
    std::time_t current_time = std::time(nullptr);
    //std::cout << "Current date: " << std::asctime(std::localtime(&current_time)) << std::endl;

    ui->Time_lcd->display(std::asctime(std::localtime(&current_time)));
}
