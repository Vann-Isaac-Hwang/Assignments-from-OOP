#include "regi.h"
#include "ui_regi.h"
#include <iostream>

regi::regi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::regi)
    , db("data.db")
{
    ui->setupUi(this);

    //Set color
    set_theme("Default");

    //Set windows title
    this->setWindowTitle("Register");

    // Connect
    //connect(ui->cancelButton, &QPushButton::clicked, this, &regi::on_cancelButton_clicked);
    //connect(ui->confirmButton, &QPushButton::clicked, this, &regi::on_confirmButton_clicked);

}

regi::~regi()
{
    delete ui;
}

void regi::set_theme(const std::string& s)
{
    if (s=="Default")
    {
        ui->cancelButton->setStyleSheet("");
        ui->confirmButton->setStyleSheet("");
        this->setStyleSheet("");
    }
    else if (s=="BlackNBlue")
    {
        ui->cancelButton->setStyleSheet("background-color: rgb(55,55,55);");
        ui->confirmButton->setStyleSheet("background-color: rgb(55,55,55);");
        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(45,45,45);");
    }
    else if (s=="Blue")
    {
        ui->cancelButton->setStyleSheet("background-color: rgb(55,55,55);");
        ui->confirmButton->setStyleSheet("background-color: rgb(55,55,55);");
        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(30,144,255);");
    }
    else if (s=="Purple")
    {
        ui->cancelButton->setStyleSheet("background-color: rgb(55,55,55);");
        ui->confirmButton->setStyleSheet("background-color: rgb(55,55,55);");
        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(123,104,238);");
    }
}

void regi::mousePressEvent(QMouseEvent *event)//This function makes the window draggable
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

void regi::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        move(event->globalPos() - mousePoint);
        //event->accept();
    }
}

void regi::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void regi::on_cancelButton_clicked()
{
    this->close();
}

void regi::on_confirmButton_clicked()
{
    //Check if filled
    int f=1;
    if (ui->UsernameEdit->text().toStdString()=="") {f=0;}
    if (ui->NicknameEdit->text().toStdString()=="") {f=0;}
    if (ui->PhoneEdit->text().toStdString()=="") {f=0;}
    if (ui->PasswordEdit->text().toStdString()=="") {f=0;}
    if (ui->CPasswordEdit->text().toStdString()=="") {f=0;}

    //Check all the information
    QString s01 = "Username exists.";
    QString s1 = "Please fill in all the information.";
    QString s2 = "Please enter a correct phone number.";
    QString s3 = "The passwords don't match.";
    QString s4 = "Saving your informatioin...";
    std::string username=ui->UsernameEdit->text().toStdString();
    std::string nickname=ui->NicknameEdit->text().toStdString();
    std::string pn=ui->PhoneEdit->text().toStdString();
    std::string pw=ui->PasswordEdit->text().toStdString();
    std::string cpw=ui->CPasswordEdit->text().toStdString();
    if (db.check_exist(username, "user")) // Database table user check name
    {
        ui->promptlabel->setText(s01);
    }
    else if (f==0)
    {
        ui->promptlabel->setText(s1);
    }
    else if (pn.length()!=PHONE_NUMBER_LENGTH)
    {
        ui->promptlabel->setText(s2);
    }
    else if (pw!=cpw)
    {
        ui->promptlabel->setText(s3);
    }
    else
    {
        ui->promptlabel->setText(s4);
        //Store Information to database
        if (std::cout<<db.add_user(username, pw, nickname, pn))
        {
            this->close();
        }
    }
}

