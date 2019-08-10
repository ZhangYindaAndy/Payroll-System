#ifndef ADMREPORT_H
#define ADMREPORT_H

#include <QDialog>

namespace Ui {
class AdmReport;
}

class AdmReport : public QDialog
{
    Q_OBJECT

public:
    explicit AdmReport(QWidget *parent = 0);
    ~AdmReport();

public slots:
    void getYearPay();
    void getTotalHour();
    void saveText();

private:
    Ui::AdmReport *ui;
};

#endif // ADMREPORT_H
