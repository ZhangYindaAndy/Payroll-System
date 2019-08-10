#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
public:
    Employee();

public:
    QString employeeName;
    QString userName;
    int UserId;
    int level;
    int payMethod;
    QString mailAddress;
    QString bankName;
    QString accountNumber;
    float hourlyRate;
    float commissionRate;
    float flatSalary;
    int hourLimit;

};


class CommissionedEmployee: public Employee
{
public:
    CommissionedEmployee();
};

class PayrollAdministrator
{
public:
    PayrollAdministrator();
};

#endif // EMPLOYEE_H
