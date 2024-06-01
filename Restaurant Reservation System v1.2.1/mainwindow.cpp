#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlite3.h"
#include <QTableWidget>

#define RRFRESHING_INTERVAL_TIME 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db("data.db")
{
    ui->setupUi(this);

    //Set windows title
    this->setWindowTitle("Restaurant Reserve");

    //Set color
    //set_theme("BlackNBlue");
    set_theme("Default");

    //NEW
    on_my_reservation_tabButton_clicked();
    ui->quitButton->hide();

    //Hide password modifier
    show_password_edit(false);
    ui->usernameEdit->hide();
    ui->nicknameEdit->hide();
    ui->phoneEdit->hide();

    ui->tabWidget->hide();

    //Set up reservation table
    ui->reservation_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->reservation_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->reservation_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reservation_table->setShowGrid(true);
    //QFont Font = ui->reservation_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->reservation_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->reservation_table->setColumnWidth(0,60);
    ui->reservation_table->setColumnWidth(1,80);
    ui->reservation_table->setColumnWidth(2,160);
    ui->reservation_table->setColumnWidth(3,70);
    ui->reservation_table->setColumnWidth(4,60);
    ui->reservation_table->setColumnWidth(5,60);
    ui->reservation_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Set up reserve table
    ui->reserve_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->reserve_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->reserve_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reserve_table->setShowGrid(true);
    //QFont Font = ui->reserve_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->reserve_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->reserve_table->setColumnWidth(0,60);
    ui->reserve_table->setColumnWidth(1,80);
    ui->reserve_table->setColumnWidth(2,140);
    ui->reserve_table->setColumnWidth(3,70);
    ui->reserve_table->setColumnWidth(4,60);
    ui->reserve_table->setColumnWidth(5,60);
    ui->reserve_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Set up the timer for refreshing
    timer->setInterval(RRFRESHING_INTERVAL_TIME);
    connect(timer, &QTimer::timeout, this, &MainWindow::refresh_time);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -----------------------------------------------------PUBLIC-----------------------------------------------------

// Assign value to variable current_user when logging in

void MainWindow::set_current_user(const std::string username)
{
    current_user=username;
    set_profile();
    ui->up_label_2->setText(QString::fromStdString("Hello, "+db.get_user_info(current_user).nickname));
    get_reservation_list();
    get_reserve_list();
}

// Refresh time label

void MainWindow::refresh_time()
{
    ui->time_label->setText(QString::fromStdString(str_time()));
}

// Acquire data

void MainWindow::get_reservation_list()
{
    //clear reservation table
    std::cout<<"\nClearing reservation table..."<<std::endl;
    ui->reservation_table->clearContents();
    ui->reservation_table->setRowCount(0);

    //Fetch reservation information
    std::cout<<"\nFetching reservation information..."<<std::endl;
    //std::cout<<"TEST: The length of table reservation:"<<db.get_table_length("reservation")<<std::endl;// TEST
    int table_length = db.get_table_length("reservation");
    for (int i=0,j=0;i<table_length;i++)
    {
        if (db.getReservationInfo(i).user_name!=current_user) continue;

        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(j));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->reservation_table->insertRow(j);
        check->setText(QString::number(j));  //display order
        //ui->coursetable->setItem(i,0,check); //insert check box

        ui->reservation_table->setItem(j,0,new QTableWidgetItem(QString::number(db.getReservationInfo(i).id)));
        ui->reservation_table->setItem(j,1,new QTableWidgetItem(QString::fromStdString(db.getReservationInfo(i).user_name)));
        QString duration = QString::number(db.getReservationInfo(i).dur.year)+"-"
                           +QString::number(db.getReservationInfo(i).dur.month)+"-"
                           +QString::number(db.getReservationInfo(i).dur.day)+" "
                           +QString::number(db.getReservationInfo(i).dur.hour_begin)+":"
                           +QString::number(db.getReservationInfo(i).dur.minute_begin)+" ~ "
                           +QString::number(db.getReservationInfo(i).dur.hour_end)+":"
                           +QString::number(db.getReservationInfo(i).dur.minute_end);
        ui->reservation_table->setItem(j,2,new QTableWidgetItem(duration));
        ui->reservation_table->setItem(j,3,new QTableWidgetItem(QString::fromStdString(db.getReservationInfo(i).table_type)));
        ui->reservation_table->setItem(j,4,new QTableWidgetItem(QString::number(db.getReservationInfo(i).table_id)));
        ui->reservation_table->setItem(j,5,new QTableWidgetItem(QString::number(db.getReservationInfo(i).deposit)));
    }
}

