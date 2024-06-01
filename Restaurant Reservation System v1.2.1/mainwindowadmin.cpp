#include "mainwindowadmin.h"
#include "ui_mainwindowadmin.h"
#include "sqlite3.h"
#include <QTableWidget>

#define RRFRESHING_INTERVAL_TIME 100

MainWindowAdmin::MainWindowAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowAdmin)
    , db("data.db")
{
    ui->setupUi(this);

    log_file.open("log.txt", std::ios::app);

    //Set windows title
    this->setWindowTitle("Restaurant Reservation Manager");

    log("Constructor: Setting up reservation table layout...");
    //Set up reservation table layout
    ui->reservation_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->reservation_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->reservation_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reservation_table->setShowGrid(true);
    //QFont Font = ui->reservation_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->reservation_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->reservation_table->setColumnWidth(0,60);
    ui->reservation_table->setColumnWidth(1,80);
    ui->reservation_table->setColumnWidth(2,140);
    ui->reservation_table->setColumnWidth(3,70);
    ui->reservation_table->setColumnWidth(4,60);
    ui->reservation_table->setColumnWidth(5,60);
    ui->reservation_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    log();

    log("Constructor: Setting up user table layout...");
    //Set up user table
    ui->user_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->user_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->user_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->user_table->setShowGrid(true);
    //QFont Font = ui->user_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->user_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->user_table->setColumnWidth(0,60);
    ui->user_table->setColumnWidth(1,80);
    ui->user_table->setColumnWidth(2,140);
    ui->user_table->setColumnWidth(3,70);
    ui->user_table->setColumnWidth(4,60);
    ui->user_table->setColumnWidth(5,60);
    ui->user_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    log();

    log("Constructor: Setting up food table layout...");
    //Set up food table
    ui->food_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->food_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->food_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->food_table->setShowGrid(true);
    //QFont Font = ui->food_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->food_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->food_table->setColumnWidth(0,60);
    ui->food_table->setColumnWidth(1,80);
    ui->food_table->setColumnWidth(2,140);
    ui->food_table->setColumnWidth(3,70);
    ui->food_table->setColumnWidth(4,60);
    ui->food_table->setColumnWidth(5,60);
    ui->food_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    log();

    log("Constructor: Setting up pair table layout...");
    //Set up pair table
    ui->pair_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pair_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->pair_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pair_table->setShowGrid(true);
    //QFont Font = ui->pair_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->pair_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->pair_table->setColumnWidth(0,60);
    ui->pair_table->setColumnWidth(1,80);
    ui->pair_table->setColumnWidth(2,140);
    ui->pair_table->setColumnWidth(3,70);
    ui->pair_table->setColumnWidth(4,60);
    ui->pair_table->setColumnWidth(5,60);
    ui->pair_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    log();

    //Set default date for date edit
    set_default_date_edit();

    log("Constructor: Setting up timer...");
    //Set up the timer for refreshing
    timer->setInterval(RRFRESHING_INTERVAL_TIME);
    connect(timer, &QTimer::timeout, this, &MainWindowAdmin::refresh_time);
    timer->start();
    log();

}

MainWindowAdmin::~MainWindowAdmin()
{
    log("Destructor: Quitting...");
    delete ui;
}

// -----------------------------------------------------PUBLIC-----------------------------------------------------

// Assign value to variable current_user when logging in

void MainWindowAdmin::set_current_user(const std::string& username)
{
    log("set_current_user: Setting current user's name...");
    current_user=username;
    ui->up_label->setText(QString::fromStdString("Name: "+username));
    get_reservation_list();
    get_user_list();
    get_food_list();
    get_food_reservation_list();
    log();
}

// Refresh time label

void MainWindowAdmin::refresh_time()
{
    ui->time_label->setText(QString::fromStdString(str_time()));
}

// Acquire data

