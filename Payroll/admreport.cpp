#include "admreport.h"
#include "ui_admreport.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

AdmReport::AdmReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdmReport)
{
    ui->setupUi(this);

    connect(ui->buttonYear, SIGNAL(clicked()), this, SLOT(getYearPay()));
    connect(ui->buttonHour, SIGNAL(clicked()), this, SLOT(getTotalHour()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveText()));
}

AdmReport::~AdmReport()
{
    delete ui;
}

void AdmReport::getYearPay()
{
    QSqlQuery query;
    QString userName = ui->lineEditName->text();
    if(userName.isEmpty())
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"Please enter an employee name",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    query.prepare("select total_wage, userexist from user where employee_name = ?");
    query.addBindValue(userName);
    query.exec();
    QSqlRecord rec = query.record();
    int uexist = 0;
    float totalWage = 0;
    while(query.next())
    {
        rec = query.record();
        uexist = query.value(rec.indexOf("userexist")).toInt();
        totalWage = query.value(rec.indexOf("total_wage")).toFloat();
    }

    if(!uexist)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid employee name",QMessageBox::Ok,this);
        msg.exec();
        return;
    }
    else
    {
        ui->textEdit->setText("Here is employee total wage year to date");
        ui->textEdit->append(QString::number(totalWage));
    }
}

void AdmReport::getTotalHour()
{
    QString userName = ui->lineEditName->text();
    if(userName.isEmpty())
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"Please enter an employee name",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    int beginDate = ui->lineEditBegin->text().toInt();
    int endDate = ui->lineEditEnd->text().toInt();
    QSqlQuery query;
    query.prepare("select userid, userexist from user where employee_name = ?");
    query.addBindValue(userName);
    query.exec();
    int UserId = 0;
    int uexist = 0;
    QSqlRecord rec = query.record();
    while(query.next())
    {
        rec = query.record();
        UserId = query.value(rec.indexOf("userid")).toInt();
        uexist = query.value(rec.indexOf("userexist")).toInt();
    }
    if(!uexist)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid employee name",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    query.prepare("select workload, start_time, end_time from timecard where userid = ?");
    query.addBindValue(UserId);
    query.exec();
    int totalWorkload = 0;
    while(query.next())
    {
        rec = query.record();
        if(beginDate <=  query.value(rec.indexOf("start_time")).toInt() && endDate >=  query.value(rec.indexOf("end_time")).toInt())
            totalWorkload += query.value(rec.indexOf("workload")).toInt();
    }
    ui->textEdit->setText("Here is employee total work hour");
    ui->textEdit->append(QString::number(totalWorkload));

}

void AdmReport::saveText()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Plesase Select a Text File");
        return;
    }
    QFile *file=new QFile;
    file->setFileName(fileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out << ui->textEdit->toPlainText();
        out << "\n";
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Messaage","File Save Error"+file->errorString());
        return;
    }
}