void MainWindow::get_reserve_list()
{
    //clear reserve table
    std::cout<<"\nClearing reserve table..."<<std::endl;
    ui->reserve_table->clearContents();
    ui->reserve_table->setRowCount(0);

    //Fetch reserve information
    std::cout<<"\nFetching reserve information..."<<std::endl;
    //std::cout<<"TEST: The length of table reservation:"<<db.get_table_length("reservation")<<std::endl;// TEST
    int table_length = db.get_table_length("reservation");
    for (int i=0,j=0;i<table_length;i++)
    {
        if (db.getReservationInfo(i).user_name!="") continue;

        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(j));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->reserve_table->insertRow(j);
        check->setText(QString::number(j));  //display order
        //ui->coursetable->setItem(i,0,check); //insert check box

        ui->reserve_table->setItem(j,0,new QTableWidgetItem(QString::number(db.getReservationInfo(i).id)));
        QString duration = QString::number(db.getReservationInfo(i).dur.year)+"-"
                           +QString::number(db.getReservationInfo(i).dur.month)+"-"
                           +QString::number(db.getReservationInfo(i).dur.day)+" "
                           +QString::number(db.getReservationInfo(i).dur.hour_begin)+":"
                           +QString::number(db.getReservationInfo(i).dur.minute_begin)+" ~ "
                           +QString::number(db.getReservationInfo(i).dur.hour_end)+":"
                           +QString::number(db.getReservationInfo(i).dur.minute_end);
        ui->reserve_table->setItem(j,1,new QTableWidgetItem(duration));
        ui->reserve_table->setItem(j,2,new QTableWidgetItem(QString::fromStdString(db.getReservationInfo(i).table_type)));
        ui->reserve_table->setItem(j,3,new QTableWidgetItem(QString::number(db.getReservationInfo(i).table_id)));
        ui->reserve_table->setItem(j,4,new QTableWidgetItem(QString::number(db.getReservationInfo(i).deposit)));
    }
}

// Functions for profile page

void MainWindow::set_profile()
{
    //ui->profile_username_label->setText(QString::fromStdString("Name: "+username));
    ui->profile_username->setText(QString::fromStdString(current_user));
    ui->profile_nickname->setText(QString::fromStdString(db.get_user_info(current_user).nickname));
    ui->profile_user_id->setText(QString::number(db.get_user_info(current_user).id));
    ui->profile_phone->setText(QString::fromStdString(db.get_user_info(current_user).phone_number));
    //ui->profile_password->setText(QString::fromStdString(db.get_user_info(current_user).password));

    ui->up_label_2->setText(QString::fromStdString("Hello, "+db.get_user_info(current_user).nickname));
}

void MainWindow::show_password_edit(bool state)
{
    if (state)
    {
        ui->cpasswordEdit->show();
        ui->passwordEdit->show();
        ui->password_modifyButton->show();
        ui->password_changeButton->hide();
    }
    else
    {
        ui->cpasswordEdit->hide();
        ui->passwordEdit->hide();
        ui->password_modifyButton->hide();
        ui->password_changeButton->show();
    }
}

// Beautify

void MainWindow::set_theme(const std::string& s)
{
    if (s=="Default")
    {
        set_all_table_stylesheet("");

        ui->tabWidget->setStyleSheet("");
        ui->tabWidget->setDocumentMode(false); //Restore white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("");
        //ui->statusbar->setStyleSheet("");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
        ui->left_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
    }
    else if (s=="BlackNBlue")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#1B89A1}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #454545,stop:1 #323232); }"
"QTableWidget{background-color:rgb(45,45,50);border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(240,240,240);\
                                             background-color: rgb(45,45,45);");
        ui->menubar->setStyleSheet("background-color: rgb(45,45,45);");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("background-color: rgb(55,55,55);");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
        ui->left_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
    }
    else if (s=="BlueNPurple")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#1B89A1}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #454545,stop:1 #323232); }"
