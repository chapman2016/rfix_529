#include "infoinput.h"
#include "ui_infoinput.h"

infoinput::infoinput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoinput)
{
    ui->setupUi(this);
}

infoinput::~infoinput()
{
    delete ui;
}
