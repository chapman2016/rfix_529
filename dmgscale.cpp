#include "dmgscale.h"
#include "ui_dmgscale.h"
#include "rdcase.h"
#include "config.h"

dmgscale::dmgscale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dmgscale)
{
    ui->setupUi(this);
    //初始化
    current_time.start();
    //sg_lastTime=current_time.msec();
    for(int i=0;i<32;i++){
        cb3[i]=cb2[i]=cb1[i]=NULL;
        cb1index[i]=cb2index[i]=cb3index[i]=-1;
        for(int i2=0;i2<8;i2++){
            ele[i][i2]=NULL;
            eleV[i][i2]=NULL;
        }
    }
}

dmgscale::~dmgscale()
{
    delete ui;
}
void dmgscale::rcv_dmgcale()
{
    //clear
    clearcbs();
    for(int i=0;i<32;i++)
    {
        if(newcase->dmgSite[i].isEmpty())break;
        on_pb_addMore_clicked();//加一行
         //yn+=30;
        cb1[i]->setCurrentIndex(1);
        cb2[i]->setCurrentIndex(1);
        cb3[i]->setCurrentIndex(1);
        cb1[i]->setCurrentText(newcase->dmgSite[i]);
        cb2[i]->setCurrentText(newcase->dmgStruct[i]);
        cb3[i]->setCurrentText(newcase->dmgType[i]);
        //假设不能编辑已添加的选项 之前可编辑的有bug 测试一下先
       // cb1[i]->setEnabled(false);
        //cb2[i]->setEnabled(false);
        //cb3[i]->setEnabled(false);

/////////////////////////////////////////////////////////////////
        //if(newcase->dmgSite[i].isEmpty())break;
        //生成后面
/*        int i4=0,i1,i2,i3,icb3;
        icb3=i;
        i1=cb1[icb3]->currentIndex();
        i2=cb2[icb3]->currentIndex();
        i3=cb3[icb3]->currentIndex();
        ye=cb1[icb3]->geometry().y();
        for( i4=0;i4<MAX_ELE&&!gl_ele[i1][i2][i3][i4].isEmpty();i4++)
        {
            ele[icb3][i4]=new QLabel;
            eleV[icb3][i4]=new QDoubleSpinBox;
            eleV[icb3][i4]->setMaximum(DBL_MAX);
            eleV[icb3][i4]->setValue(1.0);
            ele[icb3][i4]->setParent(ui->scrollAreaWidgetContents);
            eleV[icb3][i4]->setParent(ui->scrollAreaWidgetContents);
            ele[icb3][i4]->setGeometry(x4,ye,w4,hn);
            eleV[icb3][i4]->setGeometry(x5,ye,w5,hn);
            ele[icb3][i4]->setText(gl_ele[i1][i2][i3][i4]);
            ele[icb3][i4]->show();
            eleV[icb3][i4]->show();
            yn+=30;
            ye+=30;
         }
         */
/////////////////////////////////////////////////////////////////


    }


    this->show();
}
void dmgscale::rcv_cbchange(int i)
{
    bool rst=false;
    if(i<0){
        i=0;
        rst=true;
    }
   // qDebug("time elapsed %d",current_time.elapsed());


   // sg_lastTime=current_time.msec();
    //qDebug("cbi %d",i);
    //check cb1
    int icb1=0;//当前是第几行的cb1
    for( icb1=0;icb1<32&&cb1[icb1]!=NULL;icb1++)
    {
       // qDebug()<<cb1index[0];
        if(cb1[icb1]->currentIndex()!=cb1index[icb1])
        {
            cb1index[icb1]=cb1[icb1]->currentIndex();
qDebug("check cb1 changed");

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
        {   qDebug("check cb2 changed");
            cb2index[icb2]=cb2[icb2]->currentIndex();
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
//////////////////////////////////

    //check cb3
    int icb3=0;
    for( icb3=0;icb3<32&&cb3[icb3]!=NULL;icb3++){
        if(cb3[icb3]->currentIndex()!=cb3index[icb3])
        {
            //if(current_time.elapsed()<100)return;
            current_time.restart();
            cb3index[icb3]=cb3[icb3]->currentIndex();
            qDebug("check cb3 changed");
            qDebug()<<"icb3:"<<icb3;
            //cb3[icb3]->clear();hide后面
//生成后面
            int i4,i1,i2,i3,plus=0;
            //icb3=i;
            i1=cb1[icb3]->currentIndex();
            i2=cb2[icb3]->currentIndex();
            i3=cb3[icb3]->currentIndex();
            ye=cb1[icb3]->geometry().y();
            for(int iii=0;iii<MAX_ELE;iii++)
            {
                if(ele[icb3][iii]!=NULL){
                    ele[icb3][iii]->hide();
                    eleV[icb3][iii]->hide();
                    //if(yn>=30)
                   //     yn-=30;
                    //ye-=30;
                   // plus-=30;
                }
            }
            qDebug()<<"plus:"<<plus;
            for( i4=0;i4<MAX_ELE&&!gl_ele[i1][i2][i3][i4].isEmpty();i4++)
            {

                ele[icb3][i4]=new QLabel;
                eleV[icb3][i4]=new QDoubleSpinBox;
                eleV[icb3][i4]->setMaximum(DBL_MAX);
                eleV[icb3][i4]->setValue(1.0);
                ele[icb3][i4]->setParent(ui->scrollAreaWidgetContents);
                eleV[icb3][i4]->setParent(ui->scrollAreaWidgetContents);
                ele[icb3][i4]->setGeometry(x4,ye,w4,hn);
                eleV[icb3][i4]->setGeometry(x5,ye,w5,hn);
                ele[icb3][i4]->setText(gl_ele[i1][i2][i3][i4]);
                ele[icb3][i4]->show();
                eleV[icb3][i4]->show();
                //yn+=30;
                ye+=30;
                plus+=30;
                if(i4+i<8&&ele[icb3][i4+1]!=NULL)
                    ele[icb3][i4+1]=NULL;
             }
           //yn-=30;
           // ye+=30;
            //plus-=30;
            //移动其他（以下）
         /*   for(int ii=icb3+1;ii<32&&cb3[ii]!=NULL;ii++){
                if(cb3[ii]==NULL)break;
                cb1[ii]->setGeometry(x1,cb1[ii]->geometry().y()+plus,w1,hn);
                qDebug()<<"1geometry().y()+plus:"<<cb1[ii]->geometry().y()+plus;
                cb2[ii]->setGeometry(x2,cb2[ii]->geometry().y()+plus,w2,hn);
                qDebug()<<"2geometry().y()+plus:"<<cb2[ii]->geometry().y()+plus;
                cb3[ii]->setGeometry(x3,cb3[ii]->geometry().y()+plus,w3,hn);
                qDebug()<<"3geometry().y()+plus:"<<cb3[ii]->geometry().y()+plus;
                cb1[ii]->show();
                cb2[ii]->show();
                cb3[ii]->show();
                for(int i2=0;i2<8;i2++){
                    if(ele[ii][i2]==NULL)break;
                    ele[ii][i2]->setGeometry(x4,ele[ii][i2]->geometry().y()+plus,w4,hn);
                    eleV[ii][i2]->setGeometry(x5,eleV[ii][i2]->geometry().y()+plus,w5,hn);
                    ele[ii][i2]->show();
                    eleV[ii][i2]->show();
                }
            }*/

            prt_cbs();
            return;
            break;
        }
    }

    ///////////////
}

void dmgscale::on_pb_addMore_clicked()
{
    //return;//下面有问题
    int i=0;
    while(i<32){
        if(cb1[i]==NULL){
           // if(i!=0)yn-=30;
            cb1[i]=new QComboBox;
            cb2[i]=new QComboBox;
            cb3[i]=new QComboBox;
            cb1[i]->setParent(ui->scrollAreaWidgetContents);
            cb2[i]->setParent(ui->scrollAreaWidgetContents);
            cb3[i]->setParent(ui->scrollAreaWidgetContents);

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
            cb1[i]->setCurrentText(0);
            cb2[i]->setCurrentText(0);
            cb3[i]->setCurrentText(0);
            //qDebug()<<i;
            cb1[i]->show();
           cb2[i]->show();
           cb3[i]->show();
            yn+=30*3;
            ////
            QObject::connect(cb1[i],SIGNAL(currentIndexChanged(int)),this,
                             SLOT(rcv_cbchange(int)));
            QObject::connect(cb2[i],SIGNAL(currentIndexChanged(int)),this,
                             SLOT(rcv_cbchange(int)));
            QObject::connect(cb3[i],SIGNAL(currentIndexChanged(int)),this,
                            SLOT(rcv_cbchange(int)));
            //////
            //rcv_cbchange(-1);
            //////
            break;
        }
        i++;
   }//while end
}
void dmgscale::clearcbs()
{
     yn=0;
    //清除三组下拉框
    for(int i=0;i<32;i++)
    {
        if(cb1[i]!=NULL){
           //delete cb1[i];
           // cb1[i]->setDisabled(true);
           // cb2[i]->setDisabled(true);
           // cb3[i]->setDisabled(true);
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

            for(int i4=0;i4<8;i4++){
                if(ele[i][i4]!=NULL){
                    ele[i][i4]->hide();
                    eleV[i][i4]->hide();
                  //  ele[i][i4]->deleteLater();
                  //  eleV[i][i4]->deleteLater();
                    ele[i][i4]=NULL;
                    eleV[i][i4]=NULL;

                }
            }

        }
    }//for end
    //清除后面

}
void dmgscale::add_ele()
{
    //
}


void dmgscale::on_pb_next_clicked()
{
    //save
    for(int i=0;i<32;i++){
        if(cb1[i]==NULL)break;
        newcase->dmgSite[i]=cb1[i]->currentText();
        newcase->dmgStruct[i]=cb2[i]->currentText();
        newcase->dmgType[i]=cb3[i]->currentText();
        for(int i2=0;i2<8;i2++){
            if(ele[i][i2]==NULL)break;
            newcase->dmgEleName[i][i2]=ele[i][i2]->text();
            newcase->dmgEle[i][i2]=eleV[i][i2]->value();
        }
    }
    this->hide();
    emit sg_cal_task();
}

void dmgscale::on_pb_add_clicked()
{
    on_pb_addMore_clicked();//加一行
    //cb1[i]->setCurrentText(newcase->dmgSite[i]);
    //cb2[i]->setCurrentText(newcase->dmgStruct[i]);
    //cb3[i]->setCurrentText(newcase->dmgType[i]);
    //newcase也加一行

}
void dmgscale::prt_cbs()
{
    for(int i=0;i<32;i++)
    {
        if(cb1[i]!=NULL){
           //delete cb1[i];
           // cb1[i]->setDisabled(true);
           // cb2[i]->setDisabled(true);
           // cb3[i]->setDisabled(true);
            qDebug()<<cb1[i]->currentText()<<" "<<cb2[i]->currentText()<<" "<<cb3[i]->currentText();;


            for(int i4=0;i4<8;i4++){
                if(ele[i][i4]!=NULL){
                     qDebug()<<ele[i][i4]->text()<<" "<<eleV[i][i4]->value();


                }
            }

        }
    }//for end
}

void dmgscale::on_pb_back_clicked()
{
    //保存？
    this->hide();
    emit sg_go_back();
}
void dmgscale::rcv_back_to_me()
{
    this->show();
}