"QTableWidget{background-color:rgb(45,45,50);border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(240,240,240);\
                                             background: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #00BFFF,stop:1 #6A5ACD);");
        ui->menubar->setStyleSheet("background-color: rgb(45,45,45);");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("background-color: rgb(55,55,55);");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
        ui->left_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
    }
    else if (s=="Fluent")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#3490DE}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#232323;  border:1px solid #f5f5f5; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#f5f5f5; }"
"QTableWidget{background-color:#f9f7f7;border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("background-color: #f5f5f5;");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
        ui->left_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
    }
    else if (s=="FluentDark")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#1B89A1}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#323232; }"
"QTableWidget{background-color:rgb(45,45,50);border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(240,240,240);\
                                             background-color: rgb(45,45,45);");
        ui->menubar->setStyleSheet("background-color: rgb(45,45,45);");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(60,60,60);}"
                                  "QPushButton{background-color:rgb(80,80,80);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
        ui->left_widget->setStyleSheet("background-color: rgb(50,50,50); color: rgb(220,220,220);");
    }
    else if (s=="FluentLight")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#3490DE}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#232323;  border:1px solid #f5f5f5; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#f5f5f5; }"
"QTableWidget{background-color:#f9f7f7;border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("background-color: #f5f5f5;");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(240,240,240); color: rgb(45,45,45);");
        ui->left_widget->setStyleSheet("background-color: rgb(240,240,240); color: rgb(45,45,45);");
    }
    else if (s=="MS Blue")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#3490DE}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#232323;  border:1px solid #f5f5f5; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#f5f5f5; }"
"QTableWidget{background-color:#f9f7f7;border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("background-color: #f5f5f5;");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(0,120,215); color: white;");
        ui->left_widget->setStyleSheet("background-color: rgb(240,240,240); color: rgb(45,45,45);");
    }
    else if (s=="MS Green")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#3490DE}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#232323;  border:1px solid #f5f5f5; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#f5f5f5; }"
"QTableWidget{background-color:#f9f7f7;border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("background-color: #f5f5f5;");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("background-color: rgb(0,128,0); color: white;");
        ui->left_widget->setStyleSheet("background-color: rgb(240,240,240); color: rgb(45,45,45);");
    }
    else if (s=="Minecraft Soil")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#3490DE}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#232323;  border:1px solid #f5f5f5; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#f5f5f5; }"
"QTableWidget{background-color:#f9f7f7;border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("background-color: #f5f5f5;");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("QWidget{background-color: rgb(0,128,0); color: white;} #frame{background-image: url(:/new/prefix1/Soil.png);background-color: rgba(255, 255, 255, 200);};");
        //ui->frame->setStyleSheet("#frame{background-image: url(:/new/prefix1/Soil.png);background-color: rgba(255, 255, 255, 200);}");
        ui->left_widget->setStyleSheet("background-color: rgb(240,240,240); color: rgb(45,45,45);");
    }
    else if (s=="Minecraft Wood")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgba(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#3490DE}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#232323;  border:1px solid #f5f5f5; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:#f5f5f5; }"
"QTableWidget{background-color:#f9f7f7;border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side

        ui->centralwidget->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
        ui->menubar->setStyleSheet("background-color: #f5f5f5;");
        //ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");
        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        set_all_label_stylesheet("background-color: transparent;");
        ui->top_widget->setStyleSheet("QWidget{background-color: rgb(0,128,0); color: white;} #frame{background-image: url(:/new/prefix1/Wood.png);background-color: rgba(255, 255, 255, 200);};");
        //ui->frame->setStyleSheet("#frame{background-image: url(:/new/prefix1/Soil.png);background-color: rgba(255, 255, 255, 200);}");
        ui->left_widget->setStyleSheet("background-color: rgb(240,240,240); color: rgb(45,45,45);");
    }
}

