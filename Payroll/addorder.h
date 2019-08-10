#ifndef ADDORDER_H
#define ADDORDER_H

#include <QDialog>

namespace Ui {
class AddOrder;
}

class AddOrder : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrder(QWidget *parent = 0);
    ~AddOrder();
    void setUserId(int);
public slots:
    void submitOrder();

private:
    Ui::AddOrder *ui;
    int UserId;
};

#endif // ADDORDER_H