void MainWindowAdmin::get_reservation_list()
{
    log("get_reservation_list: Getting reservation list...");

    log("get_reservation_list: Getting reservation list::Clearing reservation table...");
    //clear reservation table
    std::cout<<"\nClearing reservation table..."<<std::endl;
    ui->reservation_table->clearContents();
    ui->reservation_table->setRowCount(0);
    log();

    log("get_reservation_list: Getting reservation list::Fetching reservation information...");
    //Fetch reservation information
    std::cout<<"\nFetching reservation information..."<<std::endl;
    //std::cout<<"TEST: The length of table reservation:"<<db.get_table_length("reservation")<<std::endl;// TEST
    int table_length = db.get_table_length("reservation");
    for (int i=0;i<table_length;i++)
    {
        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(i));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->reservation_table->insertRow(i);
        check->setText(QString::number(i));  //display order
        //ui->coursetable->setItem(i,0,check); //insert check box

        ui->reservation_table->setItem(i,0,new QTableWidgetItem(QString::number(db.getReservationInfo(i).id)));
        ui->reservation_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(db.getReservationInfo(i).user_name)));
        QString duration = QString::number(db.getReservationInfo(i).dur.year)+"-"
                           +QString::number(db.getReservationInfo(i).dur.month)+"-"
                           +QString::number(db.getReservationInfo(i).dur.day)+" "
                           +QString::number(db.getReservationInfo(i).dur.hour_begin)+":"
                           +QString::number(db.getReservationInfo(i).dur.minute_begin)+" ~ "
                           +QString::number(db.getReservationInfo(i).dur.hour_end)+":"
                           +QString::number(db.getReservationInfo(i).dur.minute_end);
        ui->reservation_table->setItem(i,2,new QTableWidgetItem(duration));
        ui->reservation_table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(db.getReservationInfo(i).table_type)));
        ui->reservation_table->setItem(i,4,new QTableWidgetItem(QString::number(db.getReservationInfo(i).table_id)));
        ui->reservation_table->setItem(i,5,new QTableWidgetItem(QString::number(db.getReservationInfo(i).deposit)));
    }
    log();

    log();
}

void MainWindowAdmin::get_food_reservation_list()
{
    log("get_food_reservation_list: Getting pair list...");

    log("get_food_reservation_list: Getting pair list::Clearing pair table...");
    //clear pair table
    std::cout<<"\nClearing pair table..."<<std::endl;
    ui->pair_table->clearContents();
    ui->pair_table->setRowCount(0);
    log();

    log("get_food_reservation_list: Getting pair list::Fetching pair information...");
    //Fetch pair information
    std::cout<<"\nFetching pair information..."<<std::endl;
    //std::cout<<"TEST: The length of table food:"<<db.get_table_length("reservation")<<std::endl;// TEST
    int table_length = db.get_table_length("pair");

    for (int i=0;i<table_length;i++)
    {
        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(i));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->pair_table->insertRow(i);
        check->setText(QString::number(i));  //display order
        //ui->pair_table->setItem(i,0,check); //insert check box

        ui->pair_table->setItem(i,0,new QTableWidgetItem(QString::number(db.getPairInfo(i).id)));
        ui->pair_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(db.get_reservation_info(db.getPairInfo(i).reservation_id).user_name)));
        ui->pair_table->setItem(i,2,new QTableWidgetItem(QString::number(db.getPairInfo(i).reservation_id)));
        ui->pair_table->setItem(i,3,new QTableWidgetItem(QString::number(db.getPairInfo(i).food_id)));
        ui->pair_table->setItem(i,4,new QTableWidgetItem(QString::fromStdString(db.get_food_info(db.getPairInfo(i).food_id).name)));
        ui->pair_table->setItem(i,5,new QTableWidgetItem(QString::number(db.get_food_info(db.getPairInfo(i).food_id).price)));

    }
    log();

    log();
}

void MainWindowAdmin::get_food_list()
{
    log("get_food_list: Getting food list...");

    log("get_food_list: Getting food list::Clearing food table...");
    //clear food table
    std::cout<<"\nClearing food table..."<<std::endl;
    ui->food_table->clearContents();
    ui->food_table->setRowCount(0);
    log();

    log("get_food_list: Getting food list::Fetching food information...");
    //Fetch food information
    std::cout<<"\nFetching food information..."<<std::endl;
    //std::cout<<"TEST: The length of table food:"<<db.get_table_length("reservation")<<std::endl;// TEST
    int table_length = db.get_table_length("food");
    for (int i=0;i<table_length;i++)
    {
        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(i));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->food_table->insertRow(i);
        check->setText(QString::number(i));  //display order
        //ui->food_table->setItem(i,0,check); //insert check box

        ui->food_table->setItem(i,0,new QTableWidgetItem(QString::number(db.getFoodInfo(i).id)));
        ui->food_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(db.getFoodInfo(i).name)));
        ui->food_table->setItem(i,2,new QTableWidgetItem(QString::number(db.getFoodInfo(i).price)));
        ui->food_table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(db.getFoodInfo(i).description)));
    }
    log();

    log();
}

