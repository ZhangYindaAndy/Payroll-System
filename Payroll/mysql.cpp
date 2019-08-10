#include "mysql.h"
#include <QDebug>

#include <QMessageBox>

Mysql::Mysql(QObject *parent)

    :QObject(parent)
{
    dbDriver="QMYSQL";
    dbName="sp";
    userName="root";
    userPwd="0829";
    //hostName="10.151.139.189";
    hostName="192.168.3.34";
    hostPort=3306;

    if(connectDB())
        qDebug()<<"connect success";


}

bool Mysql::connectDB()

{

    QSqlDatabase db = QSqlDatabase::addDatabase(dbDriver);//添加驱动
    db.setHostName(hostName);//设置主机名
    db.setPort(hostPort);//设置端口
    db.setDatabaseName(dbName);//设置数据库名
    db.setUserName(userName);//设置用户名
    db.setPassword(userPwd);//设置用户密码

    //发送连接

    if(!db.open())
    {
        qDebug()<<"connect failed";
        qDebug() << db.lastError();
        //QMessageBox msg(QMessageBox::Information,windowTitle(),"Database not available",QMessageBox::Ok,this);
        //msg.exec();
        return false;
    }
    /*
    QSqlQuery query;
    QSqlRecord rec = query.record();
    int snamecol = rec.indexOf("password");

    while(query.next()){
            qDebug() <<  query.value(snamecol).toString();
    }
    */
    return true;


}


bool Mysql::queryDB(const QString &sql)
{
    QSqlQuery query;
    query.exec(sql);

    if(query.next()) //如果有记录则为真 否则退出判断
    {
        return true;
    }

    return false;
}






