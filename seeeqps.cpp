#include "seeeqps.h"
#include "ui_seeeqps.h"
#include "config.h"
#include <QLabel>
seeeqps::seeeqps(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seeeqps)
{
    ui->setupUi(this);
}

seeeqps::~seeeqps()
{
    delete ui;
}
void seeeqps::rcv_seeeqps()
{
    this->show();
}

void seeeqps::on_pb_read_clicked()
{
    ui->tw->setRowCount(512);
    //print
    for(int i=0;i<512;i++)
    {
        if(eqps[i].name.isEmpty())break;
        QLabel *lb;
        lb=new QLabel;
        lb->setText(eqps[i].name);
        ui->tw->setCellWidget(i,0,lb);
    }
    ui->tw->resizeColumnsToContents();
}
