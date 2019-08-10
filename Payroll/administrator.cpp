#include "administrator.h"
#include "ui_administrator.h"

#include "maintainemployeeinfo.h"
#include "admreport.h"

Administrator::Administrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Administrator)
{
    ui->setupUi(this);

    connect(ui->buttonMaintain, SIGNAL(clicked()), this, SLOT(maintainInfo()));
    connect(ui->buttonCreateReport, SIGNAL(clicked()), this, SLOT(createReport()));
}

Administrator::~Administrator()
{
    delete ui;
}


void Administrator::maintainInfo()
{
    maintainEmployeeInfo *m = new maintainEmployeeInfo(this);
    m->exec();
}

void Administrator::createReport()
{
    AdmReport *r = new AdmReport(this);
    r->exec();
}
