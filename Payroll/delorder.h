#ifndef DELORDER_H
#define DELORDER_H

#include <QDialog>

namespace Ui {
class DelOrder;
}

class DelOrder : public QDialog
{
    Q_OBJECT

public:
    explicit DelOrder(QWidget *parent = 0);
    ~DelOrder();
    void setOrder(int);
public slots:
    void deleteOrder();
private:
    Ui::DelOrder *ui;
    int OrderId;
};

#endif // DELORDER_H