void MainWindow::set_all_button_stylesheet(const QString& stylesheet)
{
    ui->quitButton->setStyleSheet(stylesheet);
    ui->deleteButton->setStyleSheet(stylesheet);
    ui->menuButton->setStyleSheet(stylesheet);
    ui->reserveButton->setStyleSheet(stylesheet);
    ui->password_modifyButton->setStyleSheet(stylesheet);
    // Tab My profile
    ui->username_changeButton->setStyleSheet(stylesheet);
    ui->nickname_changeButton->setStyleSheet(stylesheet);
    ui->phone_changeButton->setStyleSheet(stylesheet);
    ui->password_changeButton->setStyleSheet(stylesheet);
    ui->password_modifyButton->setStyleSheet(stylesheet);
}

void MainWindow::set_side_button_stylesheet(const QString& stylesheet)
{
    ui->my_reservation_tabButton->setStyleSheet(stylesheet);
    ui->reserve_tabButton->setStyleSheet(stylesheet);
    ui->my_profile_tabButton->setStyleSheet(stylesheet);
    ui->settings_tabButton->setStyleSheet(stylesheet);
}

void MainWindow::set_all_table_stylesheet(const QString& stylesheet)
{
    ui->reservation_table->setStyleSheet(stylesheet);
    ui->reserve_table->setStyleSheet(stylesheet);
}

void MainWindow::set_all_label_stylesheet(const QString& stylesheet)
{
    ui->label->setStyleSheet(stylesheet);
    ui->label_2->setStyleSheet(stylesheet);
    ui->time_label->setStyleSheet(stylesheet);
    ui->up_label_2->setStyleSheet(stylesheet);
    ui->profile_nickname_label->setStyleSheet(stylesheet);
    ui->profile_password_label->setStyleSheet(stylesheet);
    ui->profile_phone_label->setStyleSheet(stylesheet);
    ui->profile_username_label->setStyleSheet(stylesheet);
    ui->profile_user_id_label->setStyleSheet(stylesheet);
    ui->delete_promptlabel->setStyleSheet(stylesheet);
    ui->reserve_promptlabel->setStyleSheet(stylesheet);
    ui->profile_username->setStyleSheet(stylesheet);
    ui->profile_nickname->setStyleSheet(stylesheet);
    ui->profile_phone->setStyleSheet(stylesheet);
    ui->profile_password->setStyleSheet(stylesheet);
    ui->profile_user_id->setStyleSheet(stylesheet);
}

// -----------------------------------------------------SLOTS-----------------------------------------------------

// Global

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

// My reservation

void MainWindow::on_deleteButton_clicked()
{
    std::cout<<"Removing my reservation..."<<std::endl;
    QModelIndex cur = ui->reservation_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->reservation_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;

    duration d = db.get_reservation_info(ui->reservation_table->item(row,0)->text().toInt()).dur;

    bool f=
    (
        (
            d.year==get_year() &&
            d.month==get_month() &&
            d.day==get_day()
        )
        &&
        (
            (d.hour_begin-get_hour())*60+(d.minute_begin-get_minute())>=180
        )
    );
    //Check the time
    if  (f)
    {
        db.delete_reservation(ui->reservation_table->item(row, 0)->text().toInt());
        db.delete_pair(ui->reservation_table->item(row, 0)->text().toInt());
        //Refresh
        get_reservation_list();
        ui->delete_promptlabel->setText("Select a reservation below and click Delete to delete it");
        //ui->user_list->removeRow(row);
    }
    else
    {
        ui->delete_promptlabel->setText("Sorry, less than 3 hours before reservation starts.");
    }
}

void MainWindow::on_menuButton_clicked()
{
    std::cout<<"Opening menu..."<<std::endl;

    QModelIndex cur = ui->reservation_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->reservation_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;

    int selected_reservation_id = ui->reservation_table->item(row,0)->text().toInt();
    food_menu.set_reservation_id(selected_reservation_id);
    food_menu.set_theme(ui->theme_selectBox->currentText().toStdString());
    food_menu.show();
    food_menu.get_food_list();
    food_menu.get_this_food_list();
}

