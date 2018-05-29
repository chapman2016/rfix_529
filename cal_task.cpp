#include "cal_task.h"
#include "ui_cal_task.h"
#include "config.h"
#include <QDebug>
cal_task::cal_task(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cal_task)
{
    ui->setupUi(this);
}

cal_task::~cal_task()
{
    delete ui;
}
void cal_task::rcv_cal_task()
{
    this->show();
    memset(newcase->a_tasksV, 0.0, sizeof(double)*32*16);
/*//////////////////
    double a[8];
    memset(a, 0, sizeof(double)*8);
    a[0]=2;
    a[1]=3;
    sub_calculator("a1*a2*0.5*0.1",a);
*//////////////////
/*
    for(int _type=0;_type<32;_type++)
    {
        if(newcase->dmgType[_type]==NULL)break;
        int i1,i2,i3;
        for(int i=0;i<16;i++)
        {

            //确定i1 i2 i3
            //newcase->subTask[_type][i]=gl
        }
    }
*/

    /*////extern QString gl_taskName[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_TASK];//分解任务全局量
    for(int _site=0;_site<32;_site++)
    {
        if(newcase->dmgSite[_site].isEmpty())break;
        for(int _struct=0;_struct<32;_struct++)
        {
            if(newcase->dmgStruct[_struct].isEmpty())break;
            for(int _type=0;_type<32;_type++)
            {
                if(newcase->dmgType[_type].isEmpty())break;
                for(int i=0;i<16;i++)
                {
                    newcase->subtaskV[][];
                    //newcase->subTask[_type][i]=gl
                }
            }
        }
    }
    */
    /*/////////////打印任务列表库//////////////////////////
    qDebug("all task lib:");
    for(int _site=0;_site<MAX_SITE;_site++)
    {
        if(gl_site[_site].isEmpty() )break;
        for(int _struct=0;_struct<MAX_STRUCT;_struct++)
        {
            if(gl_struct[_site][_struct].isEmpty())break;
            for(int _type=0;_type<MAX_STRUCT;_type++)
            {
                if(gl_type[_site][_struct][_type].isEmpty())break;
                //int i1,i2,i3;
                for(int i=0;i<16;i++)
                {
                   if(gl_taskName[_site][_struct][_type][i].isEmpty())break;
                   qDebug()<<gl_taskName[_site][_struct][_type][i];
                    //newcase->subTask[_type][i]=gl
                }
            }
        }
    }
    *////////////////////////////////////////
    //输出计算表达式 example "a1*0.2"
    //qDebug()<<gl_taskName[0][0][0][0].right(gl_taskName[0][0][0][0].length()-gl_taskName[0][0][0][0].indexOf("=")-1);
    ///////////////////////////////////////
    //计算任务
    int xxx=0,s2cnt=0,s3cnt=0,s4cnt=0;
    for(int s1=0;s1<32;s1++){
        int s2=0;
        if(newcase->dmgSite[s1].isEmpty())break;//若这行不存在
        //for(int i2=0;i2<16;i2++){
        //
        //}
        QString lft=newcase->dmgSite[s1]+newcase->dmgStruct[s1]+newcase->dmgType[s1];
        //qDebug()<<lft;
        //search task lib write subTask[s1][s2] subtaskV[s1][s2];

        for(int _site=0;_site<MAX_SITE;_site++)
        {
            if(gl_site[_site].isEmpty() )break;
            for(int _struct=0;_struct<MAX_STRUCT;_struct++)
            {
                if(gl_struct[_site][_struct].isEmpty())break;
                for(int _type=0;_type<MAX_STRUCT;_type++)
                {
                    if(gl_type[_site][_struct][_type].isEmpty())break;
                    //int i1,i2,i3;

                    for(int i=0;i<16;i++)
                    {
                       if(gl_taskName[_site][_struct][_type][i].isEmpty())break;
                      // qDebug()<<gl_taskName[_site][_struct][_type][i].left(gl_taskName[_site][_struct][_type][i].indexOf("+"));
                       if(gl_taskName[_site][_struct][_type][i].left(gl_taskName[_site][_struct][_type][i].indexOf("+"))
                               ==lft){
                           newcase->subTask[s1][s2++]=gl_taskName[_site][_struct][_type][i];
                          // qDebug()<<newcase->subTask[s1][s2-1];
                           //qDebug("eleV:");
                           double a[8];
                           memset(a, 0, sizeof(double)*8);
                           for(int an=0;an<8;an++){
                               if(newcase->dmgEleName[s1][an].isEmpty())break;
                               a[an]=newcase->dmgEle[s1][an];
                               //qDebug()<<a[an];
                           }

                           newcase->subtaskV[s1][s2-1]=
                           sub_calculator(gl_taskName[_site][_struct][_type][i].right(gl_taskName[_site][_struct][_type][i].length()-
                                                                                     gl_taskName[_site][_struct][_type][i].indexOf("=")-1),
                                          a);
                           //
                          // qDebug("sub taskV:%lf",newcase->subtaskV[s1][s2-1]);
                           //计算总任务量

                           for(int x=0;x<32*16;x++){
                               if(gl_h_task[x].isEmpty())break;
                               //qDebug()<<gl_h_task[x];
                               if(newcase->subTask[s1][s2-1].contains(gl_h_task[x]))
                               {
                                   for(int i=0;i<32*16;i++){
                                       if(newcase->a_tasks[i].isEmpty()){
                                           newcase->a_tasks[i]=gl_h_task[x];
                                           newcase->a_taskTag[i]=gl_h_taskStage[x];
                                           newcase->a_tasksV[i]+=newcase->subtaskV[s1][s2-1];
                                           break;
                                       }
                                       else if(newcase->a_tasks[i]==gl_h_task[x]){
                                           newcase->a_taskTag[i]=gl_h_taskStage[x];
                                           newcase->a_tasksV[i]+=newcase->subtaskV[s1][s2-1];
                                           break;
                                       }


                                   }
                                   //qDebug()<<newcase->subTask[s1][s2-1];
                                   //qDebug()<<gl_h_task[x];
                                   //newcase->a_tasks[xxx]=gl_h_task[x];
                                   //newcase->a_taskTag[xxx]=gl_h_taskStage[x];
                                   //newcase->a_tasksV[xxx]+=newcase->subtaskV[s1][s2-1];
                                   //if(newcase->a_tasks[xxx].isEmpty())xxx++;
                                   break;
                                  // qDebug()<<newcase->a_tasksV[xxx-1];
                                 //  qDebug("total task now:%d",xxx);
                               }

                               ///
                           }

                       }
                    }
                }
            }
        }
    }
    ///////////////
    //打印总任务量 任务量=0的为自定义
    qDebug("total task:");
    for(int i=0;i<32*16;i++)
    {
        if(newcase->a_tasks[i].isEmpty())break;
        qDebug()<<gl_h_task[i];
        qDebug("total V:%lf",newcase->a_tasksV[i]);
        //qDebug("s2 V:%lf",newcase->s2_tasksV[i]);
    }
    //////////////////
    //分配到三个阶段 //考虑实际 若小于1 则等于1 稍后再处理
    for(int x=0;x<32*16;x++){
        if(newcase->a_tasks[x].isEmpty())break;

        if(newcase->a_taskTag[x].contains("([2][3][4])")){
            newcase->s4_tasks[s4cnt]=newcase->s3_tasks[s3cnt]=newcase->s2_tasks[s2cnt]=newcase->a_tasks[x];
            newcase->s2_tasksV[s2cnt++]=newcase->a_tasksV[x]*0.3;
            newcase->s3_tasksV[s3cnt++]=newcase->a_tasksV[x]*0.6;
            newcase->s4_tasksV[s4cnt++]=newcase->a_tasksV[x]*0.1;
            qDebug("########################[2][3][4]");
            continue;
        }
        if(newcase->a_taskTag[x].contains("([2][3])")){
            newcase->s3_tasks[s3cnt]=newcase->s2_tasks[s2cnt]=newcase->a_tasks[x];
            newcase->s2_tasksV[s2cnt++]=newcase->a_tasksV[x]*(1.0/3.0);
            newcase->s3_tasksV[s3cnt++]=newcase->a_tasksV[x]*(2.0/3.0);
            qDebug("########################[2][3]");
            continue;
        }
        if(newcase->a_taskTag[x].contains("([2][4])")){
            newcase->s4_tasks[s4cnt]=newcase->s2_tasks[s2cnt]=newcase->a_tasks[x];
            newcase->s2_tasksV[s2cnt++]=newcase->a_tasksV[x]*(3.0/4.0);
            newcase->s4_tasksV[s4cnt++]=newcase->a_tasksV[x]*(1.0/4.0);
            qDebug("########################[2][4]");
            continue;
        }
        if(newcase->a_taskTag[x].contains("([3][4])")){
            newcase->s4_tasks[s4cnt]=newcase->s3_tasks[s3cnt]=newcase->a_tasks[x];
            newcase->s3_tasksV[s3cnt++]=newcase->a_tasksV[x]*(1.0/7.0);
            newcase->s4_tasksV[s4cnt++]=newcase->a_tasksV[x]*(6.0/7.0);
            qDebug("########################[3][4]");
            continue;
        }
        if(newcase->a_taskTag[x].contains("([2])")){
            newcase->s2_tasks[s2cnt]=newcase->a_tasks[x];
            newcase->s2_tasksV[s2cnt++]=newcase->a_tasksV[x];
            qDebug("########################[2]");
            continue;

        }
        if(newcase->a_taskTag[x].contains("([3])")){
            newcase->s3_tasks[s3cnt]=newcase->a_tasks[x];
            newcase->s3_tasksV[s3cnt++]=newcase->a_tasksV[x];
            qDebug("########################[3]");
            continue;
        }
        if(newcase->a_taskTag[x].contains("([4])")){
            newcase->s4_tasks[s4cnt]=newcase->a_tasks[x];
            newcase->s4_tasksV[s4cnt++]=newcase->a_tasksV[x];
            qDebug("########################[4]");
            continue;
        }
        //默认分配s3
        newcase->s3_tasks[s3cnt]=newcase->a_tasks[x];
        newcase->s3_tasksV[s3cnt++]=newcase->a_tasksV[x];
        qDebug("########################");
    }
    //////////////////////////////////////////////////
    //打印各阶段任务量
/*    qDebug("s2 task:");
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s2_tasks[i].isEmpty())break;
        qDebug()<<newcase->s2_tasks[i];
        qDebug("s2 V:%lf",newcase->s2_tasksV[i]);
    }
    qDebug("s3 task:");
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s3_tasks[i].isEmpty())break;
        qDebug()<<newcase->s3_tasks[i];
        qDebug("s3 V:%lf",newcase->s3_tasksV[i]);
    }
    qDebug("s4 task:");
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s4_tasks[i].isEmpty())break;
        qDebug()<<newcase->s4_tasks[i];
        qDebug("s4 V:%lf",newcase->s4_tasksV[i]);
    }
    ////////////////////////////////////////////////////
    *///
    printToTable(1);
}
void cal_task::printToTable(int stage)
{
    //QDoubleSpinBox *sbox=new QDoubleSpinBox;
   // sbox->show();
   // ui->tableWidget->setCellWidget(1,1,sbox);
    ui->tableWidget->clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_3->clear();
    ui->tableWidget_4->clear();
    ui->tableWidget->setRowCount(32*16);
    ui->tableWidget_2->setRowCount(32*16);
    ui->tableWidget_3->setRowCount(32*16);
    ui->tableWidget_4->setRowCount(32*16);
    for(int i=0;i<32*16;i++)
    {
        if(newcase->a_tasks[i].isEmpty())break;
        qDebug()<<newcase->a_tasks[i];
        qDebug("s V:%lf",newcase->a_tasksV[i]);

        QDoubleSpinBox *qd=new QDoubleSpinBox;
        qd->setMaximum(DBL_MAX);
        qd->setValue(newcase->a_tasksV[i]);
        ui->tableWidget_4->setCellWidget(i,1,qd);
        QLabel *lb=new QLabel;
        lb->setText(newcase->a_tasks[i]);
        lb->setAlignment(Qt::AlignCenter);
        ui->tableWidget_4->setCellWidget(i,0,lb);

    }
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s2_tasks[i].isEmpty())break;
        qDebug()<<newcase->s2_tasks[i];
        qDebug("s2 V:%lf",newcase->s2_tasksV[i]);
        //s2_cb[i]=new QComboBox;


        s2_sbox[i]=new QDoubleSpinBox;
        s2_sbox[i]->setMaximum(DBL_MAX);
        s2_sbox[i]->setValue(newcase->s2_tasksV[i]);
        ui->tableWidget->setCellWidget(i,1,s2_sbox[i]);
        QLabel *lb=new QLabel;
        lb->setText(newcase->s2_tasks[i]);
        lb->setAlignment(Qt::AlignCenter);
        ui->tableWidget->setCellWidget(i,0,lb);

    }
    qDebug("s3 task:");
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s3_tasks[i].isEmpty())break;
        qDebug()<<newcase->s3_tasks[i];
        qDebug("s3 V:%lf",newcase->s3_tasksV[i]);

        QLabel *lb=new QLabel;
        lb->setText(newcase->s3_tasks[i]);
        lb->setAlignment(Qt::AlignCenter);
        ui->tableWidget_2->setCellWidget(i,0,lb);
        s3_sbox[i]=new QDoubleSpinBox;
        s3_sbox[i]->setMaximum(DBL_MAX);
        s3_sbox[i]->setValue(newcase->s3_tasksV[i]);
        ui->tableWidget_2->setCellWidget(i,1,s3_sbox[i]);
    }
    qDebug("s4 task:");
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s4_tasks[i].isEmpty())break;
        qDebug()<<newcase->s4_tasks[i];
        qDebug("s4 V:%lf",newcase->s4_tasksV[i]);

        QLabel *lb=new QLabel;
        lb->setText(newcase->s4_tasks[i]);
        lb->setAlignment(Qt::AlignCenter);
        ui->tableWidget_3->setCellWidget(i,0,lb);
        s4_sbox[i]=new QDoubleSpinBox;
        s4_sbox[i]->setMaximum(DBL_MAX);
        s4_sbox[i]->setValue(newcase->s4_tasksV[i]);
        ui->tableWidget_3->setCellWidget(i,1,s4_sbox[i]);
    }

}





