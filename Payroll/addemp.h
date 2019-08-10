#ifndef ADDEMP_H
#define ADDEMP_H

#include <QDialog>


namespace Ui {
class AddEmp;
}

class AddEmp : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmp(QWidget *parent = 0);
    ~AddEmp();

public slots:
    void submitUser();

private:
    Ui::AddEmp *ui;
};

#endif // ADDEMP_H
