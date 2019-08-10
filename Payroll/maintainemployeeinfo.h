#ifndef MAINTAINEMPLOYEEINFO_H
#define MAINTAINEMPLOYEEINFO_H

#include <QDialog>

namespace Ui {
class maintainEmployeeInfo;
}

class maintainEmployeeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit maintainEmployeeInfo(QWidget *parent = 0);
    ~maintainEmployeeInfo();

public slots:
    void createEmployee();
    void updateEmployee();
    void deleteEmployee();

private:
    Ui::maintainEmployeeInfo *ui;
};

#endif // MAINTAINEMPLOYEEINFO_H
