#ifndef PAYMENTMETHED_H
#define PAYMENTMETHED_H

#include <QDialog>
#include <QInputDialog>
#include <QWidget>
#include <QString>
#include <QtSql>
#include <QsqlDatabase>

namespace Ui {
class PaymentMethed;
}

class PaymentMethed : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentMethed(QWidget *parent = 0);
    ~PaymentMethed();

public slots:
    void mMail();  //1
    void mDeposit();  //2
    void mPickup();   //3

public:
    QString mailAddress;
    QString bankName;
    QString accountNumber;
    int method;

private:
    Ui::PaymentMethed *ui;
};

#endif // PAYMENTMETHED_H
