#include "base.h"
#include "ui_base.h"

base::base(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::base)
{
    ui->setupUi(this);
}

base::~base()
{
    delete ui;
}
