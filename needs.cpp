#include "needs.h"
#include "ui_needs.h"
#include "config.h"
needs::needs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::needs)
{
    ui->setupUi(this);
    updateui(ui->listWidget,"s2");
    updateui(ui->listWidget_2,"s3");
    updateui(ui->listWidget_3,"s4");
}

needs::~needs()
{
    delete ui;
}

void needs::rcv_NeedInput(){
    //ui->listWidget->clear();
    //ui->listWidget_2->clear();
    //ui->listWidget->addItem("sss");
    QObject::connect(this,SIGNAL(sg_addlist(int)),this,SLOT(add_to_list(int)));
    this->show();
}
void needs::on_pb_next_clicked()
{

    //save
    for(int i=0;i<ui->listWidget->count();i++){
        newcase->s2_needs[i]=ui->listWidget->item(i)->text();
    }
    for(int i=0;i<ui->listWidget_2->count();i++){
        newcase->s3_needs[i]=ui->listWidget_2->item(i)->text();
    }
    for(int i=0;i<ui->listWidget_3->count();i++){
        newcase->s4_needs[i]=ui->listWidget_3->item(i)->text();
    }
    emit sg_matcheqp();
    this->hide();
}
void needs::updateui(QListWidget *lw,QString stage)
{
    QComboBox *cb;
    if(stage=="s2")cb=ui->comboBox;
    else if(stage=="s3")cb=ui->comboBox_2;
    else cb=ui->comboBox_3;
    //extern QString gl_needs[64];//装备能力需求标签 //“s2=多功能化”
    lw->clear();
    for(int i=0;i<64;i++){
        if(gl_needs[i].isEmpty())break;
        if(gl_needs[i].contains(stage)){
            lw->addItem(gl_needs[i].right(gl_needs[i].length()-gl_needs[i].indexOf("=")-1));
        }
        //
        cb->addItem(gl_needs[i].right(gl_needs[i].length()-gl_needs[i].indexOf("=")-1));
    }
}

void needs::on_pb_back_clicked()
{
    this->hide();
    emit sg_back();
}

void needs::on_pb_add_1_clicked()
{
    emit sg_addlist(1);
}

void needs::on_pb_add_2_clicked()
{
    emit sg_addlist(2);
}

void needs::on_pb_add_3_clicked()
{
    emit sg_addlist(3);
}
void needs::add_to_list(int i)
{
    QComboBox *cb;
    QListWidget *lw;
    if(i==1){cb=ui->comboBox;lw=ui->listWidget;}
    else if(i==2){cb=ui->comboBox_2;lw=ui->listWidget_2;}
    else {cb=ui->comboBox_3;lw=ui->listWidget_3;}
    lw->addItem(cb->currentText());

}