/**输入表达式和变量数组 得结果
 * 装载=a1*a2*0.5 常量要写成 x.x格式
 * formula eg: a1*a2*0.5
 * 目前只写了乘法支持 其他以后有需要再写
 * */
double cal_task::sub_calculator(QString formula,double a[8])
{
    if(formula.isEmpty())return 0.0;
    if(formula.at(0)=='x')return 0;
    double aws=0;
    double mleft,mright,tt,div;//所有计算的数值，包括常量
    int flg=1,afterdot=0;//0时正在解析 数zi
    //int ff=3;//1 2 3 4,+ - * /
    double x=0;
    int len=formula.length();
    aws=a[0];
    for(int i=0;i<len;i++){
        if(formula.at(i)=='a'){
            flg=1;
            if(i+1>=len)break;
            i++;
            if(QString(formula.at(i)).toInt()-1!=0&&QString(formula.at(i)).toInt()-1<8){
                aws*=a[QString(formula.at(i)).toInt()-1];
            };
           // qDebug("is a%d:%lf",QString(formula.at(i)).toInt()-1,a[QString(formula.at(i)).toInt()-1]);
        }
        else if(formula.at(i).isDigit()||formula.at(i)=='.'){
          //  qDebug("is digit:");
           afterdot=0;
           mleft=0;
           mright=0;
           div=1;
           for(;i<len;i++){
                if(formula.at(i).isDigit()){
                    if(afterdot==0){
                        mleft*=10;
                        mleft+=QString(formula.at(i)).toDouble();
                    }
                    else{
                        div*=10;
                        mright+=QString(formula.at(i)).toDouble()/div;
                    }
                }
                else if(formula.at(i)=='.'){
                    afterdot=1;
                }
                else break;
           }
           tt=mleft+mright;
           aws*=tt;
          // qDebug("const num:%lf",tt);
        }

    }
   // qDebug("aws:%f",aws);
    return aws;
}

