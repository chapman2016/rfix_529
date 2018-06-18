#include "matcheqp.h"
#include "ui_matcheqp.h"

matcheqp::matcheqp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::matcheqp)
{
    nowstage=2;
    ui->setupUi(this);
}

matcheqp::~matcheqp()
{
    delete ui;
}

void matcheqp::on_pb_next_clicked()//计算建议数量
{
    cal=true;
    QString *tasks=newcase->s2_tasks;
    double *tasksV=newcase->s2_tasksV;
    eqp *e=newcase->s2eqp;

    switch (nowstage) {
    case 2:
        tasks=newcase->s2_tasks;
        tasksV=newcase->s2_tasksV;
        e=newcase->s2eqp;
        break;
    case 3:
        tasks=newcase->s3_tasks;
        tasksV=newcase->s3_tasksV;
        e=newcase->s3eqp;
        break;
    case 4:
        tasks=newcase->s4_tasks;
        tasksV=newcase->s4_tasksV;
        e=newcase->s4eqp;
        break;
    default:
        break;
    }



    //保存装备
    saveeqp(e);
    //读取测试
    for(int i=0;i<64;i++){
        if(newcase->s2eqp[i].name.isEmpty())break;
       qDebug()<<newcase->s2eqp[i].name;
    }
    //计算s2_数量/时间
    //cal_cnt(tasks,tasksV,e);//注释掉就默认最大数量了。。。。
    //打印
    ui->tableWidget_result->setRowCount(32*16);
    ui->tableWidget_result->clearContents();
    for(int i=0;i<64;i++){
            if(e[i].name.isEmpty())break;
            qDebug()<<e[i].name<<":"<<e[i].cnt;
            QLabel *lb=new QLabel;
            lb->setText(e[i].name);
            ui->tableWidget_result->setCellWidget(i,0,lb);
            QSpinBox *qd=new QSpinBox;
            qd->setValue(e[i].cnt);
            ui->tableWidget_result->setCellWidget(i,1,qd);

        }
    ui->tableWidget_result->resizeColumnsToContents();
}
void  matcheqp::rcv_matcheqp()
{
   // QString str="a";
   // qDebug()<<str.right(2);

/*
    //遍历任务 匹配装备
    for(int i=0;i<32*16;i++)
    {
        if(newcase->s2_tasks[i].isEmpty())break;
        //对于每一个任务 遍历装备库
        for(int i2=0;i2<512;i2++){
            if(eqps[i2].name.isEmpty())break;
            if(eqps[i2].name.contains(newcase->s2_tasks[i].right(2))){
                qDebug()<<newcase->s2_tasks[i];
                qDebug()<<eqps[i2].name;

            }

        }
    }
*/    //////////////////////////
    //初始化
    nowstage=2;
    ui->tableWidget->clearContents();
    ui->tableWidget_2->clearContents();
    ui->tableWidget_result->clearContents();
    ui->doubleSpinBox_time->setValue(0);
    tempe[0].name="";
    tempeqp2[0].name="";
    //qDebug("s2_tasks:");
    /////////////////////////////////
    print_task_eqp();
    this->show();
}
void matcheqp::print_task_eqp(){
    QString *tasks=newcase->s2_tasks;
    double *tasksV=newcase->s2_tasksV;

    switch (nowstage) {
    case 2:
        tasks=newcase->s2_tasks;
        tasksV=newcase->s2_tasksV;
        ui->label_stage->setText("2");
        ui->progressBar->setValue(62);
        break;
    case 3:
        tasks=newcase->s3_tasks;
        tasksV=newcase->s3_tasksV;
        ui->label_stage->setText("3");
        ui->progressBar->setValue(75);
        break;
    case 4:
        tasks=newcase->s4_tasks;
        tasksV=newcase->s4_tasksV;
        ui->label_stage->setText("4");
        ui->progressBar->setValue(88);
        break;
    default:
        break;
    }
    ////////////////////////////////////
    match(tasks,tempe);
    print_eqp(tempe,ui->tableWidget_2);
    //打印任务列表
    print_to_table(tasks,tasksV,ui->tableWidget);

}
void matcheqp::match(QString tasks[],eqp e[])
{
    int ecnt=0,ecnt2=0;
    //tp2cnt=0;
    bool used[256];
    for(int i=0;i<256;i++){used[i]=false;}
    //遍历任务 匹配装备
    for(int i=0;i<32*16;i++)
    {
        if(tasks[i].isEmpty()&&i!=0)break;
        //对于每一个任务 遍历装备库
        for(int i2=0;i2<256;i2++){
            if(eqps[i2].name.isEmpty())break;
            //匹配任务名称 关键词
            //used=false;
            if(eqps[i2].name.contains(tasks[i].right(2))&&!tasks[i].isEmpty()){
                qDebug()<<tasks[i];
                qDebug()<<eqps[i2].name;
                e[ecnt].doTask=tasks[i];
                e[ecnt].efficiency=eqps[i2].efficiency;
                e[ecnt++].name=eqps[i2].name;
                used[i2]=true;
                if(ecnt>=64)break;
                e[ecnt].name.clear();

            }

        }
    }
    qDebug()<<"**************x"<<ecnt2;
    for(int xx=0;ecnt2<256;xx++,ecnt2++)
    {

        if(eqps[ecnt2].name.isEmpty())break;
        if(!used[ecnt2]){
            qDebug()<<"**************unused "<<ecnt2;
            tempeqp2[xx].doTask="custom";
            tempeqp2[xx].efficiency=eqps[ecnt2].efficiency;
            tempeqp2[xx].name=eqps[ecnt2].name;
            //tp2cnt++;
            if(xx+1>=256)break;
            //tempeqp2[xx+1].name.clear();

        }
    }
}
void matcheqp::print_to_table(QString tasks[],double tasksV[],QTableWidget *tw)
{
    tw->clearContents();
    tw->horizontalHeader()->setVisible(true);
    tw->setRowCount(32*16);
    QScrollBar *scrollBar =tw->verticalScrollBar();
    scrollBar->setValue(0);
    for(int i=0;i<32*16;i++)
    {
        if(tasks[i].isEmpty())break;
        qDebug()<<tasks[i];
        qDebug("s V:%lf",tasksV[i]);

        QDoubleSpinBox *qd=new QDoubleSpinBox;
        qd->setMaximum(DBL_MAX);
        qd->setValue(tasksV[i]);
        //qd->setEnabled(false);//禁止编辑
        tw->setCellWidget(i,1,qd);
        QLabel *lb=new QLabel;
        lb->setText(tasks[i]);
        lb->setAlignment(Qt::AlignCenter);
        tw->setCellWidget(i,0,lb);

    }
}
void matcheqp::print_eqp(eqp e[], QTableWidget *tw)
{
    tw->clearContents();
    QScrollBar *scrollBar =tw->verticalScrollBar();
    scrollBar->setValue(0);
    //QLabel* a="装备名称"
    //QString str="装备名称，是否启用，最大数量";//中文乱码啊 实在太麻烦了
   // QString str="equipment,enable,MAX_NUM";
    //QStringList h=str.split(",");
    //QStringList h;
    //h<<tr("装备名称")<<tr("是否启用")<<tr("最大数量");
    //tw->setHorizontalHeaderLabels(h);
    tw->horizontalHeader()->setVisible(true);
   //tw->setHorizontalHeaderItem(0,"是否启用");
   // tw->setHorizontalHeaderItem(0,"最大数量");
    tw->setRowCount(32*16);
    int i=0;
    for(;i<64;i++)
    {
        if(e[i].name.isEmpty())break;
        QLabel *lb=new QLabel;
        lb->setText("["+e[i].doTask+"]:"+e[i].name);
        //lb->setAlignment(Qt::AlignCenter);
        tw->setCellWidget(i,0,lb);
        QSpinBox *qd=new QSpinBox;
        //qd->setMaximum(DBL_MAX);
        qd->setValue(1);//默认1台
        tw->setCellWidget(i,2,qd);
        QCheckBox *cb=new QCheckBox;
        cb->setCheckState(Qt::Unchecked);
        cb->setText("use");
        tw->setCellWidget(i,1,cb);
    }
     //qDebug()<<"*********************tp2"<<tp2cnt+1;
    for(int i2=0;i2<256;i2++,i++)
    {

        if(tempeqp2[i2].name.isEmpty())break;
        QLabel *lb=new QLabel;
        lb->setText("["+tempeqp2[i2].doTask+"]:"+tempeqp2[i2].name);
        //lb->setAlignment(Qt::AlignCenter);
        tw->setCellWidget(i,0,lb);
        QSpinBox *qd=new QSpinBox;
        //qd->setMaximum(DBL_MAX);
        qd->setValue(1);//默认1台
        tw->setCellWidget(i,2,qd);
        QCheckBox *cb=new QCheckBox;
        cb->setCheckState(Qt::Unchecked);
        cb->setText("use");
        tw->setCellWidget(i,1,cb);
    }
     tw->resizeColumnsToContents();
}
void matcheqp::saveeqp(eqp e[])
{   //将勾选的存入


    int cnt=0;
    for(int i=0;i<256;i++){
        if(cnt>=64)break;
        if(i>=ui->tableWidget_2->rowCount())break;
        QWidget * widget=ui->tableWidget_2->cellWidget(i,0);//获得widget
        QLabel *lb=(QLabel*)widget;
        if(widget==NULL)break;//是否到尽头
        //QLabel *lb=(QLabel*)widget;

        QWidget * widget2=ui->tableWidget_2->cellWidget(i,1);//获得check btn
        QCheckBox *cb= (QCheckBox*)widget2;

        if(cb->isChecked()){
            qDebug()<<"xxxxx"<<lb->text();
            e[cnt].name=tempe[i].name;
            e[cnt].doTask=tempe[i].doTask;
            if(tempe[i].name.isEmpty()){
                e[cnt].name=tempeqp2[i].name;
                e[cnt].doTask=tempeqp2[i].doTask;
            }
            QWidget * widget3=ui->tableWidget_2->cellWidget(i,2);//获得max_cnt
            QSpinBox *spb= (QSpinBox*)widget3;
            e[cnt].cnt=spb->value();//max 先设为最大
            if(!tempe[i].name.isEmpty())
            e[cnt].efficiency=tempe[i].efficiency;
            cnt++;
            qDebug()<<e[cnt-1].name;
            if(cnt<64&&!e[cnt].name.isEmpty()){//清除后面的
                e[cnt].name.clear();
            }
        }

    }

  /*  for(int i=0;i<256;i++){
        if(cnt>=64)break;
        if(i>=ui->tableWidget_2->rowCount())break;
        QWidget * widget=ui->tableWidget_2->cellWidget(i,0);//获得widget
        if(widget==NULL)break;//是否到尽头
        //QLabel *lb=(QLabel*)widget;
        QWidget * widget2=ui->tableWidget_2->cellWidget(i,1);//获得check btn
        QCheckBox *cb= (QCheckBox*)widget2;
        if(cb->isChecked()){
            e[cnt].name=tempeqp2[i].name;
            e[cnt].doTask=tempeqp2[i].doTask;
            QWidget * widget3=ui->tableWidget_2->cellWidget(i,2);//获得max_cnt
            QSpinBox *spb= (QSpinBox*)widget3;
            e[cnt].cnt=spb->value();//max 先设为最大
            e[cnt++].efficiency=tempeqp2[i].efficiency;
            //qDebug()<<e[cnt-1].name;
            if(cnt<64&&!e[cnt].name.isEmpty()){//清除后面的
                e[cnt].name.clear();
            }
        }

    }*/
}
void matcheqp::cal_cnt(QString tasks[], double tasksV[], eqp e[])
{
    //遍历task
        //对于每一个task 遍历eqp 找出对应eqps
        //算出每个任务最短用时：装备数量最大时   ,e[i].cnt默认值为最大限制值
        //筛选其中耗时最长的一项作为基准 max_short_time
        //遍历减小其他装备数量，直到其他任务时间与基准时间最接近（小于等于）
    //对于没有匹配到eqp的任务处理：加入作业风险时间 or 给个提示 忽略计算
    //对于各阶段任务量 已在计算任务量模块限制
    double max_time=0;
    int maxtime_taskid=0;
    //计算 max short time
    for(int i=0;i<32*16;i++){//对每项任务
        if(tasks[i].isEmpty())break;
        double eft=0;
        bool found=false;
        for(int i2=0;i2<64;i2++)//遍历装备
        {
            if(e[i2].name.isEmpty())break;
            if(e[i2].doTask==tasks[i])
            {
                found=true;
                eft+=e[i2].cnt*e[i2].efficiency;
            }
        }
        ///////////////////
        if(!found){
            //该任务没有分配到装备 暂不加入运算
        }
        else{
            if(max_time<tasksV[i]/eft){
                max_time=tasksV[i]/eft;
                maxtime_taskid=i;
            }
        }
        ///////////////////
    }
    qDebug("max_shortest_time:%lf",max_time);
    //ui->doubleSpinBox_time->setValue(max_time);
    //max_time较小时，全设为1台

    ////////////////////////////////////
    //逐个减少装备数量，直到时间tasksV[i]/eft>max-time,此时的数量+1作为最终数量
    for(int i=0;i<32*16;i++){//对每项任务
        if(tasks[i].isEmpty())break;
        if(i==maxtime_taskid)continue;

        while(1){
            double eft=0;
            bool found=false;
            int tp[64];
            memset(tp,-1,64*sizeof(int));
            //qDebug()<<"tp0"<<tp[0];
            int ti=0;
        for(int i2=0;i2<64;i2++)//遍历装备
        {
            if(e[i2].name.isEmpty())break;
            if(e[i2].doTask==tasks[i])
            {
                found=true;
                eft+=(e[i2].cnt-1)*e[i2].efficiency;//这种方式同一任务的装备数量只能同步增减 当同一任务的装备最大数量相同时给出的建议数量最合理 否则多给一台
                tp[ti++]=i2;
               // qDebug()<<tasks[i]<<e[i2].name;
               // qDebug("cnt now:%d",e[i2].cnt);
            }
        }
        ///////////////////
        if(!found){
            //该任务没有分配到装备 暂不加入运算
            break;
        }
        else{
            if(max_time<tasksV[i]/eft){
                //max_time=tasksV[i]/eft;
                for(int i3=0;i3<64;i3++){
                    if(tp[i3]==-1)break;
                    if(e[tp[i3]].cnt>1)
                    e[tp[i3]].cnt--;
                }
                break;
            }
        //e[i2].cnt--;
        //if(e[i2].cnt<1){
        //    e[i2].cnt=1;
        //    break;
        //}
            for(int i3=0;i3<64;i3++){
                if(tp[i3]==-1)break;
                if(e[tp[i3]].cnt>1)
                e[tp[i3]].cnt--;
            }
        }
        }//while end

        ///////////////////
    }
}

