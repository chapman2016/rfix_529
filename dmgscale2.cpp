#include "dmgscale2.h"
#include "ui_dmgscale2.h"

dmgscale2::dmgscale2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dmgscale2)
{
    ui->setupUi(this);
}

dmgscale2::~dmgscale2()
{
    delete ui;
}
