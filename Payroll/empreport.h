#ifndef EMPREPORT_H
#define EMPREPORT_H

#include <QDialog>

namespace Ui {
class EmpReport;
}

class EmpReport : public QDialog
{
    Q_OBJECT

public:
    explicit EmpReport(QWidget *parent = 0);
    ~EmpReport();
    void setUserId(int);

public slots:
    void getProjectHour();
    void getYearPay();
    void getVacation();
    void getTotalHour();
    void saveText();

private:
    Ui::EmpReport *ui;
    int UserId;
};

#endif // EMPREPORT_H
