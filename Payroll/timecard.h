#ifndef TIMECARD_H
#define TIMECARD_H

#include <QDialog>

namespace Ui {
class Timecard;
}

class Timecard : public QDialog
{
    Q_OBJECT

public:
    explicit Timecard(QWidget *parent = 0);
    ~Timecard();
    void setUserId(int);

public slots:
    void updateTimecard();
    void submitTimecard();

private:
    Ui::Timecard *ui;
    int UserId;
};

#endif // TIMECARD_H
