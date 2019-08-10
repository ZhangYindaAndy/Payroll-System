#include "updemp.h"
#include "ui_updemp.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>

UpdEmp::UpdEmp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdEmp)
{
    ui->setupUi(this);

    connect(ui->buttonUpdate, SIGNAL(clicked()), this, SLOT(updateUser()));
}

UpdEmp::~UpdEmp()
{
    delete ui;
}

void UpdEmp::updateUser()
{
    QSqlQuery query;
    query.prepare("update user "
                  "set username = ?, level = ?, password = ?, employee_name = ?, mail_address = ?, "
                  "hour_rate = ?, com_rate = ?, flat_salary = ?, hour_limit = ?, deduction = ? "
                  "where userid = ?");
    query.addBindValue(ui->lineEditUserName->text());
    query.addBindValue(ui->lineEditEmployeeType->text().toInt());
    query.addBindValue(ui->lineEditPassword->text());
    query.addBindValue(ui->lineEditEmployeeName->text());
    query.addBindValue(ui->lineEditMailAddress->text());
    query.addBindValue(ui->lineEditHourRate->text().toFloat());
    query.addBindValue(ui->lineEditCommRate->text().toFloat());
    query.addBindValue(ui->lineEditSalary->text().toFloat());
    query.addBindValue(ui->lineEditHourLimit->text().toInt());
    query.addBindValue(ui->lineEditDeduction->text());
    query.addBindValue(UserId);
    QMessageBox msg(QMessageBox::Information,windowTitle(),"Do you want to update this user?",QMessageBox::Ok|QMessageBox::No,this);
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

void UpdEmp::setUser(int userid)
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
