#include "logindlg.h"
#include "ui_logindlg.h"
#include <QString>
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDebug>

Logindlg::Logindlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Logindlg)
{
    ui->setupUi(this);
}

Logindlg::~Logindlg()
{
    delete ui;
}

void Logindlg::on_confirmButton_clicked()
{
    QString str1, str2;
    std::string a, pw;
    //get information
    str1 = ui->UsernameEdit->text();
    a = str1.toStdString();
    str2 = ui->PasswordEdit->text();
    pw = str2.toStdString();
    if (str1.isEmpty())
    {
        std::cout<<"Please don't leave blank."<<std::endl;
        ui->promptlabel->setText("Please don't leave blank.");
        return;
    }
    //Username & Password judge
    std::ifstream infile;
    infile.open("StudentData.txt",std::ios::in);
    if (!infile.is_open())
    {
        std::cout<<"cannot open the StudentData file"<<std::endl;
    }
    char pasw[64];
    std::string buf, pas;
    int f=0, fp, id;
    while (getline(infile,buf))
    {
        int i=0;
        f=1, id=0;
        while (buf[i]!=' ')
        {
            if (buf[i]!=str1[i])
            {
                f=0;
                break;
            }
            i++;
        }
        if (str1.length()!=i) f=0;


        i++;
        while (buf[i]!=' ')
        {
            id*=10;
            id+=buf[i]-'0';
            i++;
        }
        i++;
        int j=0;
        while (buf[i]!=' '&&buf[i]!='\0'&&buf[i]!='\n')
        {
            pasw[j++]=buf[i];
            i++;
        }
        pasw[j]='\0';
        pas=pasw;

        if (f==1) break;
    }
    if (f==0)
    {
        std::cout<<"User not found"<<std::endl;
        ui->promptlabel->setText("User not found.");
    }
    if (pas==pw) fp=1;
    else
    {
        fp=0;
        std::cout<<"Wrong password"<<std::endl;
        if (f==1)
            ui->promptlabel->setText("Wrong password.");
    }
    infile.close();
    if (f==1&&fp==1)
    {
        logged_flag=1;
        logged_user=a;
        logged_user_id=id;
        std::cout<<"Successfully logged in."<<std::endl;
        sign=1;
        this->close();
    }
}

int Logindlg::get_sign()
{
    return sign;
}

void Logindlg::set_sign()
{
    sign=0;
}

void Logindlg::on_cancelButton_clicked()
{
    this->close();
}

int Logindlg::get_logged_flag()
{

    return logged_flag;
}

std::string Logindlg::get_logged_user()
{
    return logged_user;
}

int Logindlg::get_logged_user_id()
{
    return logged_user_id;
}
