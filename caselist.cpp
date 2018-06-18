#include "caselist.h"
#include "ui_caselist.h"
#include "config.h"
#include <QFile>
#include <QUrl>
#include <QDir>
#include <QMessageBox>
#include <QListWidget>
#include <QLabel>
#include <QDesktopServices>
caseList::caseList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::caseList)
{
    ui->setupUi(this);
}

caseList::~caseList()
{
    delete ui;
}

void caseList::on_opendir_clicked()
{
    bool ok=QDesktopServices::openUrl(QUrl::fromLocalFile("./"));
    if(!ok){QMessageBox::warning(this,"sdf","can't open file,no case saved yet?",QMessageBox::Yes);}
    return;
}
void caseList::rcv_caselist()
{
    this->show();
    //read list

    QDir dir;
    if(!dir.exists("./case/"))
    {
       qDebug()<<"不存在该路径"<<endl;
       dir.mkpath("./case/");
    }
    dir.setCurrent("./case/");
         dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
         dir.setSorting(QDir::Size | QDir::Reversed);

         QFileInfoList list = dir.entryInfoList();
         qDebug() << "     Bytes Filename";
         for (int i = 0; i < list.size(); ++i) {
             QFileInfo fileInfo = list.at(i);
             //.arg(fileInfo.metadataChangeTime().toString("yyyy-MM-dd")
             QString file= qPrintable(QString("%1")
                                      .arg(fileInfo.fileName()));
             ui->listWidget->addItem(file);

         }
}
void caseList::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug()<<item->text();
    emit see_case(item->text());
}