void matcheqp::on_pb_conferm_clicked()
{
    eqp *e=newcase->s2eqp;
    switch (nowstage) {
    case 2:
        e=newcase->s2eqp;
        break;
    case 3:
        e=newcase->s3eqp;
        break;
    case 4:
        e=newcase->s4eqp;
        break;
    default:
        break;
    }
    //save装备数目
    for(int i=0;i<64;i++){
            if(e[i].name.isEmpty())break;
            QWidget * widget3=ui->tableWidget_result->cellWidget(i,1);//获得cnt
            QSpinBox *spb= (QSpinBox*)widget3;
            e[i].cnt=spb->value();//
            qDebug()<<e[i].cnt;
        }
}

void matcheqp::on_pb_realnext_clicked()
{
   //检测是否确认数量
    if(!cal){
        on_pb_next_clicked();

    }
   //保存
   //on_pb_conferm_clicked();
   on_pb_flush_time_clicked();
   //on_pb_flush_time_clicked();//包含on_pb_conferm_clicked();
   nowstage++;
   cal=false;
   if(nowstage<=4){

       ui->tableWidget->clearContents();
       ui->tableWidget_2->clearContents();
       ui->tableWidget_result->clearContents();
       print_task_eqp();
   }
   else{
       //next page

       cal_ataskV();
       this->hide();
       emit sg_final();
   }

}

