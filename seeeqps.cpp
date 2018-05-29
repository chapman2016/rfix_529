#include "seeeqps.h"
#include "ui_seeeqps.h"
#include "config.h"
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QScrollBar>
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
    on_pb_read_clicked();
}

void seeeqps::on_pb_read_clicked()
{
    QString str;
    //int eqpcnt=0;
    QFile file2("eqps.txt");
    if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the eqp file!"<<endl;
    }
    int eqpcnt=0;
    while(!file2.atEnd())
    {
        QByteArray line = file2.readLine();
        str=QString(line);
        str=str.left(str.length()-1);//去除换行\n
        //qDebug()<<str;
        eqps[eqpcnt].efficiency=str.right(str.length()-str.indexOf("@")-1).toDouble();
        eqps[eqpcnt++].name=str.left(str.indexOf("@"));
    }

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

void seeeqps::on_Pb_add_eqp_clicked()
{

    QFile file("eqps.txt");
    if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
    {
          QMessageBox::warning(this,"eqp","can't open file",QMessageBox::Yes);
    }
    QTextStream in(&file);
    in<<ui->le_name->text()<<"@"<<QString::number(ui->doubleSpinBox_eft->value(),10,2)<<endl;
    //for(int i=0;i<512;i++){
    //    if(eqps[i].name.isEmpty())break;
    //    in<<eqps[i].name<<"@"<<eqps[i].efficiency<<endl;
    //}
    file.close();
}

void seeeqps::on_pb_search_clicked()
{
    QScrollBar *scrollBar =ui->tw->verticalScrollBar();
    scrollBar->setValue(0);
    if(ui->le_keyword->text().isEmpty())
    {
        //print
        ui->tw->clearContents();
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
    else
    {
        ui->tw->clearContents();
        int i2=0;
        for(int i=0;i<512;i++)
        {
            if(eqps[i].name.isEmpty())break;
            if(eqps[i].name.contains(ui->le_keyword->text()))
            {
                QLabel *lb;
                lb=new QLabel;
                lb->setText(eqps[i].name);
                ui->tw->setCellWidget(i2++,0,lb);
            }
        }
        ui->tw->resizeColumnsToContents();
    }
}