// Reserve

void MainWindow::on_reserveButton_clicked()
{
    std::cout<<"Reserving..."<<std::endl;
    // 1.change the username of the reservation in table reservation to current_user.
    QModelIndex cur = ui->reserve_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->reserve_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;
    int reserve_id = ui->reserve_table->item(row,0)->text().toInt();
    db.modify_reservation_user_name(reserve_id, current_user);
    // 2.refresh reserve list
    get_reserve_list();
    // 3.refresh reservation list
    get_reservation_list();
}

// My profile

void MainWindow::on_username_changeButton_clicked()
{
    if (ui->username_changeButton->text()=="Change")
    {
        ui->usernameEdit->show();
        ui->username_changeButton->setText("Confirm");
    }
    else if (ui->username_changeButton->text()=="Confirm")
    {
        std::string new_username=ui->usernameEdit->text().toStdString();
        if (ui->usernameEdit->text().isEmpty())
        {
            ui->profile_password->setText("Please Enter new username.");
            return;
        }
        if (db.check_exist(ui->usernameEdit->text().toStdString(),"user"))
        {
            ui->profile_password->setText("The username is in use.");
            return;
        }
        if (db.modify_user_name(db.get_user_info(current_user).id, ui->usernameEdit->text().toStdString()) &&
            db.replace_all_username(current_user,new_username))
        {
            ui->profile_password->setText("Successfully changed username.");
            set_current_user(new_username);
        }
        else
        {
            ui->profile_password->setText("Failed to change username!");
        }
        ui->usernameEdit->hide();
        ui->username_changeButton->setText("Change");
    }
}

void MainWindow::on_nickname_changeButton_clicked()
{
    if (ui->nickname_changeButton->text()=="Change")
    {
        ui->nicknameEdit->show();
        ui->nickname_changeButton->setText("Confirm");
    }
    else if (ui->nickname_changeButton->text()=="Confirm")
    {
        std::string new_nickname=ui->nicknameEdit->text().toStdString();
        if (ui->nicknameEdit->text().isEmpty())
        {
            ui->profile_password->setText("Please Enter new nickname.");
            return;
        }
        if (db.get_user_info(current_user).nickname==new_nickname)
        {
            ui->profile_password->setText("Please enter a different nickname.");
            return;
        }
        if (db.modify_user_nickname(db.get_user_info(current_user).id, new_nickname))
        {
            ui->profile_password->setText("Successfully changed nickname.");
            set_profile();
        }
        else
        {
            ui->profile_password->setText("Failed to change nickname!");
        }
        ui->nicknameEdit->hide();
        ui->nickname_changeButton->setText("Change");
    }
}

void MainWindow::on_phone_changeButton_clicked()
{
    if (ui->phone_changeButton->text()=="Change")
    {
        ui->phoneEdit->show();
        ui->phone_changeButton->setText("Confirm");
    }
    else if (ui->phone_changeButton->text()=="Confirm")
    {
        std::string new_phone=ui->phoneEdit->text().toStdString();
        if (ui->phoneEdit->text().isEmpty())
        {
            ui->profile_password->setText("Please Enter new phone number.");
            return;
        }
        if (db.get_user_info(current_user).phone_number==new_phone)
        {
            ui->profile_password->setText("Please enter a different phone number.");
            return;
        }
        if (new_phone.length()!=11)
        {
            ui->profile_password->setText("Please enter a valid phone number.");
            return;
        }
        if (db.modify_user_phone_number(db.get_user_info(current_user).id, ui->phoneEdit->text().toStdString()))
        {
            ui->profile_password->setText("Successfully changed phone number.");
            set_profile();
        }
        else
        {
            ui->profile_password->setText("Failed to change phone number!");
        }
        ui->phoneEdit->hide();
        ui->phone_changeButton->setText("Change");
    }
}

void MainWindow::on_password_changeButton_clicked()
{
    show_password_edit(true);
}

