#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>
#include <QtSql>
#include <QsqlDatabase>

class Mysql: public QObject
{
public:
    Mysql(QObject *parent = 0);

    bool connectDB();
    bool queryDB(const QString &sql);

public:
    QSqlQuery query;

private:
    QString dbDriver;
    QString dbName;
    QString userName;
    QString userPwd;
    QString hostName;
    int hostPort;
};

#endif // MYSQL_H
