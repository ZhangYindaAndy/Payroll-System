#include "maintainemployeeinfo.h"
#include "ui_maintainemployeeinfo.h"

#include "addemp.h"
#include "delemp.h"
#include "updemp.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QtSql>
#include <QsqlDatabase>


maintainEmployeeInfo::maintainEmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maintainEmployeeInfo)
{
    ui->setupUi(this);

    connect(ui->buttonCreate, SIGNAL(clicked()), this, SLOT(createEmployee()));
    connect(ui->buttonUpdate, SIGNAL(clicked()), this, SLOT(updateEmployee()));
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteEmployee()));
}

maintainEmployeeInfo::~maintainEmployeeInfo()
{
    delete ui;
}


void maintainEmployeeInfo::createEmployee()
{
    AddEmp *e = new AddEmp(this);
    e->exec();
}

void maintainEmployeeInfo::updateEmployee()
{
    bool ok = false;
    int userId = QInputDialog::getText(this,
                       tr( "User ID" ),
                       tr( "Please enter an User ID" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();

    QSqlQuery query;
    query.prepare("select userexist from user where userid = :uid");
    query.bindValue(":uid",userId);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();
    int uexist = 0; //用户存在标志
    while(query.next())
    {
        rec = query.record();
        uexist = query.value(rec.indexOf("userexist")).toInt();
    }


    if(ok && uexist)
    {
        UpdEmp *e = new UpdEmp(this);
        e->setUser(userId);
        e->exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"User not exist!",QMessageBox::Ok,this);
        msg.exec();
    }
}

void maintainEmployeeInfo::deleteEmployee()
{
    bool ok = false;
    int userId = QInputDialog::getText(this,
                       tr( "User Name" ),
                       tr( "Please enter an User ID" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();

    QSqlQuery query;
    query.prepare("select userexist from user where userid = :uid");
    query.bindValue(":uid",userId);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();
    int uexist = 0; //用户存在标志
    while(query.next())
    {
        rec = query.record();
        uexist = query.value(rec.indexOf("userexist")).toInt();
    }


    if(ok && uexist)
    {
        DelEmp *e = new DelEmp(this);
        e->setUser(userId);
        e->exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"User not exist!",QMessageBox::Ok,this);
        msg.exec();
    }
}







