#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QDialog>
#include <QInputDialog>
#include "mysql.h"
#include "employee.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUser(QString);

public slots:
    void selectPaymentMethod();
    void maintainTimecard();
    void createEmployeeReport();
    void maintainPurchaseOrder();
    void submitInfo();

public:
    Employee *user;

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
