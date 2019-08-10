#include "empreport.h"
#include "ui_empreport.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

EmpReport::EmpReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmpReport)
{
    ui->setupUi(this);
    connect(ui->buttonProject, SIGNAL(clicked()), this, SLOT(getProjectHour()));
    connect(ui->buttonYear, SIGNAL(clicked()), this, SLOT(getYearPay()));
    connect(ui->buttonVacation, SIGNAL(clicked()), this, SLOT(getVacation()));
    connect(ui->buttonHour, SIGNAL(clicked()), this, SLOT(getTotalHour()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveText()));
}

EmpReport::~EmpReport()
{
    delete ui;
}

void EmpReport::setUserId(int userid)
{
    UserId = userid;
}

void EmpReport::getProjectHour()
{
    ui->textEdit->setText("Here are availiable charge number:");
    int beginDate = ui->lineEditBegin->text().toInt();
    int endDate = ui->lineEditEnd->text().toInt();

    QSqlQuery query;
    query.exec("select * from project_management");

    QSqlRecord rec = query.record();
    while(query.next())
    {
        rec = query.record();
        ui->textEdit->append(query.value(rec.indexOf("charge_number")).toString());
    }

    bool ok = false;
    int chargeNumber = QInputDialog::getText(this,
                       tr( "charge number" ),
                       tr( "Please enter a charge number" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();

    query.prepare("select * from project_management where charge_number = ?");
    query.addBindValue(chargeNumber);
    query.exec();
    rec = query.record();
    int nexist = 0;
    while(query.next())
    {
        rec = query.record();
        nexist = 1;
    }
    if(!nexist)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid charge number",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    ui->textEdit->setText("Here is your total workload for the given project:");

    query.prepare("select workload, start_time, end_time from timecard where userid = ? and charge_number = ?");
    query.addBindValue(UserId);
    query.addBindValue(chargeNumber);
    query.exec();
    rec = query.record();
    int totalWorkload = 0;
    while(query.next())
    {
        rec = query.record();
        if(beginDate <=  query.value(rec.indexOf("start_time")).toInt() && endDate >=  query.value(rec.indexOf("end_time")).toInt())
            totalWorkload += query.value(rec.indexOf("workload")).toInt();
    }
    ui->textEdit->append(QString::number(totalWorkload));

}

void EmpReport::getYearPay()
{
    QSqlQuery query;
    ui->textEdit->setText("Here is your total wage year to date");
    query.prepare("select total_wage from user where userid = ?");
    query.addBindValue(UserId);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next())
    {
        rec = query.record();
        ui->textEdit->append(query.value(rec.indexOf("total_wage")).toString());
    }
}

void EmpReport::getVacation()
{
    ui->textEdit->setText("Here is your remaining vacation");
    int beginDate = ui->lineEditBegin->text().toInt();
    int endDate = ui->lineEditEnd->text().toInt();
    ui->textEdit->append(QString::number((endDate - beginDate)* 2 / 7));
}

void EmpReport::getTotalHour()
{
    ui->textEdit->setText("Here is your total work hours");
    int beginDate = ui->lineEditBegin->text().toInt();
    int endDate = ui->lineEditEnd->text().toInt();
    QSqlQuery query;
    query.prepare("select workload, start_time, end_time from timecard where userid = ?");
    query.addBindValue(UserId);
    query.exec();
    QSqlRecord rec = query.record();
    int totalWorkload = 0;
    while(query.next())
    {
        rec = query.record();
        if(beginDate <=  query.value(rec.indexOf("start_time")).toInt() && endDate >=  query.value(rec.indexOf("end_time")).toInt())
            totalWorkload += query.value(rec.indexOf("workload")).toInt();
    }
    ui->textEdit->append(QString::number(totalWorkload));

}

void EmpReport::saveText()
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



