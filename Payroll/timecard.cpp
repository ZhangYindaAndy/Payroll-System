#include "timecard.h"
#include "ui_timecard.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>
#include <QInputDialog>

Timecard::Timecard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timecard)
{
    ui->setupUi(this);

    connect(ui->buttonSubmit, SIGNAL(clicked()), this, SLOT(submitTimecard()));
    connect(ui->buttonUpdate, SIGNAL(clicked()), this, SLOT(updateTimecard()));
}

Timecard::~Timecard()
{
    delete ui;
}

void Timecard::setUserId(int userid)
{
    UserId = userid;
    ui->textEditDisplay->setPlainText("your Timecard:\n");

    QSqlQuery query;
    query.prepare("select charge_number, start_time, workload from timecard where userid = :uid");
    query.bindValue(":uid",userid);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();

    while(query.next())
    {
        rec = query.record();

        ui->textEditDisplay->append("charge number:");
        ui->textEditDisplay->append(query.value(rec.indexOf("charge_number")).toString());
        ui->textEditDisplay->append("workload(hour):");
        ui->textEditDisplay->append(query.value(rec.indexOf("workload")).toString());
        ui->textEditDisplay->append("start time:");
        ui->textEditDisplay->append(query.value(rec.indexOf("start_time")).toString());
        ui->textEditDisplay->append("\n");
    }
}


void Timecard::submitTimecard()
{
    QSqlQuery query;
    query.prepare("update timecard "
                  "set state = 2 "
                  "where userid = ? and state = 1");
    query.addBindValue(UserId);
    query.exec();

    query.prepare("update user set timecard_submit = 1 where userid = ?");
    query.addBindValue(UserId);
    query.exec();

    QDialog::accept();

}

void Timecard::updateTimecard()
{
    QSqlQuery query;
    query.prepare("select timecard_submit, hour_limit from user where userid = ?");
    query.addBindValue(UserId);
    query.exec();
    QSqlRecord rec = query.record();
    int hourLimit = 0;

    while(query.next())
    {
        rec = query.record();
        if(query.value(rec.indexOf("timecard_submit")).toInt() == 1) //用户已经submit
        {
            QMessageBox msg(QMessageBox::Information,windowTitle(),"Timecard has been submitted",QMessageBox::Ok,this);
            msg.exec();
            return;
        }
        hourLimit = query.value(rec.indexOf("hour_limit")).toInt();
    }


    bool ok = false;
    int chargeNumber = QInputDialog::getText(this,
                       tr( "charge number" ),
                       tr( "Please enter a charge number" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();

    query.prepare("select charge_number from project_management where charge_number = ?");
    query.addBindValue(chargeNumber);
    query.exec();
    int pexist = 0; //任务存在标识
    rec = query.record();

    while(query.next())
    {
        rec = query.record();
        pexist = 1;
    }

    if(!pexist)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid charge number",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    //用户继续输入所需信息
    ok = false;
    int workload = QInputDialog::getText(this,
                       tr( "Workload (hour)" ),
                       tr( "Please enter your workload" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();
    if(workload > 24 && workload <= 0)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid workload",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    ok = false;
    int startTime = QInputDialog::getText(this,
                       tr( "start time" ),
                       tr( "Please enter your start time" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();
    //判断以前的总workload+当前workload时候超过limit
    int totalWork = 0;
    query.prepare("select workload, state from timecard where userid = ?");
    query.addBindValue(UserId);
    query.exec();
    rec = query.record();
    while(query.next())
    {
        rec = query.record();
        int state = query.value(rec.indexOf("state")).toInt();
        if(state == 1 || state == 2)
            totalWork += query.value(rec.indexOf("workload")).toInt();
    }

    if(totalWork + workload > hourLimit)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"you are over worked!",QMessageBox::Ok,this);
        msg.exec();
        return;
    }


    //分配card_id
    query.exec("select cardid_next from idnext");
    rec = query.record();
    int cardId = 0;
    while(query.next())
    {
        rec = query.record();
        cardId = query.value(rec.indexOf("cardid_next")).toInt();
    }
    query.prepare("update idnext set cardid_next = ?");
    query.addBindValue(cardId + 1);
    query.exec();

    query.prepare("insert into timecard (userid, card_id, charge_number, workload, state, start_time, end_time) "
                  "values (?,?,?,?,?,?,?)");
    query.addBindValue(UserId);
    query.addBindValue(cardId); //card_id
    query.addBindValue(chargeNumber);
    query.addBindValue(workload);
    query.addBindValue(1);//state 未发布
    query.addBindValue(startTime);
    query.addBindValue(startTime + 7);//end_time

    bool success = query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << lastError.databaseText();
    }

    //把新的timecard显示出来
    ui->textEditDisplay->append("charge number:");
    ui->textEditDisplay->append(QString::number(chargeNumber));
    ui->textEditDisplay->append("workload(hour):");
    ui->textEditDisplay->append(QString::number(workload));
    ui->textEditDisplay->append("start time:");
    ui->textEditDisplay->append(QString::number(startTime));
    ui->textEditDisplay->append("\n");

}
