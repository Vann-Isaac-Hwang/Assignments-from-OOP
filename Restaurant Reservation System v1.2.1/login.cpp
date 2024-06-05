#include "login.h"
#include "ui_login.h"
#include <iostream>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
    , db("data.db")
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    //Set windows title
    this->setWindowTitle("Login");

    //Set color
    theme_name="Default";
    set_theme(theme_name);

    //connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    //connect(ui->sign_upButton, &QPushButton::clicked, this, &login::on_sign_upButton_clicked);
    //connect(ui->cancelButton, &QPushButton::clicked, this, &login::on_cancelButton_clicked);

}

login::~login()
{
    delete ui;
}

void login::on_sign_upButton_clicked()
{
    r.set_theme(theme_name);
    r.show();
}

void login::on_cancelButton_clicked()
{
    r.close();
    this->close();
}

void login::on_confirmButton_clicked()
{
    std::string username = ui->UsernameEdit->text().toStdString();
    std::string password = ui->PasswordEdit->text().toStdString();
    bool admin = ui->admin_checkBox->isChecked();
    if (username=="")
    {
        ui->promptlabel->setText("Please enter your username.");
    }
    else if (password=="")
    {
        ui->promptlabel->setText("Please enter password.");
    }
    else if ( !admin && (db.check_exist(username, "user")==false || db.verify_password(username, password, "user")==false) )
    {
        ui->promptlabel->setText("User not exist or wrong password.");
    }
    else if ( admin && (db.check_exist(username, "administrator")==false || db.verify_password(username, password, "administrator")==false) )
    {
        ui->promptlabel->setText("User not exist or wrong password.");
    }
    else
    {
        if (ui->auto_clear_checkBox->isChecked())
        {
            ui->UsernameEdit->clear();
            ui->PasswordEdit->clear();
        }
        ui->promptlabel->setText("Logging in...");

        if (admin)
        {
            wa = new MainWindowAdmin;
            wa->set_current_user(username);
            wa->show();
        }
        else
        {
            w = new MainWindow;
            w->set_current_user(username);
            w->show();
        }

        if (ui->auto_close_checkBox->isChecked())
        {
            this->close();
        }
        ui->promptlabel->setText("Please enter your username and password.");
    }
}

void login::mousePressEvent(QMouseEvent *event)//This function makes the window draggable
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

void login::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        move(event->globalPos() - mousePoint);
        //event->accept();
    }
}

void login::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void login::set_theme(const std::string& s)
{
    if (s=="Default")
    {
        ui->tabWidget->setStyleSheet("");
        ui->tabWidget->setDocumentMode(false); //Restore white side
        ui->cancelButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                        "QPushButton{background-color:rgb(180,180,180);}"
                                        "QPushButton{border:0px}"
                                        "QPushButton{border-radius:5px}"
                                        "QPushButton{padding:2px 4px}");
        ui->confirmButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(180,180,180);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        ui->sign_upButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(180,180,180);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        this->setStyleSheet("");
    }
    else if (s=="BlackNBlue")
    {
        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side
        ui->cancelButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                        "QPushButton{background-color:rgb(55,55,55);}"
                                        "QPushButton{border:0px}"
                                        "QPushButton{border-radius:5px}"
                                        "QPushButton{padding:2px 4px}");
        ui->confirmButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(55,55,55);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        ui->sign_upButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(55,55,55);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(45,45,45);");
    }
    else if (s=="Blue")
    {
        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(136,206,250);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side
        ui->cancelButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                        "QPushButton{background-color:rgb(55,55,55);}"
                                        "QPushButton{border:0px}"
                                        "QPushButton{border-radius:5px}"
                                        "QPushButton{padding:2px 4px}");
        ui->confirmButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(55,55,55);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        ui->sign_upButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(55,55,55);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(30,144,255);");
    }
    else if (s=="Purple")
    {
        ui->tabWidget->setStyleSheet("QTabWidget#tabWidget{background-color:rgb(255,0,0);}\
                                 QTabBar::tab{background-color:rgb(132,112,255);color:rgb(0,0,0);font:10pt 'Song'}\
                                 QTabBar::tab::selected{background-color:rgb(106,90,205);color:rgb(45,45,45);font:10pt 'Song'}");
        ui->tabWidget->setDocumentMode(true); //Remove white side
        ui->cancelButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                        "QPushButton{background-color:rgb(55,55,55);}"
                                        "QPushButton{border:0px}"
                                        "QPushButton{border-radius:5px}"
                                        "QPushButton{padding:2px 4px}");
        ui->confirmButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(55,55,55);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        ui->sign_upButton->setStyleSheet("QPushButton:hover{color:white;background-color:rgb(160,160,160);}"
                                         "QPushButton{background-color:rgb(55,55,55);}"
                                         "QPushButton{border:0px}"
                                         "QPushButton{border-radius:5px}"
                                         "QPushButton{padding:2px 4px}");
        this->setStyleSheet("color: rgb(240,240,240);\
                                background-color: rgb(123,104,238);");
    }
}

void login::on_theme_selectBox_currentIndexChanged(int index)
{
    theme_name = ui->theme_selectBox->currentText().toStdString();
    set_theme(theme_name);
}

