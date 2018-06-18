#include "basicinfo.h"
#include "config.h"
#include "ui_basicinfo.h"
#include "rdcase.h"
//#include "ca.h"
#include <QDebug>
rdcase *newcase;

basicInfo::basicInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::basicInfo)
{
    ui->setupUi(this);


    //初始化
    //for(int i=0;i<32;i++){
     //   cb3[i]=cb2[i]=cb1[i]=NULL;
      //  cb1index[i]=cb2index[i]=cb3index[i]=0;
   // }
    //


}

basicInfo::~basicInfo()
{
    delete ui;
}
void basicInfo::rcv_addcase()
{

    //更新事件类型下拉框
    int cnt=0;
    while(!gl_sjtype[cnt].isEmpty())
         ui->cb_type->addItem(gl_sjtype[cnt++]);
    //
    clearcbs();
    //创建3个损毁下拉框 初始化第一个下拉框
    //on_pb_addRdDmgType_clicked();
    //后面两个根据前面的current值生成
    //
    if(newcase!=NULL)
        delete newcase;
    newcase=new rdcase;
    this->show();
}
void basicInfo::rcv_basicinfo()
{
    updateui();
    this->show();
}
void basicInfo::updateui()
{

    //从newcase中重绘ui
}

void basicInfo::rcv_cbchange(int i)
{
    if(i<0)i=0;
    //qDebug("cbi %d",i);
    //check cb1
    int icb1=0;//当前是第几行的cb1
    for( icb1=0;icb1<32&&cb1[icb1]!=NULL;icb1++)
    {
       // qDebug()<<cb1index[0];
        if(cb1[icb1]->currentIndex()!=cb1index[icb1])
        {
            cb1index[icb1]=cb1[icb1]->currentIndex();


            cb2[icb1]->clear();
            int i2=0;
            for( i2=0;i2<MAX_STRUCT&&!gl_struct[i][i2].isEmpty();i2++)
            {
                cb2[icb1]->addItem(gl_struct[i][i2]);
             }
            return;
            break;
        }
     }
    //check cb2
    int icb2=0;
    for( icb2=0;icb2<32&&cb2[icb2]!=NULL;icb2++){
        if(cb2[icb2]->currentIndex()!=cb2index[icb2])
        {
            cb2index[icb2]=cb2[icb2]->currentIndex();\
            cb3[icb2]->clear();
            int i3=0;
            for( i3=0;i3<MAX_TYPE&&!gl_type[cb1[icb2]->currentIndex()][i][i3].isEmpty();i3++)
            {
                cb3[icb2]->addItem(gl_type[cb1[icb2]->currentIndex()][i][i3]);
             }
            return;
            break;
        }
    }
    ///////////////


}
/*
void basicInfo::on_pb_addRdDmgType_clicked()
{
    int i=0;
    while(i<32){
        if(cb1[i]==NULL){
            cb1[i]=new QComboBox;
            cb2[i]=new QComboBox;
            cb3[i]=new QComboBox;
            cb1[i]->setParent(ui->scrollAreaWidgetContents_2);
            cb2[i]->setParent(ui->scrollAreaWidgetContents_2);
            cb3[i]->setParent(ui->scrollAreaWidgetContents_2);

            cb1[i]->setGeometry(x1,yn,w1,hn);
            cb2[i]->setGeometry(x2,yn,w2,hn);
            cb3[i]->setGeometry(x3,yn,w3,hn);

            //初始化下拉框
            /////////////////
            int i1=0;
            for( i1=0;i1<MAX_SITE&&!gl_site[i1].isEmpty();i1++)
            {
                cb1[i]->addItem(gl_site[i1]);
             }
            i1=0;
            int i2=0;
            for( i2=0;i2<MAX_STRUCT&&!gl_struct[i1][i2].isEmpty();i2++)
            {
                cb2[i]->addItem(gl_struct[i1][i2]);
             }
            i2=0;
            int i3=0;
            for( i3=0;i3<MAX_TYPE&&!gl_type[i1][i2][i3].isEmpty();i3++)
            {
                cb3[i]->addItem(gl_type[i1][i2][i3]);
             }
            ///////////////
            cb1index[i]=0;
            cb2index[i]=0;
            cb3index[i]=0;
            //qDebug()<<i;
            cb1[i]->show();
            cb2[i]->show();
            cb3[i]->show();
            yn+=30;
            ////
            QObject::connect(cb1[i],SIGNAL(currentIndexChanged(int)),this,
                             SLOT(rcv_cbchange(int)));
            QObject::connect(cb2[i],SIGNAL(currentIndexChanged(int)),this,
                             SLOT(rcv_cbchange(int)));
            //////
            break;
        }
        i++;
   }//while end
    //qDebug()<<cb1index[0];
    //qDebug()<<cb2index[0];
    //qDebug()<<cb3index[0];
}
*/
void basicInfo::closeEvent(QCloseEvent *event)
{
    qDebug("basicinfo closed");
    clearcbs();
}
void basicInfo::clearcbs()
{
    //清除三组下拉框
    for(int i=0;i<32;i++)
    {
        if(cb1[i]!=NULL){
            //delete cb1[i];
            cb1[i]->setDisabled(true);
            cb2[i]->setDisabled(true);
            cb3[i]->setDisabled(true);
            cb1[i]->hide();
            cb2[i]->hide();
            cb3[i]->hide();
            cb1[i]->deleteLater();
            cb2[i]->deleteLater();
            cb3[i]->deleteLater();
            cb1[i]=NULL;
            cb2[i]=NULL;
            cb3[i]=NULL;
            cb1index[i]=0;
            cb2index[i]=0;
            cb3index[i]=0;
            yn=0;
        }
    }//for end
}

void basicInfo::on_pb_next_clicked()
{
    //先保存到newcase
    newcase->id=0;//
    newcase->datetime=ui->dte_time->dateTime();
    newcase->place=ui->le_place->text();
    newcase->sjtype=ui->cb_type->currentText();
    newcase->GEOs=ui->le_geos->text();
/*    for(int i=0;i<32;i++){
        if(cb1[i]==NULL)break;
        newcase->dmgSite[i]=cb1[i]->currentText();
        newcase->dmgStruct[i]=cb2[i]->currentText();
        newcase->dmgType[i]=cb1[i]->currentText();
    }
*/
    this->hide();
    emit sg_dmgscale();
}
void basicInfo::rcv_back_to_me()
{
    //清空
    //读取写入

    this->show();
}

void basicInfo::on_pb_cancel_clicked()
{
    this->hide();
}
