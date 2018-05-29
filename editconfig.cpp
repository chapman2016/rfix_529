#include "editconfig.h"
#include "ui_editconfig.h"
#include <QLabel>
#include <QFile>
#include <QString>
editconfig::editconfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editconfig)
{
    ui->setupUi(this);
}

editconfig::~editconfig()
{
    delete ui;
}

void editconfig::on_pb_read_clicked()
{
    QTableWidget *tw= ui->tableWidget;
    tw->setRowCount(512);
    tw->clearContents();
    //QLabel *lb=new QLabel;
    //lb->setText("e[i].name");
    //tw->setCellWidget(0,0,lb);
    //int site=0,structs=0,type=0,
    //    taskd=0,ele=0,sjtype=0,need=0;
    int yy=0;
    for(int site=0;site<MAX_SITE;site++)
    {
        if(gl_site[site].isEmpty())break;
        QTableWidgetItem* item01 = new QTableWidgetItem(gl_site[site]);
        tw->setItem(yy,0,item01);
        //QLabel *lb=new QLabel;
        //lb->setText(gl_site[site]);
        //tw->setCellWidget(yy,0,lb);
        for(int structs=0;structs<MAX_STRUCT;structs++)
        {
            if(gl_struct[site][structs].isEmpty())break;
            //QLabel *lb=new QLabel;
            //lb->setText(gl_struct[site][structs]);
            //tw->setCellWidget(yy,1,lb);
            QTableWidgetItem* item01 = new QTableWidgetItem(gl_struct[site][structs]);
            tw->setItem(yy,1,item01);
            for(int type=0;type<MAX_TYPE;type++)
            {
                if(gl_type[site][structs][type].isEmpty())break;
                //QLabel *lb=new QLabel;
                //lb->setText(gl_type[site][structs][type]);
                //tw->setCellWidget(yy,2,lb);
                QTableWidgetItem* item01 = new QTableWidgetItem(gl_type[site][structs][type]);
                tw->setItem(yy,2,item01);
                int ya=0,yb=0;
                for(int ele=0;ele<MAX_ELE;ele++)
                {
                    if(gl_ele[site][structs][type][ele].isEmpty())break;
                    //QLabel *lb=new QLabel;
                    //lb->setText(gl_ele[site][structs][type][ele]);
                    //tw->setCellWidget(yy+ya++,3,lb);
                    QTableWidgetItem* item01 = new QTableWidgetItem(gl_ele[site][structs][type][ele]);
                    tw->setItem(yy+ya++,3,item01);
                }
                for(int taskd=0;taskd<MAX_TASK;taskd++)
                {
                    if(gl_taskName[site][structs][type][taskd].isEmpty())break;
                    //QLabel *lb=new QLabel;
                    //lb->setText(gl_taskName[site][structs][type][taskd]
                    //            .right(gl_taskName[site][structs][type][taskd].length()
                    //                   -gl_taskName[site][structs][type][taskd].indexOf("+")-1));
                    //tw->setCellWidget(yy+yb++,4,lb);
                    QTableWidgetItem* item01 = new QTableWidgetItem(gl_taskName[site][structs][type][taskd]
                                              .right(gl_taskName[site][structs][type][taskd].length()
                                              -gl_taskName[site][structs][type][taskd].indexOf("+")-1));
                    tw->setItem(yy+yb++,4,item01);
                }

                //ya>yb?yy+=ya:yy+=yb;
                yy+=8;
            }
        }
    }
    QTableWidgetItem* item01 = new QTableWidgetItem("-end-");
    tw->setItem(yy++,0,item01);
    QTableWidgetItem* item02 = new QTableWidgetItem("-事件类型-");
    tw->setItem(yy++,0,item02);
    for(int i=0;i<MAX_SJTYPE;i++)
    {
        if(gl_sjtype[i].isEmpty())break;
        QTableWidgetItem* item01 = new QTableWidgetItem(gl_sjtype[i]);
        tw->setItem(yy++,0,item01);
    }
    QTableWidgetItem* item011 = new QTableWidgetItem("-end-");
    tw->setItem(yy++,0,item011);
    item02 = new QTableWidgetItem("-能力需求-");
    tw->setItem(yy++,0,item02);
    for(int i=0;i<64;i++)
    {
        if(gl_needs[i].isEmpty())break;
        QTableWidgetItem* item01 = new QTableWidgetItem(gl_needs[i]);
        tw->setItem(yy++,0,item01);
    }
    QTableWidgetItem* item0111 = new QTableWidgetItem("-end-");
    tw->setItem(yy++,0,item0111);
    tw->resizeColumnsToContents();
    ui->pb_change->setEnabled(true);
}
void editconfig::rcv_show()
{
    this->show();
}

void editconfig::on_pb_change_clicked()
{
    QString str;
    str="";
    QFile file("config.txt");

    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    QTextStream out(&file);
    out << "----------config----------" <<endl;
    int row=0;
    QTableWidget *tw=ui->tableWidget;

    QTableWidgetItem* item0;
    QTableWidgetItem* item1;
    QTableWidgetItem* item2;
    QTableWidgetItem* item3;
    QTableWidgetItem* item4;
    int r1=0,r2=0;
    while(row<tw->rowCount()){

        item0=tw->item(row,0);
        item1=tw->item(row,1);
        item2=tw->item(row,2);

        r1=0;
        r2=0;
        item3=tw->item(row,3);
        item4=tw->item(row,4);
        if(item0!=NULL&&!item0->text().isEmpty())
        {
            if(item0->text()=="-end-")break;
            out<<"@sited@"<<item0->text()<<endl;
        }
        if(item1!=NULL&&!item1->text().isEmpty())
        {
            out<<"@struc@"<<item1->text()<<endl;
        }
        if(item2!=NULL&&!item2->text().isEmpty())
        {
            out<<"@typed@"<<item2->text()<<endl;
        }

        while(item3!=NULL&&!item3->text().isEmpty()&&r1<8)
        {
            //qDebug()<<r1;
            item3=tw->item(row+r1++,3);
            if(item3!=NULL&&!item3->text().isEmpty())
            out<<"@eleme@"<<item3->text()<<endl;
            //row++;
        }

        while(item4!=NULL&&!item4->text().isEmpty()&&r2<8)
        {
            item4=tw->item(row+r2++,4);
            if(item4!=NULL&&!item4->text().isEmpty())
            out<<"@taskd@"<<item4->text()<<endl;
            //row++;
        }
        //row++;
        row+=8;
    }

    //事件类型
    //qDebug()<<
    row++;
    row++;
    out<<"----------------------"<<endl;
     while(row<tw->rowCount())
     {
         item0=tw->item(row++,0);
         if(item0!=NULL&&!item0->text().isEmpty()&&item0->text()!="-end-")
             out<<"@stype@"<<item0->text()<<endl;
         else{break;}
     }
    //能力需求
     row++;
     out<<"----------------------"<<endl;
     while(row<tw->rowCount())
     {
         item0=tw->item(row++,0);
         if(item0!=NULL&&!item0->text().isEmpty()&&item0->text()!="-end-")
             out<<"@needs@"<<item0->text()<<endl;
         else{break;}
     }
    file.close();

}
