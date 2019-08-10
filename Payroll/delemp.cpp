#include "delemp.h"
#include "ui_delemp.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>
#include <QDebug>


DelEmp::DelEmp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelEmp)
{
    ui->setupUi(this);

    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteUser()));
}

DelEmp::~DelEmp()
{
    delete ui;
}

void DelEmp::deleteUser()
{
    QSqlQuery query;
    query.prepare("update user set userexist = 0 where userid = :uid");
    query.bindValue(":uid",UserId);
    QMessageBox msg(QMessageBox::Information,windowTitle(),"Do you want to delete this user?",QMessageBox::Ok|QMessageBox::No,this);
    if(msg.exec() == QMessageBox::Ok)
    {
        bool success = query.exec();
        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << lastError.databaseText();
        }
        QDialog::accept();
    }
}

void DelEmp::setUser(int userid)
{
    this->UserId = userid;
    QSqlQuery query;
    query.prepare("select * from user where userid = :uid");
    query.bindValue(":uid",userid);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();

    while(query.next())
    {
        rec = query.record();

        ui->lineEditUserName->setText(query.value(rec.indexOf("username")).toString());
        ui->lineEditEmployeeType->setText(query.value(rec.indexOf("level")).toString());
        ui->lineEditPassword->setText(query.value(rec.indexOf("password")).toString());
        ui->lineEditEmployeeName->setText(query.value(rec.indexOf("employee_name")).toString());
        ui->lineEditMailAddress->setText(query.value(rec.indexOf("mail_address")).toString());
        ui->lineEditHourRate->setText(query.value(rec.indexOf("hour_rate")).toString());
        ui->lineEditCommRate->setText(query.value(rec.indexOf("com_rate")).toString());
        ui->lineEditSalary->setText(query.value(rec.indexOf("flat_salary")).toString());
        ui->lineEditHourLimit->setText(query.value(rec.indexOf("hour_limit")).toString());
        ui->lineEditDeduction->setText(query.value(rec.indexOf("deduction")).toString());
    }

}