void matcheqp::on_pb_back_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget_2->clearContents();
    ui->tableWidget_result->clearContents();
    if(nowstage>2)
    {
       nowstage--;
       //清数据 有个小bug？
       eqp *e=newcase->s2eqp;
       switch (nowstage) {
       case 2:
           e=newcase->s2eqp;
           break;
       case 3:
           e=newcase->s3eqp;
           break;
       case 4:
           e=newcase->s4eqp;
           break;
       default:
           break;
       }
       //save装备数目
       for(int i=0;i<64;i++){
              if(e[i].name.isEmpty())break;
              e[i].name.clear();
           }
       print_task_eqp();

    }
    else if(nowstage==2)
    {
        this->hide();
        emit sg_back();
    }
}

void matcheqp::on_pb_flush_time_clicked()
{
    QString *tasks=newcase->s2_tasks;
    double *tasksV=newcase->s2_tasksV;
    eqp *e=newcase->s2eqp;
    QTableWidget *tw=ui->tableWidget;
    switch (nowstage) {
    case 2:
        tasks=newcase->s2_tasks;
        tasksV=newcase->s2_tasksV;
        e=newcase->s2eqp;
        break;
    case 3:
        tasks=newcase->s3_tasks;
        tasksV=newcase->s3_tasksV;
        e=newcase->s3eqp;
        break;
    case 4:
        tasks=newcase->s4_tasks;
        tasksV=newcase->s4_tasksV;
        e=newcase->s4eqp;
        break;
    default:
        break;
    }

    //保存任务量
    save_table(tasks,tasksV,tw);
    //确认数量
    on_pb_conferm_clicked();
    //计算时间
    double total_time=0;
    for(int i=0;i<32*16;i++)
    {
        if(tasks[i].isEmpty())break;
        double eft=0;
        for(int ii=0;ii<512;ii++)
        {
            if(e[ii].name.isEmpty())break;
            if(e[ii].doTask==tasks[i])
                eft+=e[ii].efficiency*e[ii].cnt;
        }
        if(eft==0)continue;
        total_time+=tasksV[i]/eft;
    }
    qDebug()<<"total_time:"<<total_time;
    ui->doubleSpinBox_time->setValue(total_time);
}
void matcheqp::save_table(QString tasks[], double tasksV[], QTableWidget *tw)
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
void matcheqp::cal_ataskV()
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
void matcheqp::rcv_matcheqp1()
{
    this->show();

}
