#ifndef UPDORDER_H
#define UPDORDER_H

#include <QDialog>

namespace Ui {
class UpdOrder;
}

class UpdOrder : public QDialog
{
    Q_OBJECT

public:
    explicit UpdOrder(QWidget *parent = 0);
    ~UpdOrder();
    void setOrder(int);
public slots:
    void updateOrder();

private:
    Ui::UpdOrder *ui;
    int OrderId;
};

#endif // UPDORDER_H
