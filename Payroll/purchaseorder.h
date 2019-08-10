#ifndef PURCHASEORDER_H
#define PURCHASEORDER_H

#include <QDialog>

namespace Ui {
class PurchaseOrder;
}

class PurchaseOrder : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseOrder(QWidget *parent = 0);
    ~PurchaseOrder();
    void setUserId(int);

public slots:
    void createOrder();
    void updateOrder();
    void deleteOrder();

private:
    Ui::PurchaseOrder *ui;
    int UserId;
};

#endif // PURCHASEORDER_H
