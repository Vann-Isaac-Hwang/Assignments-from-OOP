#include "form.h"
#include "ui_form.h"

#include <iostream>

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked, this, &Form::on_cancelButton_clicked);
    connect(ui->upButton, &QPushButton::clicked, this, &Form::on_upButton_clicked);
    connect(ui->downButton, &QPushButton::clicked, this, &Form::on_downButton_clicked);

}

Form::~Form()
{
    delete ui;
}

int Form::take_sign()
{
    int temp;
    temp=sign;
    sign=0;
    return temp;
}

void Form::on_cancelButton_clicked()
{
    this->close();
}
void Form::on_upButton_clicked()
{
    sign=1;
}
void Form::on_downButton_clicked()
{
    sign=2;
}

void Form::set_sen(std::string str)
{
    sen=str;
}

void Form::show_text()
{
    ui->label->setText(QString::fromStdString(sen));
}
