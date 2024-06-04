#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
    , db("data.db")
{
    ui->setupUi(this);

    this->setWindowTitle("Menu");

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
    ui->food_table->setColumnWidth(2,160);
    ui->food_table->setColumnWidth(3,70);
    ui->food_table->setColumnWidth(4,60);
    ui->food_table->setColumnWidth(5,60);
    ui->food_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Set up this food table
    ui->this_food_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->this_food_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->this_food_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->this_food_table->setShowGrid(true);
    //QFont Font = ui->this_food_table->horizontalHeader()->font();
    //Font.setBold(true);
    //ui->this_food_table->horizontalHeader()->setDefaultSectionSize(80);
    ui->this_food_table->setColumnWidth(0,60);
    ui->this_food_table->setColumnWidth(1,80);
    ui->this_food_table->setColumnWidth(2,160);
    ui->this_food_table->setColumnWidth(3,70);
    ui->this_food_table->setColumnWidth(4,60);
    ui->this_food_table->setColumnWidth(5,60);
    ui->this_food_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

menu::~menu()
{
    delete ui;
}

void menu::set_reservation_id(int reservation_id)
{
    menu::reservation_id = reservation_id;
}

void menu::get_food_list()
{
    ui->label->setText("Reservation ID: "+QString::number(reservation_id));

    //clear food table
    std::cout<<"\nClearing food table..."<<std::endl;
    ui->food_table->clearContents();
    ui->food_table->setRowCount(0);

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
}

void menu::get_this_food_list()
{
    //clear this food table
    std::cout<<"\nClearing this food table..."<<std::endl;
    ui->this_food_table->clearContents();
    ui->this_food_table->setRowCount(0);

    int total_price = db.get_reservation_info(reservation_id).deposit;
    //Fetch this food information
    std::cout<<"\nFetching this food information..."<<std::endl;
    //std::cout<<"TEST: The length of table pair:"<<db.get_table_length("pair")<<std::endl;// TEST
    int table_length = db.get_table_length("pair");
    for (int i=0,j=0;i<table_length;i++)
    {
        if (db.getPairInfo(i).reservation_id!=reservation_id) continue;

        //Insert data
        QTableWidgetItem *check=new QTableWidgetItem(QString::number(j));
        check->setCheckState(Qt::Unchecked);  //Set check box
        ui->this_food_table->insertRow(j);
        check->setText(QString::number(j));  //display order
        //ui->coursetable->setItem(i,0,check); //insert check box

        ui->this_food_table->setItem(j,0,new QTableWidgetItem(QString::number(db.getPairInfo(i).id)));
        ui->this_food_table->setItem(j,1,new QTableWidgetItem(QString::number(db.getPairInfo(i).food_id)));
        ui->this_food_table->setItem(j,2,new QTableWidgetItem(QString::fromStdString(db.get_food_info(db.getPairInfo(i).food_id).name)));
        ui->this_food_table->setItem(j,3,new QTableWidgetItem(QString::number(db.get_food_info(db.getPairInfo(i).food_id).price)));
        ui->this_food_table->setItem(j,4,new QTableWidgetItem(QString::fromStdString(db.get_food_info(db.getPairInfo(i).food_id).description)));
        total_price += db.get_food_info(db.getPairInfo(i).food_id).price;
    }

    ui->pricelcdNumber->display(total_price);
    ui->depositlcdNumber->display(((double)total_price)*DEPOSIT_RATE);
}

void menu::on_doneButton_clicked()
{
    this->close();
}

void menu::on_addButton_clicked()
{
    std::cout<<"Adding new food..."<<std::endl;

    QModelIndex cur = ui->food_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->food_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;

    int target_food_id = ui->food_table->item(row,0)->text().toInt();
    db.add_pair(reservation_id,target_food_id);

    get_this_food_list();
}

void menu::on_removeButton_clicked()
{
    std::cout<<"Deleting food..."<<std::endl;

    QModelIndex cur = ui->this_food_table->selectionModel()->currentIndex();
    int row = cur.row();
    if (row<0) return;
    if (ui->this_food_table->hasFocus()) return;
    std::cout<<"Row "<<row<<std::endl;

    int cor_pair_id = ui->this_food_table->item(row,0)->text().toInt();
    db.delete_pair_by_id(cor_pair_id);

    get_this_food_list();
}

void menu::set_theme(const std::string& s)
{
    if (s=="Default")
    {
        ui->this_food_table->setStyleSheet("");
        ui->food_table->setStyleSheet("");

        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");
        this->setStyleSheet("color: rgb(45,45,45);\
                                             background-color: #f5f5f5;");
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

        set_all_button_stylesheet("background-color: rgb(55,55,55);");

        set_all_label_stylesheet("background-color: transparent;");

        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(45,45,45);");
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

        set_all_button_stylesheet("background-color: rgb(55,55,55);");

        set_all_label_stylesheet("background-color: transparent;");

        this->setStyleSheet("color: rgb(240,240,240);\
                                             background: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #00BFFF,stop:1 #6A5ACD);");
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

        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(60,60,60);}"
                                  "QPushButton{background-color:rgb(80,80,80);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");

        set_all_label_stylesheet("background-color: transparent;");

        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(45,45,45);");
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

        set_all_button_stylesheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                  "QPushButton{background-color:rgb(180,180,180);}"
                                  "QPushButton{border:0px}"
                                  "QPushButton{border-radius:5px}"
                                  "QPushButton{padding:2px 4px}");

        set_all_label_stylesheet("background-color: transparent;");

        this->setStyleSheet("color: rgb(45,45,45);\
                                background-color: #f5f5f5;");
    }
}

void menu::set_all_button_stylesheet(const QString& stylesheet)
{
    ui->addButton->setStyleSheet(stylesheet);
    ui->doneButton->setStyleSheet(stylesheet);
    ui->removeButton->setStyleSheet(stylesheet);
}

void menu::set_all_table_stylesheet(const QString& stylesheet)
{
    ui->this_food_table->setStyleSheet(stylesheet);
    ui->food_table->setStyleSheet(stylesheet);
}

void menu::set_all_label_stylesheet(const QString& stylesheet)
{
    ui->label->setStyleSheet(stylesheet);
    ui->label_2->setStyleSheet(stylesheet);
}
