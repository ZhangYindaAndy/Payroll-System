#ifndef UPDEMP_H
#define UPDEMP_H

#include <QDialog>

namespace Ui {
class UpdEmp;
}

class UpdEmp : public QDialog
{
    Q_OBJECT

public:
    explicit UpdEmp(QWidget *parent = 0);
    ~UpdEmp();
    void setUser(int);

public slots:
    void updateUser();

private:
    Ui::UpdEmp *ui;
    int UserId;
};

#endif // UPDEMP_H
