#include "login.h"
#include "ui_login.h"

#include "mainwindow.h"
#include "administrator.h"


#include <QMessageBox>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(login_in()));

}

Login::~Login()
{
    delete ui;
}

void Login::login_in()
{
    QString userName = ui->lineEditUserName->text();

    QSqlQuery query;
    query.prepare("select username, password, userexist from user where username = :uname");
    query.bindValue(":uname",userName);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();

    QString upassword = QString::null;
    int uexist = 0;  //如果没读到用户就是不存在

    while(query.next())
    {
        rec = query.record();
        upassword = query.value(rec.indexOf("password")).toString();
        uexist = query.value(rec.indexOf("userexist")).toInt();
    }

    if(userName == "root" && ui->lineEditPassWord->text() == upassword)
    {
        QMessageBox msg2(QMessageBox::Information,windowTitle(),"login succeed!\nWelcome Administrator!",QMessageBox::Ok,this);
        if(msg2.exec() == QMessageBox::Ok)
        {
            Administrator *a = new Administrator(this);
            this->hide();
            a->show();
        }
    }
    else if(ui->lineEditPassWord->text() == upassword && uexist == 1)
    {
        QMessageBox msg1(QMessageBox::Information,windowTitle(),"login succeed!\nWelcome to the system!",QMessageBox::Ok,this);
        if(msg1.exec() == QMessageBox::Ok)
        {
            MainWindow *w = new MainWindow(this);
            w->setUser(userName);
            this->hide();
            w->show();
        }
    }
    else
    {
        QMessageBox msg3(QMessageBox::Information,windowTitle(),"login failed",QMessageBox::Ok,this);
        msg3.exec();
    }
}
