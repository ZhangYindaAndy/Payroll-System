#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T20:32:22
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Payroll
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mysql.cpp \
    employee.cpp \
    login.cpp \
    paymentmethed.cpp \
    administrator.cpp \
    maintainemployeeinfo.cpp \
    addemp.cpp \
    delemp.cpp \
    updemp.cpp \
    timecard.cpp \
    purchaseorder.cpp \
    addorder.cpp \
    updorder.cpp \
    delorder.cpp \
    empreport.cpp \
    admreport.cpp

HEADERS  += mainwindow.h \
    mysql.h \
    employee.h \
    login.h \
    paymentmethed.h \
    administrator.h \
    maintainemployeeinfo.h \
    addemp.h \
    delemp.h \
    updemp.h \
    timecard.h \
    purchaseorder.h \
    addorder.h \
    updorder.h \
    delorder.h \
    empreport.h \
    admreport.h

FORMS    += mainwindow.ui \
    login.ui \
    paymentmethed.ui \
    administrator.ui \
    maintainemployeeinfo.ui \
    addemp.ui \
    delemp.ui \
    updemp.ui \
    timecard.ui \
    purchaseorder.ui \
    addorder.ui \
    updorder.ui \
    delorder.ui \
    empreport.ui \
    admreport.ui
