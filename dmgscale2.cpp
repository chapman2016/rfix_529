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
int tbCNT=0;
dmgscale2::dmgscale2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dmgscale2)
{
    ui->setupUi(this);
    listwgt=ui->listWidget;
    QTableWidget*tb=new QTableWidget(0,6);
    tb->setHorizontalHeaderLabels(QStringList() <<tr("损毁位置")<<tr("损毁结构")<<tr("类型")<<tr("计算要素")<<tr("数值")<<tr("删除"));
    tb->setColumnWidth(4,99);
    QListWidgetItem *item = new QListWidgetItem;
    QSize size = item->sizeHint();
    item->setSizeHint(QSize(size.width(),30));
    //listwgt->addItem(item);
    //listwgt->setItemWidget(item,tb);


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
   cb_insert_data_values(msite->currentIndex(),mstructs->currentIndex(),mtype->currentIndex(),
                         item,tbs[tbCNT]);
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
    for(int i=0;i<=tbCNT;i++)
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
        cb_insert_data_values(c1->currentIndex(),c2->currentIndex(),c3->currentIndex(),
                              item,tw);
        break;
    }
    default:
        break;
    }

}
//on_cb_changed3生成后面
void dmgscale2::cb_insert_data_values(int i1,int i2,int i3,QListWidgetItem *item,QTableWidget *tw)
{
    //tw->removeColumn(3);
    int old=0;
    QWidget *w1,*w2;
    for(;;old++){
        w1=tw->cellWidget(old,3);
        w2=tw->cellWidget(old,4);
        if(NULL==w1||NULL==w2)break;
        tw->removeCellWidget(old,3);
        tw->removeCellWidget(old,4);
    }
    //tw->removeColumn(4);
    QLabel* ele[32];
    QDoubleSpinBox *eleV[32];
    int i4=0;
    for( i4=0;i4<MAX_ELE&&!gl_ele[i1][i2][i3][i4].isEmpty();i4++)
    {
        ele[i4]=new QLabel;
        eleV[i4]=new QDoubleSpinBox;
        eleV[i4]->setMaximum(DBL_MAX);
        eleV[i4]->setValue(1.0);
        ele[i4]->setText(gl_ele[i1][i2][i3][i4]);
        tw->setCellWidget(i4,3,ele[i4]);
        tw->setCellWidget(i4,4,eleV[i4]);
     }
    tw->resizeColumnsToContents();
    //qDebug()<<"spbox width"<<eleV[0]->width();
    QSize size = item->sizeHint();
    item->setSizeHint(QSize(size.width(),30*i4+25));

}
//on_cb_changed1,2
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
    for(int i=0;i<=tbCNT;i++)
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
    QTableWidget *tw0;
    QWidget *w=listwgt->itemWidget(listwgt->item(0));
    tw0=(QTableWidget*)w;
    if(NULL!=tw0)
        tw0->horizontalHeader()->setVisible(true);

    //QSize size = item->sizeHint();
    //item->setSizeHint(QSize(size.width(),30*4));
}

void dmgscale2::on_pb_next_clicked()
{
    //save
    int x=0;
    QTableWidget *tw;
    for(;;x++)
    {
        QWidget *w=listwgt->itemWidget(listwgt->item(x));
        tw=(QTableWidget*)w;
        if(NULL==tw)break;
        QComboBox *msite=(QComboBox *)tw->cellWidget(0,0);
        QComboBox *mstructs=(QComboBox *)tw->cellWidget(0,1);
        QComboBox *mtype=(QComboBox *)tw->cellWidget(0,2);
        newcase->dmgSite[x]=msite->currentText();
        newcase->dmgStruct[x]=mstructs->currentText();
        newcase->dmgType[x]=mtype->currentText();
        qDebug()<<newcase->dmgType[x];
        QLabel* ele[32];
        QDoubleSpinBox *eleV[32];
        //QPushButton *pb=new QPushButton;
        int old=0;
        QWidget *w1,*w2;
        for(;;old++){
            w1=tw->cellWidget(old,3);
            w2=tw->cellWidget(old,4);
            if(NULL==w1||NULL==w2)break;
            ele[old]=(QLabel*)tw->cellWidget(old,3);
            eleV[old]=(QDoubleSpinBox*)tw->cellWidget(old,4);
            newcase->dmgEleName[x][old]=ele[old]->text();
            newcase->dmgEle[x][old]=eleV[old]->value();
            qDebug()<< newcase->dmgEle[x][old];
        }

    }
    this->hide();
    emit sg_cal_task();

}
void dmgscale2::rcv_back_to_me()
{
    this->show();
}
void dmgscale2::rcv_dmgscale()
{
    //clear contents?
    QTableWidget *tw0;
    QWidget *w=listwgt->itemWidget(listwgt->item(0));
    tw0=(QTableWidget*)w;
    if(NULL==tw0)
        on_pb_add_clicked();
    this->show();
}
void dmgscale2::on_pb_back_clicked()
{
    //保存？
    this->hide();
    emit sg_go_back();
}
