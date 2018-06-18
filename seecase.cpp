#include "seecase.h"
#include "ui_seecase.h"
#include "config.h"
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
seeCase::seeCase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seeCase)
{
    ui->setupUi(this);


}

seeCase::~seeCase()
{
    delete ui;
}


void seeCase::rcv_seecase(QString name){
    this->show();
    on_pb_read_clicked(name);
}

void seeCase::on_pb_read_clicked(QString name)
{

    QFile f(name);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"sdf","can't open file,no case saved?",QMessageBox::Yes);
        return;
    }

    QTextStream txtInput(&f);
    QString Str;
    Str="";
    while(!txtInput.atEnd())
    {
        Str += txtInput.readLine()+"\n";
        //cout << lineStr << endl;
        //qDebug()<<Str;
    }
    f.close();
    ui->textBrowser->setText(Str);
}
