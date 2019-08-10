#include "paymentmethed.h"
#include "ui_paymentmethed.h"

PaymentMethed::PaymentMethed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentMethed)
{
    mailAddress = QString::null;
    bankName = QString::null;;
    accountNumber = QString::null;;
    method = 0;

    ui->setupUi(this);

    connect(ui->buttonMail, SIGNAL(clicked()), this, SLOT(mMail()));
    connect(ui->buttonDeposit, SIGNAL(clicked()), this, SLOT(mDeposit()));
    connect(ui->buttonPickup, SIGNAL(clicked()), this, SLOT(mPickup()));
}

PaymentMethed::~PaymentMethed()
{
    delete ui;
}

void PaymentMethed::mMail()
{
    bool ok = false;
    mailAddress = QInputDialog::getText(this,
                       tr( "Mail Address" ),
                       tr( "Please enter your mail address" ),
                       QLineEdit::Normal, QString::null, &ok);
    if(ok && !mailAddress.isEmpty())
    {
        method = 1;
    }
}

void PaymentMethed::mDeposit()
{
    bool ok = false;
    bankName = QInputDialog::getText(this,
                       tr( "Bank Name" ),
                       tr( "Please enter your Bank Name" ),
                       QLineEdit::Normal, QString::null, &ok);

    ok = false;
    accountNumber = QInputDialog::getText(this,
                       tr( "Account Number" ),
                       tr( "Please enter your Account Number" ),
                       QLineEdit::Normal, QString::null, &ok);
    if(ok && !bankName.isEmpty() && !accountNumber.isEmpty())
    {
        method = 2;
    }
}

void PaymentMethed::mPickup()
{
    method = 3;
}

