#include "addorder.h"
#include "ui_addorder.h"

#include <QtSql>
#include <QsqlDatabase>

AddOrder::AddOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrder)
{
    ui->setupUi(this);
    connect(ui->buttonSubmit, SIGNAL(clicked()), this, SLOT(submitOrder()));
}

AddOrder::~AddOrder()
{
    delete ui;
}

void AddOrder::setUserId(int userid)
{
    UserId = userid;
}


void AddOrder::submitOrder()
{
    QSqlQuery query;
    //获取下一个orderid
    query.exec("select order_next from idnext");
    QSqlRecord rec = query.record();
    int orderId = 0;
    while(query.next())
    {
        rec = query.record();
        orderId = query.value(rec.indexOf("order_next")).toInt();
    }
    query.prepare("update idnext set order_next = ?");
    query.addBindValue(orderId + 1);
    query.exec();

    query.prepare("insert into purchase_order (customer_name, product, date, userid, order_id) "
                  "values (?,?,?,?,?)");
    query.addBindValue(ui->lineEditCustomer->text());
    query.addBindValue(ui->lineEditProduct->text().toInt());
    query.addBindValue(ui->lineEditDate->text().toInt());
    query.addBindValue(UserId);
    query.addBindValue(orderId);

    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "insert failure：" << lastError.driverText() << lastError.databaseText();return;
    }
    QDialog::accept();
}
