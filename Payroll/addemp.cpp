#include "addemp.h"
#include "ui_addemp.h"

#include <QtSql>
#include <QsqlDatabase>


AddEmp::AddEmp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmp)
{
    ui->setupUi(this);

    connect(ui->buttonSubmit, SIGNAL(clicked()), this, SLOT(submitUser()));
}

AddEmp::~AddEmp()
{
    delete ui;
}


void AddEmp::submitUser()
{
    QSqlQuery query;
    //获取下一个userid
    query.exec("select userid_next from idnext");
    QSqlRecord rec = query.record();
    int userId = 0;
    while(query.next())
    {
        rec = query.record();
        userId = query.value(rec.indexOf("userid_next")).toInt();
    }
    query.prepare("update idnext set userid_next = ?");
    query.addBindValue(userId + 1);
    query.exec();

    query.prepare("insert into user (username, level, password, userid, userexist, total_wage, "
                  "employee_name, mail_address, bank_name, account_number, hour_rate, com_rate, flat_salary, hour_limit, payment_method, timecard_submit, deduction) "
                  "values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    query.addBindValue(ui->lineEditUserName->text());
    query.addBindValue(ui->lineEditEmployeeType->text());
    query.addBindValue(ui->lineEditPassword->text());
    query.addBindValue(userId);//userid
    query.addBindValue(1);//userexist
    query.addBindValue(0);//total_wage
    query.addBindValue(ui->lineEditEmployeeName->text());
    query.addBindValue(ui->lineEditMailAddress->text());
    query.addBindValue("NULL");//bank_name
    query.addBindValue("NULL");//account_number
    query.addBindValue(ui->lineEditHourRate->text());
    query.addBindValue(ui->lineEditCommRate->text());
    query.addBindValue(ui->lineEditSalary->text());
    query.addBindValue(ui->lineEditHourLimit->text());
    query.addBindValue(3); //payment_method
    query.addBindValue(0); //timecard_submit
    query.addBindValue(ui->lineEditDeduction->text()); //deduction

    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "insert failure：" << lastError.driverText() << lastError.databaseText();return;
    }
    QDialog::accept();
}
