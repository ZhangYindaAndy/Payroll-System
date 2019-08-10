#include "purchaseorder.h"
#include "ui_purchaseorder.h"

#include "addorder.h"
#include "updorder.h"
#include "delorder.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>
#include <QInputDialog>

PurchaseOrder::PurchaseOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseOrder)
{
    ui->setupUi(this);

    connect(ui->buttonCreate, SIGNAL(clicked()), this, SLOT(createOrder()));
    connect(ui->buttonUpdate, SIGNAL(clicked()), this, SLOT(updateOrder()));
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteOrder()));
}

PurchaseOrder::~PurchaseOrder()
{
    delete ui;
}
void PurchaseOrder::setUserId(int userid)
{
    UserId = userid;
}

void PurchaseOrder::createOrder()
{
    AddOrder *o = new AddOrder(this);
    o->setUserId(UserId);
    o->exec();
}

void PurchaseOrder::updateOrder()
{
    bool ok = false;
    int OrderId = QInputDialog::getText(this,
                       tr( "purchase Order ID" ),
                       tr( "Please enter purchase Order ID" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();

    QSqlQuery query;
    query.prepare("select userid from purchase_order where order_id = ?");
    query.addBindValue(OrderId);
    query.exec();
    int pexist = 0; //任务存在标识
    int userid = 0;
    QSqlRecord rec = query.record();

    while(query.next())
    {
        rec = query.record();
        userid = query.value(rec.indexOf("userid")).toInt();
        pexist = 1;
    }

    if(!pexist)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid purchase order id",QMessageBox::Ok,this);
        msg.exec();
        return;
    }
    if(userid != UserId)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"This is not your purchase order",QMessageBox::Ok,this);
        msg.exec();
        return;
    }

    UpdOrder *o = new UpdOrder(this);
    o->setOrder(OrderId);
    o->exec();
    QDialog::accept();

}

void PurchaseOrder::deleteOrder()
{
    bool ok = false;
    int OrderId = QInputDialog::getText(this,
                       tr( "purchase Order ID" ),
                       tr( "Please enter purchase Order ID" ),
                       QLineEdit::Normal, QString::null, &ok).toInt();

    QSqlQuery query;
    query.prepare("select userid from purchase_order where order_id = ?");
    query.addBindValue(OrderId);
    query.exec();
    int pexist = 0; //任务存在标识
    int userid = 0;
    QSqlRecord rec = query.record();

    while(query.next())
    {
        rec = query.record();
        userid = query.value(rec.indexOf("userid")).toInt();
        pexist = 1;
    }

    if(!pexist)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"invalid purchase order id",QMessageBox::Ok,this);
        msg.exec();
        return;
    }
    if(userid != UserId)
    {
        QMessageBox msg(QMessageBox::Information,windowTitle(),"This is not your purchase order",QMessageBox::Ok,this);
        msg.exec();
        return;
    }


    DelOrder *o = new DelOrder(this);
    o->setOrder(OrderId);
    o->exec();
    QDialog::accept();
}
