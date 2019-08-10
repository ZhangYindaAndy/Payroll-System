#ifndef DELEMP_H
#define DELEMP_H

#include <QDialog>


namespace Ui {
class DelEmp;
}

class DelEmp : public QDialog
{
    Q_OBJECT

public:
    explicit DelEmp(QWidget *parent = 0);
    ~DelEmp();
    void setUser(int);

public slots:
    void deleteUser();

private:
    Ui::DelEmp *ui;
    int UserId;
};

#endif // DELEMP_H
