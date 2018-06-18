#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>

QString gl_sjtype[MAX_SJTYPE];//事件类型
QString gl_site[MAX_SITE];//发生位置 路段 桥梁 隧道
QString gl_struct[MAX_SITE][MAX_STRUCT];//损毁结构
QString gl_type[MAX_SITE][MAX_STRUCT][MAX_TYPE];//损毁类型
QString gl_ele[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_ELE];//计算要素
QString gl_taskName[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_TASK];//分解任务
double gl_taskValue[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_TASK];//总分解任务
QString gl_h_task[32*16];
QString gl_h_taskStage[32*16];
QString gl_needs[64];
QSqlDatabase *m_pDB;
int usertype;
eqp eqps[512];

bool first=true;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //on_pushButton_clicked();//skin

    QPixmap pixmap = QPixmap("base.jpg").scaled(this->size());
        QPalette palette(this->palette());
        palette.setBrush(QPalette::Background, QBrush(pixmap));
        this->setPalette(palette);
        //setWindowOpacity(0.7);
    usertype=IS_USER;
    updateconfig();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::rcv_mainwindow()
{
    if(first)
    {   color *co;
        co=new color;
        co->on_pb_go_clicked();
        delete co;
        first=false;
    }
    this->show();
}
void MainWindow::on_pb_create_newcase_clicked()
{
    //添加事件
    emit sg_addCase();

}
void MainWindow::updateconfig()
{
    QFile file("config.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the config file!"<<endl;
    }
    QString str;
    int site=-1,structs=-1,type=-1,
        taskd=-1,ele=-1,sjtype=-1,need=-1;
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        str=QString(line);
        str=str.left(str.length()-1);//去除换行\n
        /////////////////////////////
        ///  ///site
        ///  #structs
        ///  ##type
        ///  ###taskd
        ///  .element_calculate
        /// /////////////////////////
        //site ///
        if(str.left(7)=="@sited@")
        {   if(site+1<MAX_SITE){

                site++;
                structs=-1;
                type=-1;
                taskd=-1;
                ele=-1;
                gl_site[site]=str.right(str.length()-7);

            }
        }
        //structs#
        else if(str.left(7)=="@struc@")
        {
            if(structs+1<MAX_STRUCT){

                structs++;
                type=-1;
                taskd=-1;
                ele=-1;
                gl_struct[site][structs]=str.right(str.length()-7);

            }
        }
        //type##
        else if(str.left(7)=="@typed@")
        {
            if(type+1<MAX_TYPE){

                type++;
                taskd=-1;
                ele=-1;
                gl_type[site][structs][type]=str.right(str.length()-7);

            }
        }
        //taskd###sub tasks
        else if(str.left(7)=="@taskd@")
        {
            if(taskd+1<=MAX_TASK){
                taskd++;
                gl_taskName[site][structs][type][taskd]+=gl_site[site];
                gl_taskName[site][structs][type][taskd]+=gl_struct[site][structs];
                gl_taskName[site][structs][type][taskd]+=gl_type[site][structs][type];
                gl_taskName[site][structs][type][taskd]+="+";
                gl_taskName[site][structs][type][taskd]+=str.right(str.length()-7);
                //example"道路路面隆起开裂挖=a*0.2"
                //add gl_h_task
                str=str.right(str.length()-7);
                for(int i=0;i<32*16;i++)
                {
                    if(gl_h_task[i].isEmpty())
                    {
                        gl_h_task[i]=str.left(str.indexOf("("));
                        //qDebug()<<gl_h_task[i];
                        gl_h_taskStage[i]=str;//"挖([3])=a1*0.2"
                        //qDebug()<<gl_h_taskStage[i];
                        //qDebug()<<str;
                        //qDebug()<<str.indexOf("(");
                        break;
                    }
                    if(gl_h_task[i]==str.left(str.indexOf("("))){
                        break;
                    }

                }

            }
        }
        //ele.
        else if(str.left(7)=="@eleme@")
        {
            if(ele+1<=MAX_ELE){
                ele++;
                gl_ele[site][structs][type][ele]=str.right(str.length()-7);
            }
        }
        //sjtype
        else if(str.left(7)=="@stype@")
        {
            if(sjtype+1<=MAX_SJTYPE){
                sjtype++;
                gl_sjtype[sjtype]=str.right(str.length()-7);
            }
        }
        else if(str.left(7)=="@needs@")
        {
            if(need+1<64){
                need++;
                gl_needs[need]=str.right(str.length()-7);
                //qDebug()<<gl_needs[need];
            }
        }
        else;

    }//while end

/*
   for(int i1=0;i1<MAX_SITE;i1++){
        for(int i2=0;i2<MAX_STRUCT;i2++){
            for(int i3=0;i3<MAX_TYPE;i3++){
                if(!gl_type[i1][i2][i3].isEmpty())
                   qDebug()<<gl_type[i1][i2][i3];
                for(int i4=0;i4<MAX_ELE;i4++){
                    if(!gl_taskName[i1][i2][i3][i4].isEmpty()){
                        qDebug()<<gl_taskName[i1][i2][i3][i4];
                    }
                }
            }
           // if(!gl_struct[i1][i2].isEmpty())
            //qDebug()<<gl_struct[i1][i2];

        }
       // qDebug()<<gl_site[site];

    }
*/
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
    ///////////////////////
   /* QFile file3("eqpeft.txt");
    if(!file3.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the eqpeft file!"<<endl;
    }
    int eqpcnt2=0;
    while(!file3.atEnd())
    {
        QByteArray line = file3.readLine();
        str=QString(line);
        str=str.left(str.length()-1);//去除换行\n
        //qDebug()<<str;
        eqps[eqpcnt2++].efficiency=str.toDouble();
    }*/


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug("mainwindow closed");
    qApp->quit();
}
//更改配色
void MainWindow::on_pushButton_clicked()
{
    //skin
    color *co;
    co=new color;
    co->show();

}

void MainWindow::on_pb_conf_clicked()
{
    emit sg_config();
}

void MainWindow::on_pb_see_saved_clicked()
{
    //emit sg_seecase();
    emit sg_caselist();
}

void MainWindow::on_pb_see_eqps_clicked()
{
    emit sg_seeeqps();
}
