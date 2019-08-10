#include "mainwindow.h"
#include "login.h"
#include "mysql.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Mysql m;

    QApplication a(argc, argv);
    Login *l = new Login();
    l->show();

    return a.exec();
}