void MainWindow::on_password_modifyButton_clicked()
{

    if (ui->cpasswordEdit->text().isEmpty())
    {
        ui->profile_password->setText("Please Enter old password!");
        return;
    }
    if (ui->passwordEdit->text().isEmpty())
    {
        ui->profile_password->setText("Please Enter new password!");
        return;
    }
    std::string cpassword = ui->cpasswordEdit->text().toStdString();
    if (db.verify_password(current_user,cpassword,"user")==0)
    {
        ui->profile_password->setText("Wrong old password!");
        return;
    }
    else
    {
        std::string npassword = ui->passwordEdit->text().toStdString();
        if (db.modify_user_password(db.get_user_info(current_user).id, npassword))
        {
            ui->profile_password->setText("Successfully changed password.");
        }
        else
        {
            ui->profile_password->setText("Failed to change password!");
        }
        ui->passwordEdit->clear();
        ui->cpasswordEdit->clear();
        show_password_edit(false);
    }
}

// Table widget

void MainWindow::on_my_reservation_tabButton_clicked()
{
    //General
    set_side_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(60,60,60);}"
                               "QPushButton{border:0px}"
                               "QPushButton{border-radius:0px}"
                               "QPushButton{padding:2px 4px}");
    //This button
    ui->my_reservation_tabButton->setStyleSheet("color:black;"
                                                "hover{color:green};"
                                                "background-color:rgba(220,220,220,255);"
                                                "border:0px");


    ui->stackedWidget->setCurrentIndex(0);

    ui->delete_promptlabel->setText("Select a reservation below and click Delete to delete it");
    get_reservation_list();
}

void MainWindow::on_reserve_tabButton_clicked()
{
    //General
    set_side_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(60,60,60);}"
                               "QPushButton{border:0px}"
                               "QPushButton{border-radius:0px}"
                               "QPushButton{padding:2px 4px}");
    //This button
    ui->reserve_tabButton->setStyleSheet("color:black;"
                                         "hover{color:green};"
                                         "background-color:rgba(220,220,220,255);"
                                         "border:0px");

    ui->stackedWidget->setCurrentIndex(1);

    get_reserve_list();
}

void MainWindow::on_my_profile_tabButton_clicked()
{
    //General
    set_side_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(60,60,60);}"
                               "QPushButton{border:0px}"
                               "QPushButton{border-radius:0px}"
                               "QPushButton{padding:2px 4px}");
    //This button
    ui->my_profile_tabButton->setStyleSheet("color:black;"
                                            "hover{color:green};"
                                            "background-color:rgba(220,220,220,255);"
                                            "border:0px");

    ui->stackedWidget->setCurrentIndex(2);

    ui->profile_password->setText("");
    show_password_edit(false);
    ui->usernameEdit->hide();
    ui->nicknameEdit->hide();
    ui->phoneEdit->hide();
    ui->username_changeButton->setText("Change");
    ui->nickname_changeButton->setText("Change");
    ui->phone_changeButton->setText("Change");
}

void MainWindow::on_settings_tabButton_clicked()
{
    //General
    set_side_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(60,60,60);}"
                               "QPushButton{border:0px}"
                               "QPushButton{border-radius:0px}"
                               "QPushButton{padding:2px 4px}");
    //This button
    ui->settings_tabButton->setStyleSheet("color:black;"
                                          "hover{color:green};"
                                          "background-color:rgba(220,220,220,255);"
                                          "border:0px");

    ui->stackedWidget->setCurrentIndex(3);
}

// ELSE

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch (index)
    {
    case 0:
    {
        ui->delete_promptlabel->setText("Select a reservation below and click Delete to delete it");
        get_reservation_list();
        break;
    }
    case 1:
    {
        get_reserve_list();
        break;
    }
    case 2:
    {
        ui->profile_password->setText("");
        show_password_edit(false);
        ui->usernameEdit->hide();
        ui->nicknameEdit->hide();
        ui->phoneEdit->hide();
        ui->username_changeButton->setText("Change");
        ui->nickname_changeButton->setText("Change");
        ui->phone_changeButton->setText("Change");
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_theme_selectBox_currentIndexChanged(int index)
{
    set_theme(ui->theme_selectBox->currentText().toStdString());
}

