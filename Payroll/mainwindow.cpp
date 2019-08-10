#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "paymentmethed.h"
#include "timecard.h"
#include "purchaseorder.h"
#include "empreport.h"

#include <QMessageBox>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    user = new Employee();
    ui->setupUi(this);

    connect(ui->buttonPayment, SIGNAL(clicked()), this, SLOT(selectPaymentMethod()));
    connect(ui->buttonMaintainCard, SIGNAL(clicked()), this, SLOT(maintainTimecard()));
    connect(ui->buttonMaintainOrder, SIGNAL(clicked()), this, SLOT(maintainPurchaseOrder()));
    connect(ui->buttonCreateReport, SIGNAL(clicked()), this, SLOT(createEmployeeReport()));
    connect(ui->buttonSubmit, SIGNAL(clicked()), this, SLOT(submitInfo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectPaymentMethod()
{
    PaymentMethed *p = new PaymentMethed(this);
    p->exec();
    if(p->method == 1)
    {
        user->mailAddress = p->mailAddress;
        user->payMethod = p->method;
        user->bankName = QString::null;
        user->accountNumber = QString::null;
    }
    else if(p->method == 2)
    {
        user->mailAddress = QString::null;
        user->payMethod = p->method;
        user->bankName = p->bankName;
        user->accountNumber = p->accountNumber;
    }
    else if(p->method == 3)
    {
        user->mailAddress = QString::null;
        user->payMethod = p->method;
        user->bankName = QString::null;
        user->accountNumber = QString::null;
    }

}

void MainWindow::maintainTimecard()
{
    Timecard *c = new Timecard(this);
    c->setUserId(user->UserId);
    c->exec();

}

void MainWindow::maintainPurchaseOrder()
{
    if(user->level != 3) //如果不是commission不执行
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"you are not the commission employee",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    PurchaseOrder *p = new PurchaseOrder(this);
    p->setUserId(user->UserId);
    p->exec();
}

void MainWindow::createEmployeeReport()
{
    EmpReport *r = new EmpReport(this);
    r->setUserId(user->UserId);
    r->exec();
}

void MainWindow::submitInfo()
{
    QSqlQuery query;
    query.prepare("update user set mail_address = ?, bank_name = ?, account_number = ?, payment_method = ? where username = ?");
    query.addBindValue(user->mailAddress);
    query.addBindValue(user->bankName);
    query.addBindValue(user->accountNumber);
    query.addBindValue(user->payMethod);
    query.addBindValue(user->userName);   // 绑定数据到指定的位置
    bool success = query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << lastError.databaseText();
    }
}

void MainWindow::setUser(QString userName)
{
    user->userName = userName;
    QSqlQuery query;

    query.prepare("select * from user where username = :uname");
    query.bindValue(":uname",userName);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();

    while(query.next())
    {
        rec = query.record();

        user->employeeName = query.value(rec.indexOf("employee_name")).toString();
        user->UserId = query.value(rec.indexOf("userid")).toInt();
        user->level = query.value(rec.indexOf("level")).toInt();
        user->payMethod = query.value(rec.indexOf("payment_method")).toInt();
        user->mailAddress = query.value(rec.indexOf("address")).toString();
        user->bankName = query.value(rec.indexOf("bank_name")).toString();
        user->accountNumber = query.value(rec.indexOf("account_number")).toString();
        user->hourlyRate = query.value(rec.indexOf("hour_rate")).toFloat();
        user->commissionRate = query.value(rec.indexOf("com_rate")).toFloat();
        user->flatSalary = query.value(rec.indexOf("flat_salary")).toFloat();
        user->hourLimit = query.value(rec.indexOf("hour_limit")).toInt();
    }
}