void MainWindowAdmin::get_user_list()
{
    log("get_user_list: Getting user list...");

    log("get_user_list: Getting user list::Clearing user table...");
    //clear user table
    std::cout<<"\nClearing user table..."<<std::endl;
    ui->user_table->clearContents();
    ui->user_table->setRowCount(0);
    log();

    log("get_user_list: Getting user list::Fetching user information...");
    //Fetch user information
    std::cout<<"\nFetching user information..."<<std::endl;
    //std::cout<<"TEST: The length of table user:"<<db.get_table_length("user")<<std::endl;// TEST
    int table_length = db.get_table_length("user");
    for (int i=0;i<table_length;i++)
    {
        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(i));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->user_table->insertRow(i);
        check->setText(QString::number(i));  //display order
        //ui->coursetable->setItem(i,0,check); //insert check box

        ui->user_table->setItem(i,0,new QTableWidgetItem(QString::number(db.getUserInfo(i).id)));
        ui->user_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(db.getUserInfo(i).name)));
        ui->user_table->setItem(i,2,new QTableWidgetItem(QString::fromStdString(db.getUserInfo(i).nickname)));
        ui->user_table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(db.getUserInfo(i).phone_number)));
        ui->user_table->setItem(i,4,new QTableWidgetItem(QString::fromStdString(db.getUserInfo(i).password)));
    }
    log();

    log();
}

// Set the initial value of date editor

void MainWindowAdmin::set_default_date_edit()
{
    log("set_default_date_edit: Setting date...");
    ui->dateEdit->date().setDate(get_year(),get_month(),get_day());
    log();
}

// Beautify

void MainWindowAdmin::set_theme(const std::string s)
{
    if (s=="Default")
    {
        set_all_table_stylesheet("");

        ui->tabWidget->setStyleSheet("");
        ui->tabWidget->setDocumentMode(false); //Restore white side

        ui->centralwidget->setStyleSheet("");
        ui->menubar->setStyleSheet("");
        ui->statusbar->setStyleSheet("");

        set_all_button_stylesheet("");
    }
    else if (s=="BlackNBlue")
    {
        set_all_table_stylesheet("QTableWidget::item:hover{background-color:rgb(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#1B89A1}"
                    "QHeaderView::section,QTableCornerButton:section{ \
            padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #454545,stop:1 #323232); }"
"QTableWidget{background-color:rgb(45,45,50);border:none;}");

        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Restore white side

        ui->centralwidget->setStyleSheet("color: rgb(240,240,240);\
                                             background-color: rgb(45,45,45);");

        ui->menubar->setStyleSheet("background-color: rgb(45,45,45);");
        ui->statusbar->setStyleSheet("background-color: rgb(45,45,45);");

        set_all_button_stylesheet("background-color: rgb(55,55,55);");
    }
}

void MainWindowAdmin::set_all_button_stylesheet(const QString& stylesheet)
{
    ui->quitButton->setStyleSheet(stylesheet);

    ui->addButton->setStyleSheet(stylesheet);
    ui->deleteButton->setStyleSheet(stylesheet);

    ui->pair_deleteButton->setStyleSheet(stylesheet);

    ui->food_deleteButton->setStyleSheet(stylesheet);
    ui->food_addButton->setStyleSheet(stylesheet);

    ui->user_deleteButton->setStyleSheet(stylesheet);

    ui->user_id_resetButton->setStyleSheet(stylesheet);
    ui->user_table_clearButton->setStyleSheet(stylesheet);
    ui->user_table_createButton->setStyleSheet(stylesheet);

    ui->reservation_id_resetButton->setStyleSheet(stylesheet);
    ui->reservation_table_clearButton->setStyleSheet(stylesheet);
    ui->reservation_table_createButton->setStyleSheet(stylesheet);

    ui->administrator_id_resetButton->setStyleSheet(stylesheet);
    ui->administrator_table_clearButton->setStyleSheet(stylesheet);
    ui->administrator_table_createButton->setStyleSheet(stylesheet);

    ui->food_id_resetButton->setStyleSheet(stylesheet);
    ui->food_table_clearButton->setStyleSheet(stylesheet);
    ui->food_table_createButton->setStyleSheet(stylesheet);

    ui->pair_id_resetButton->setStyleSheet(stylesheet);
    ui->pair_table_clearButton->setStyleSheet(stylesheet);
    ui->pair_table_createButton->setStyleSheet(stylesheet);
}

void MainWindowAdmin::set_all_table_stylesheet(const QString& stylesheet)
{
    ui->reservation_table->setStyleSheet(stylesheet);
    ui->user_table->setStyleSheet(stylesheet);
    ui->food_table->setStyleSheet(stylesheet);
    ui->pair_table->setStyleSheet(stylesheet);
}

// Write log to page Log and file log.txt