void cal_task::on_pb_next_clicked()
{
    //保存任务量 只保存三个阶段的修改 总任务等于其求和
    save_table(newcase->s2_tasks,newcase->s2_tasksV,ui->tableWidget);
    save_table(newcase->s3_tasks,newcase->s3_tasksV,ui->tableWidget_2);
    save_table(newcase->s4_tasks,newcase->s4_tasksV,ui->tableWidget_3);
    //重新计算总任务量
    cal_ataskV();
    this->hide();
    emit sg_NeedIput();
}
void cal_task::save_table(QString tasks[], double tasksV[], QTableWidget *tw)
{
    for(int i=0;i<32*16;i++)
    {
        if(tasks[i].isEmpty())break;
        QWidget * widget=tw->cellWidget(i,1);//获得spinbox
        if(widget==NULL)break;
        QDoubleSpinBox *dbox= (QDoubleSpinBox*)widget;
        tasksV[i]=dbox->value();

    }
}
void cal_task::cal_ataskV()
{
    //清空a_taskV
    for(int i=0;i<32*16;i++)
    {
        if(newcase->a_tasks[i].isEmpty())break;
        newcase->a_tasksV[i]=0;
    }
    //扫描s_task,对每一个s_task 扫描a_task匹配 匹配到 a_taskV[i]+=s_taskV[i]
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s2_tasks[i].isEmpty())break;
        for(int i2=0;i2<32*16;i2++)
        {
            if(newcase->a_tasks[i2].isEmpty())break;
            if(newcase->a_tasks[i2]==newcase->s2_tasks[i])
            {
                newcase->a_tasksV[i2]+=newcase->s2_tasksV[i];
            }
        }
    }
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s3_tasks[i].isEmpty())break;
        for(int i2=0;i2<32*16;i2++)
        {
            if(newcase->a_tasks[i2].isEmpty())break;
            if(newcase->a_tasks[i2]==newcase->s3_tasks[i])
            {
                newcase->a_tasksV[i2]+=newcase->s3_tasksV[i];
            }
        }
    }
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s4_tasks[i].isEmpty())break;
        for(int i2=0;i2<32*16;i2++)
        {
            if(newcase->a_tasks[i2].isEmpty())break;
            if(newcase->a_tasks[i2]==newcase->s4_tasks[i])
            {
                newcase->a_tasksV[i2]+=newcase->s4_tasksV[i];
            }
        }
    }
}

void cal_task::on_pb_back_clicked()
{
    this->hide();
    emit sg_back();
}
void cal_task::rcv_back_to_me()
{
    this->show();
}
