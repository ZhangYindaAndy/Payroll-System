#include "updorder.h"
#include "ui_updorder.h"

#include <QtSql>
#include <QsqlDatabase>
#include <QMessageBox>

UpdOrder::UpdOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdOrder)
{
    ui->setupUi(this);
    connect(ui->buttonUpdate, SIGNAL(clicked()), this, SLOT(updateOrder()));
}

UpdOrder::~UpdOrder()
{
    delete ui;
}

void UpdOrder::updateOrder()
{
    QSqlQuery query;
    query.prepare("update purchase_order set "
                  "customer_name = ?, product = ?, date = ? "
                  "where order_id = ?");
    query.addBindValue(ui->lineEditCustomer->text());
    query.addBindValue(ui->lineEditProduct->text().toInt());
    query.addBindValue(ui->lineEditDate->text());
    query.addBindValue(OrderId);
    QMessageBox msg(QMessageBox::Information,windowTitle(),"Do you want to update this purchase order?",QMessageBox::Ok|QMessageBox::No,this);
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

void UpdOrder::setOrder(int orderid)
{
    this->OrderId = orderid;
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