void MainWindowAdmin::log(const std::string& s)
{
    std::string ss = str_time()+" "+s;
    QString qs = QString::fromStdString(ss);
    ui->textBrowser->append(qs);
    log_file << ss << std::endl;
}

void MainWindowAdmin::log()
{
    std::string s = str_time()+" "+"Done";
    QString qs = QString::fromStdString(s);
    ui->textBrowser->append(qs);
    log_file << s << std::endl;
}

// -----------------------------------------------------SLOTS-----------------------------------------------------

// Global

void MainWindowAdmin::on_quitButton_clicked()
{
    this->close();
}

// Reservation

void MainWindowAdmin::on_deleteButton_clicked()
{
    log("on_deleteButton_clicked: Removing reservation...");
    std::cout<<"Removing reservation..."<<std::endl;
    QModelIndex cur = ui->reservation_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->reservation_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;
    db.delete_reservation(ui->reservation_table->item(row, 0)->text().toInt());
    db.delete_pair(ui->reservation_table->item(row, 0)->text().toInt());
    //Refresh
    get_reservation_list();
    //ui->reservation_table->removeRow(row);
    log();
}

void MainWindowAdmin::on_addButton_clicked()
{
    log("on_addButton_clicked: Adding reservation...");

    //Check if necessarily filled
    if (ui->table_idEdit->text().isEmpty())
    {
        ui->add_promptLabel->setText(QString::fromStdString("Please enter table ID!"));
        return;
    }
    if (ui->table_priceEdit->text().isEmpty())
    {
        ui->add_promptLabel->setText(QString::fromStdString("Please enter table price!"));
        return;
    }

    //Check all the information
    //1.Check the date
    int *year1 = new int;
    int *month1 = new int;
    int *day1 = new int;
    ui->dateEdit->date().getDate(year1, month1, day1);
    if (*year1<get_year())
    {
        ui->add_promptLabel->setText(QString::fromStdString("Please check the year!"));
        return;
    }
    if (*month1<get_month())
    {
        ui->add_promptLabel->setText(QString::fromStdString("Please check the month!"));
        return;
    }
    if (*day1<get_day())
    {
        ui->add_promptLabel->setText(QString::fromStdString("Please check the day!"));
        return;
    }
    //2.Check the time
    int begin_hour=ui->begin_timeEdit->time().hour();
    int begin_minute=ui->begin_timeEdit->time().minute();
    int end_hour=ui->end_timeEdit->time().hour();
    int end_minute=ui->end_timeEdit->time().minute();
    if (begin_hour*60+begin_minute>=end_hour*60+end_minute)
    {
        ui->add_promptLabel->setText(QString::fromStdString("Please check the time!"));
        return;
    }


    //Add the information to database
    //continue
    std::string user_name;
    user_name = (ui->usernameEdit->text().toStdString());
    duration dur;
    dur.year=*year1, dur.month=*month1, dur.day=*day1;
    dur.hour_begin=ui->begin_timeEdit->time().hour();
    dur.minute_begin=ui->begin_timeEdit->time().minute();
    dur.hour_end=ui->end_timeEdit->time().hour();
    dur.minute_end=ui->end_timeEdit->time().minute();
    db.add_reservation(user_name, dur, ui->table_typeBox->currentText().toStdString(), ui->table_idEdit->text().toInt(), ui->table_priceEdit->text().toInt());

    //Refresh
    get_reservation_list();
    set_default_date_edit();
    ui->add_promptLabel->setText(QString::fromStdString("Click Add to add a reservation"));

    log();
}

// Food Reservation

void MainWindowAdmin::on_pair_deleteButton_clicked()
{
    log("on_pair_deleteButton_clicked: Removing pair...");
    std::cout<<"Removing pair..."<<std::endl;
    QModelIndex cur = ui->pair_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->pair_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;
    db.delete_pair(db.delete_reservation(ui->pair_table->item(row, 2)->text().toInt()),db.delete_reservation(ui->pair_table->item(row, 3)->text().toInt()));
    //Refresh
    get_food_reservation_list();
    //ui->pair_table->removeRow(row);
    log();
}

// Food

void MainWindowAdmin::on_food_deleteButton_clicked()
{
    log("on_food_deleteButton_clicked: Removing food...");

    std::cout<<"Removing food..."<<std::endl;
    QModelIndex cur = ui->food_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->food_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;
    db.delete_food(ui->food_table->item(row,0)->text().toInt());
    //Refresh
    get_food_list();
    //ui->food_list->removeRow(row);

    log();
}

