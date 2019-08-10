#include "delorder.h"
#include "ui_delorder.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>

DelOrder::DelOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelOrder)
{
    ui->setupUi(this);
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteOrder()));
}

DelOrder::~DelOrder()
{
    delete ui;
}

void DelOrder::deleteOrder()
{
    QSqlQuery query;
    query.prepare("delete from purchase_order where order_id = :uid");
    query.bindValue(":uid",OrderId);
    QMessageBox msg(QMessageBox::Information,windowTitle(),"Do you want to delete this purchase order?",QMessageBox::Ok|QMessageBox::No,this);
    if(msg.exec() == QMessageBox::Ok)
    {
        query.exec();
        QDialog::accept();
    }
}

void DelOrder::setOrder(int orderid)
{
    OrderId = orderid;
    QSqlQuery query;
    query.prepare("select * from purchase_order where order_id = :uid");
    query.bindValue(":uid",orderid);   // 绑定数据到指定的位置
    query.exec();
    QSqlRecord rec = query.record();

    while(query.next())
    {
        rec = query.record();

        ui->lineEditCustomer->setText(query.value(rec.indexOf("customer_name")).toString());
        ui->lineEditProduct->setText(query.value(rec.indexOf("product")).toString());
        ui->lineEditDate->setText(query.value(rec.indexOf("date")).toString());

    }
}
