#include "dmgscale2.h"
#include "ui_dmgscale2.h"
#include "config.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QScrollBar>
#include <QLabel>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QHeaderView>
#include <QListWidget>

QListWidget *listwgt=NULL;
QTableWidget *tbs[32];
int tbCNT=1;
dmgscale2::dmgscale2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dmgscale2)
{
    ui->setupUi(this);
    listwgt=ui->listWidget;
    QTableWidget*tb=new QTableWidget(0,6);
    tb->setHorizontalHeaderLabels(QStringList() <<tr("损毁位置")<<tr("损毁结构")<<tr("类型")<<tr("计算要素")<<tr("数值")<<tr("删除"));
    QListWidgetItem *item = new QListWidgetItem;
    QSize size = item->sizeHint();
    item->setSizeHint(QSize(size.width(),30));
    listwgt->addItem(item);
    listwgt->setItemWidget(item,tb);
}

dmgscale2::~dmgscale2()
{
    delete ui;
}

void dmgscale2::on_pb_add_clicked()
{
   if(tbCNT==31)return;
   int rows=2;
   tbs[tbCNT]=new QTableWidget(rows,6);
   tbs[tbCNT]->verticalHeader()->setVisible(false);
   tbs[tbCNT]->setHorizontalHeaderLabels(QStringList() <<tr("损毁位置")<<tr("损毁结构")<<tr("类型")<<tr("计算要素")<<tr("数值")<<tr("删除"));
   if(tbCNT==0){

   }
   else {
       tbs[tbCNT]->horizontalHeader()->setVisible(false);
   }
   QComboBox *msite=new QComboBox;
   QComboBox *mstructs=new QComboBox;
   QComboBox *mtype=new QComboBox;
   QPushButton *pb=new QPushButton;
   cb_insert_data(msite,mstructs,mtype,0,0,0);
   pb->setText("删除此条");
   //pb->set
   tbs[tbCNT]->setCellWidget(0,0,msite);
   tbs[tbCNT]->setCellWidget(0,1,mstructs);
   tbs[tbCNT]->setCellWidget(0,2,mtype);
   tbs[tbCNT]->setCellWidget(0,5,pb);
   //tbs[tbCNT]->resizeColumnsToContents();

   QListWidgetItem *item = new QListWidgetItem;
   QSize size = item->sizeHint();
   item->setSizeHint(QSize(size.width(),30*rows));
   listwgt->addItem(item);
   listwgt->setItemWidget(item,tbs[tbCNT]);
   QObject::connect(pb,SIGNAL(clicked()),this,SLOT(on_pb_del_clicked()));
   QObject::connect(msite,SIGNAL(currentIndexChanged(int)),this,SLOT(on_update_cb_index()));
   QObject::connect(mstructs,SIGNAL(currentIndexChanged(int)),this,SLOT(on_update_cb_index()));
   QObject::connect(mtype,SIGNAL(currentIndexChanged(int)),this,SLOT(on_update_cb_index()));
   qDebug()<<"pb parent:"<<pb->parentWidget();
   qDebug()<<"cb parent:"<<msite->parentWidget();
   tbCNT++;
}
void dmgscale2::on_update_cb_index()
{
    int cbNum=0;//1,2,3
    QComboBox *cb =dynamic_cast<QComboBox*>(sender());
    if(cb==NULL)return;
    QTableWidget *tw;
    //cb->setText("del");
    QListWidgetItem *item;
    for(int i=1;i<=tbCNT;i++)
    {
        item=listwgt->item(i);
        QWidget *w=listwgt->itemWidget(item);
        if(NULL==w){
            //qDebug()<<"return cnt:"<<i;
            return;
        }
        tw=(QTableWidget*)w;
        if(tw->cellWidget(0,0)==cb )
        {
            cbNum=1;
            break;
        }
        if(tw->cellWidget(0,1)==cb )
        {
            cbNum=2;
            break;
        }
        if(tw->cellWidget(0,2)==cb )
        {
            cbNum=3;
            break;
        }
    }
    QComboBox *c=(QComboBox *)tw->cellWidget(0,cbNum-1);
    QComboBox *c1=(QComboBox *)tw->cellWidget(0,0);
    QComboBox *c2=(QComboBox *)tw->cellWidget(0,1);
    QComboBox *c3=(QComboBox *)tw->cellWidget(0,2);
    qDebug()<<c->currentText();
    switch ( cbNum) {
    case 1:
    {
        qDebug()<<"cb1";
        cb_insert_data_one(c2,1,c->currentIndex(),0,0);
        break;
    }
    case 2:
    {
        qDebug()<<"cb2";
        cb_insert_data_one(c3,2,c1->currentIndex(),c2->currentIndex(),0);
        break;
    }
    case 3:
    {
        qDebug()<<"cb3";
        break;
    }
    default:
        break;
    }

}
void dmgscale2::cb_insert_data_one(QComboBox*cb,int x,int ii1,int ii2,int ii3){
    //初始化下拉框
    /////////////////
    /// \brief i1
    cb->clear();
    int i1=0;
    //for( i1=0;i1<MAX_SITE&&!gl_site[i1].isEmpty();i1++)
    //{
    //    cb1->addItem(gl_site[i1]);
    // }
    //cb1->setCurrentIndex(ii1);
    i1=ii1;
    int i2=0;
    if(x==1)
    for( i2=0;i2<MAX_STRUCT&&!gl_struct[i1][i2].isEmpty();i2++)
    {
        cb->addItem(gl_struct[i1][i2]);
     }
    //cb2->setCurrentIndex(ii2);
    i2=ii2;
    int i3=0;
    if(x==2)
    for( i3=0;i3<MAX_TYPE&&!gl_type[i1][i2][i3].isEmpty();i3++)
    {
        cb->addItem(gl_type[i1][i2][i3]);
     }
    //cb3->setCurrentIndex(ii3);
}
void dmgscale2::cb_insert_data(QComboBox*cb1,QComboBox*cb2,QComboBox*cb3 ,int ii1,int ii2,int ii3 )
{
    //初始化下拉框
    /////////////////
    int i1=0;
    for( i1=0;i1<MAX_SITE&&!gl_site[i1].isEmpty();i1++)
    {
        cb1->addItem(gl_site[i1]);
     }
    cb1->setCurrentIndex(ii1);
    i1=ii1;
    int i2=0;
    for( i2=0;i2<MAX_STRUCT&&!gl_struct[i1][i2].isEmpty();i2++)
    {
        cb2->addItem(gl_struct[i1][i2]);
     }
    cb2->setCurrentIndex(ii2);
    i2=ii2;
    int i3=0;
    for( i3=0;i3<MAX_TYPE&&!gl_type[i1][i2][i3].isEmpty();i3++)
    {
        cb3->addItem(gl_type[i1][i2][i3]);
     }
    cb3->setCurrentIndex(ii3);
}
void dmgscale2::on_pb_del_clicked()
{
    qDebug()<<"delete 1 row";
    QPushButton *pb =dynamic_cast<QPushButton*>(sender());
    if(pb==NULL)return;
    QTableWidget *tw;
    pb->setText("del");
    QListWidgetItem *item;
    for(int i=1;i<=tbCNT;i++)
    {
        item=listwgt->item(i);
        QWidget *w=listwgt->itemWidget(item);
        if(NULL==w){
            qDebug()<<"return cnt:"<<i;
            return;
        }
        tw=(QTableWidget*)w;
        if(tw->cellWidget(0,5)==pb )
        {
         break;
        }
    }



    listwgt->removeItemWidget(item);
    delete item;
    qDebug()<<"row:"<<listwgt->count();
    tbCNT--;
    //if(NULL!=tbs[0])
    //tbs[0]->horizontalHeader()->setVisible(true);

    //QSize size = item->sizeHint();
    //item->setSizeHint(QSize(size.width(),30*4));
}