void MainWindowAdmin::on_food_addButton_clicked()
{
    log("on_food_addButton_clicked: Adding food...");

    //Check if necessarily filled
    if (ui->foodnameEdit->text().isEmpty())
    {
        ui->add_food_promptLabel->setText(QString::fromStdString("Please enter food name!"));
        return;
    }
    if (ui->foodpriceEdit->text().isEmpty())
    {
        ui->add_food_promptLabel->setText(QString::fromStdString("Please enter food price!"));
        return;
    }
    if (ui->fooddescriptionEdit->text().isEmpty())
    {
        ui->add_food_promptLabel->setText(QString::fromStdString("Please enter food description!"));
        return;
    }

    //Check all the information
    if (db.check_exist(ui->foodnameEdit->text().toStdString(),"food"))
    {
        ui->add_food_promptLabel->setText(QString::fromStdString("Food exists!"));
        return;
    }

    //Add the information to database
    db.add_food(ui->foodnameEdit->text().toStdString(), ui->foodpriceEdit->text().toInt(), ui->fooddescriptionEdit->text().toStdString());

    //Refresh
    get_food_list();
    ui->add_food_promptLabel->setText(QString::fromStdString("Click Add to add food"));

    log();
}

// User

void MainWindowAdmin::on_user_deleteButton_clicked()
{
    log("on_user_deleteButton_clicked: Removing user...");

    std::cout<<"Removing user..."<<std::endl;
    QModelIndex cur = ui->user_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->user_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;
    db.delete_user(ui->user_table->item(row, 0)->text().toInt());
    //Refresh
    get_user_list();
    //ui->user_list->removeRow(row);

    log();
}

// Other

void MainWindowAdmin::on_reservation_id_resetButton_clicked()
{
    log("on_reservation_id_resetButton_clicked: Resetting reservation ID...");
    db.reset_reservation_id();
    get_reservation_list();
    log();
}

void MainWindowAdmin::on_reservation_table_clearButton_clicked()
{
    log("on_reservation_table_clearButton_clicked: Clearing reservation table...");
    db.clear_reservation_table();
    get_reservation_list();
    log();
}

void MainWindowAdmin::on_reservation_table_createButton_clicked()
{
    log("on_reservation_table_createButton_clicked: Creating reservation table...");
    db.create_reservation_table();
    log();
}


void MainWindowAdmin::on_user_id_resetButton_clicked()
{
    log("on_user_id_resetButton_clicked: Resetting user ID...");
    db.reset_user_id();
    get_user_list();
    log();
}

void MainWindowAdmin::on_user_table_clearButton_clicked()
{
    log("on_user_table_clearButton_clicked: Clearing user table...");
    db.clear_user_table();
    get_user_list();
    log();
}

void MainWindowAdmin::on_user_table_createButton_clicked()
{
    log("on_user_table_createButton_clicked: Creating user table...");
    db.create_user_table();
    log();
}


void MainWindowAdmin::on_administrator_id_resetButton_clicked()
{
    log("on_administrator_id_resetButton_clicked: Resetting administrator ID...");
    db.reset_administrator_id();
    log();
}

void MainWindowAdmin::on_administrator_table_clearButton_clicked()
{
    log("on_administrator_table_clearButton_clicked: Clearing administrator table...");
    db.clear_administrator_table();
    log();
}

void MainWindowAdmin::on_administrator_table_createButton_clicked()
{

    log("on_administrator_table_createButton_clicked: Creating administrator table...");
    db.create_administrator_table();
    log();
}


void MainWindowAdmin::on_food_id_resetButton_clicked()
{
    db.reset_food_id();
}

void MainWindowAdmin::on_food_table_clearButton_clicked()
{
    db.clear_food_table();
}

void MainWindowAdmin::on_food_table_createButton_clicked()
{
    db.create_food_table();
}


void MainWindowAdmin::on_pair_id_resetButton_clicked()
{
    db.reset_pair_id();
}

void MainWindowAdmin::on_pair_table_clearButton_clicked()
{
    db.clear_pair_table();
}

void MainWindowAdmin::on_pair_table_createButton_clicked()
{
    db.create_pair_table();
}

// ELSE

void MainWindowAdmin::on_theme_selectBox_currentIndexChanged(int index)
{
    set_theme(ui->theme_selectBox->currentText().toStdString());
}

void MainWindowAdmin::on_tabWidget_tabBarClicked(int index)
{
    switch (index)
    {
    case 0:
    {
        get_reservation_list();
        break;
    }
    case 1:
    {
        get_food_reservation_list();
        break;
    }
    case 2:
    {
        get_food_list();
        break;
    }
    case 3:
    {
        get_user_list();
        break;
    }
    default:
        break;
    }
}

