#include "final.h"
#include "ui_final.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
final::final(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::final)
{
    ui->setupUi(this);
}

final::~final()
{
    delete ui;
}


void final::rcv_final()
{
    this->show();
    //刷新表格
    ui->tableWidget->clearContents();
    print_to_table(newcase->a_tasks,newcase->a_tasksV,ui->tableWidget);
    //输出任务列表
    //输出装备列表
    ui->tableWidget_2->clearContents();
    print_eqps(ui->tableWidget_2);
    //计算所选装备完成相应任务耗时
    double maxtime=cal_time();//所有任务中耗时最长的 假设所有任务并行
    qDebug()<<"total time:"<<maxtime;
    ui->doubleSpinBox_time->setValue(maxtime);

}
void final::print_eqps(QTableWidget *tw)
{
    tw->clearContents();
    tw->horizontalHeader()->setVisible(true);
    tw->setRowCount(32*16);
    QScrollBar *scrollBar =tw->verticalScrollBar();
    scrollBar->setValue(0);
    int row=0;
    //eqp *e;
    //e=newcase->s2eqp;
    row=add_to_eqptb(row,newcase->s2eqp,tw);
    row=add_to_eqptb(row,newcase->s3eqp,tw);
    row=add_to_eqptb(row,newcase->s4eqp,tw);

     tw->resizeColumnsToContents();
}
int final::add_to_eqptb(int startrow,eqp e[],QTableWidget *tw)
{
    int row=startrow;
    for(int i=0;i<64;i++)
    {
        if(e[i].name.isEmpty())break;
        QLabel *lb=new QLabel;
        lb->setText("["+e[i].doTask+"]:"+e[i].name);
        //lb->setAlignment(Qt::AlignCenter);
        tw->setCellWidget(row,0,lb);
        QSpinBox *qd=new QSpinBox;
        //qd->setMaximum(DBL_MAX);
        qd->setValue(e[i].cnt);//
        tw->setCellWidget(row,1,qd);
        //QCheckBox *cb=new QCheckBox;
        //cb->setCheckState(Qt::Unchecked);
        //cb->setText("use");
        //tw->setCellWidget(row,2,cb);
        row++;
    }
    return row;
}
void final::print_to_table(QString tasks[],double tasksV[],QTableWidget *tw)
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
        qd->setEnabled(false);//禁止编辑
        tw->setCellWidget(i,1,qd);
        QLabel *lb=new QLabel;
        lb->setText(tasks[i]);
        lb->setAlignment(Qt::AlignCenter);
        tw->setCellWidget(i,0,lb);

    }
}
double final::cal_time()
{
    double max_time=0;
    max_time+=cal_time_sub(newcase->s2_tasks,newcase->s2_tasksV,newcase->s2eqp);
    max_time+=cal_time_sub(newcase->s3_tasks,newcase->s3_tasksV,newcase->s3eqp);
    max_time+=cal_time_sub(newcase->s4_tasks,newcase->s4_tasksV,newcase->s4eqp);
    return max_time;

}
double final::cal_time_sub(QString tasks[],double tasksV[],eqp e[])
{
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
    return max_time;
}
void final::on_pb_save_clicked()
{
    QString outstring;
    outstring="--------new case----------\n";
    outstring+="录入时间:"+newcase->writedatetime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n";
    //outstring+="id:"+newcase->id+"\n";
    outstring+="发生时间:"+newcase->datetime.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    outstring+="地点:"+newcase->place+"\n";
    outstring+="类型:"+newcase->sjtype+"\n";
    outstring+="地理特征:"+newcase->GEOs+"\n";
    outstring+="损毁信息:\n";
    for(int i=0;i<32;i++)
    {
        if(newcase->dmgSite[i].isEmpty())break;
        outstring+=newcase->dmgSite[i]+" "+newcase->dmgStruct[i]+" "+newcase->dmgType[i]+"\n";
        outstring+="损毁规模:\n";
        for(int i2=0;i2<8;i2++)
        {
            if(newcase->dmgEleName[i][i2].isEmpty())break;
            outstring+=newcase->dmgEleName[i][i2]+":"+QString::number(newcase->dmgEle[i][i2], 10, 4)+"\n";
        }
    }
    outstring+="阶段2装备:\n";
    for(int i=0;i<64;i++)
    {
        if(newcase->s2eqp[i].name.isEmpty())break;
        outstring+=newcase->s2eqp[i].name+"*"+QString::number(newcase->s2eqp[i].cnt, 10, 0)+"\n";
    }
    outstring+="阶段3装备:\n";
    for(int i=0;i<64;i++)
    {
        if(newcase->s3eqp[i].name.isEmpty())break;
        outstring+=newcase->s3eqp[i].name+"*"+QString::number(newcase->s3eqp[i].cnt, 10, 0)+"\n";
    }
    outstring+="阶段4装备:\n";
    for(int i=0;i<64;i++)
    {
        if(newcase->s4eqp[i].name.isEmpty())break;
        outstring+=newcase->s4eqp[i].name+"*"+QString::number(newcase->s4eqp[i].cnt, 10, 0)+"\n";
    }


///////////////////////////////////////////////////////////////////////////////////////////
    QDir tempDir;
    //临时保存程序当前路径
    //QString currentDir = tempDir.currentPath();
    //qDebug()<<currentDir;
    if(!tempDir.exists("./case/"))
    {
       qDebug()<<"不存在该路径"<<endl;
       tempDir.mkpath("./case/");
    }
    //qDebug()<<currentDir.toStdString();
    QString name="./case/";
    name+=newcase->place+"-";
    name+=newcase->sjtype+"-";
    name+=newcase->datetime.toString("yyyy-MM-dd");
    name+=".txt";
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
    {
          QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
    }
    QTextStream in(&file);
    in<<outstring;
    file.close();
    qDebug()<<outstring;
    see_case(name);
    this->hide();
}

void final::on_pb_back_clicked()
{
    emit sg_matcheqp1();
    this->hide();
}
