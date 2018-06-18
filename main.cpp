#include "mainwindow.h"
#include <QApplication>
#include "basicinfo.h"
#include "dmgscale.h"
#include "dmgscale2.h"
#include "form.h"
#include "infoinput.h"
#include "cal_task.h"
#include "needs.h"
#include "seecase.h"
#include "matcheqp.h"
#include "final.h"
#include "editconfig.h"
#include "seeeqps.h"
#include "base.h"
#include "caselist.h"
#include "database.h"
#include "login.h"
//#include "ui_base.h"
#include <QPluginLoader>
#include <QStyleFactory>
#include <QTextCodec>
#include <QDir>
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    //QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);

    QApplication a(argc, argv);
    login lg;
    MainWindow w;

    lg.show();
    QObject::connect(&lg,SIGNAL(offline_use()),&w,SLOT(rcv_mainwindow()));
    //w.show();
    //db
    //QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator() + "plugins");
    //a.addLibraryPath(strLibPath);
    QPluginLoader loader;
    loader.setFileName("qsqlmysql.dll");
    //qDebug() << loader.load();
    //qDebug() << loader.errorString();
    database dbc;
    qDebug()<<"login:"<<dbc.login("admin","123456");
    dbc.readeqp();
    dbc.addeqp("ad","hh",1,"asd","12","sad");
    //
    editconfig ec;
    //ec.show();
    QObject::connect(&w,SIGNAL(sg_config()),&ec,SLOT(rcv_show()));
    basicInfo bi;
    //bi.setParent(ba);

    //ba->setLayout(bi.layout());
    QObject::connect(&w,SIGNAL(sg_addCase()),&bi,SLOT(rcv_addcase()));
    dmgscale ds;
    dmgscale2 ds2;
    //ds2.show();
    //ds.setParent(ba);
    //QObject::connect(&bi,SIGNAL(sg_dmgscale()),&ds,SLOT(rcv_dmgcale()));
    QObject::connect(&bi,SIGNAL(sg_dmgscale()),&ds2,SLOT(rcv_dmgscale()));
    //QObject::connect(&ds,SIGNAL(sg_go_back()),&bi,SLOT(rcv_back_to_me()));
    QObject::connect(&ds2,SIGNAL(sg_go_back()),&bi,SLOT(rcv_back_to_me()));
    //Form f;
    //f.show();
    //infoinput ip;
    //ip.show();
    cal_task ct;
    //QObject::connect(&ds,SIGNAL(sg_cal_task()),&ct,SLOT(rcv_cal_task()));
    QObject::connect(&ds2,SIGNAL(sg_cal_task()),&ct,SLOT(rcv_cal_task()));
    //QObject::connect(&ct,SIGNAL(sg_back()),&ds,SLOT(rcv_back_to_me()));
    QObject::connect(&ct,SIGNAL(sg_back()),&ds2,SLOT(rcv_back_to_me()));
    needs nd;
    QObject::connect(&ct,SIGNAL(sg_NeedIput()),&nd,SLOT(rcv_NeedInput()));
    QObject::connect(&nd,SIGNAL(sg_back()),&ct,SLOT(rcv_back_to_me()));
    seeCase sc;
    caseList cl;
    //sc.show();
    QObject::connect(&w,SIGNAL(sg_caselist()),&cl,SLOT(rcv_caselist()));
    QObject::connect(&cl,SIGNAL(see_case(QString)),&sc,SLOT(rcv_seecase(QString)));
    //QObject::connect(&w,SIGNAL(sg_seecase()),&sc,SLOT(rcv_seecase()));
    matcheqp me;
    QObject::connect(&nd,SIGNAL(sg_matcheqp()),&me,SLOT(rcv_matcheqp()));
    QObject::connect(&me,SIGNAL(sg_back()),&nd,SLOT(rcv_NeedInput()));
    final fn;
    QObject::connect(&me,SIGNAL(sg_final()),&fn,SLOT(rcv_final()));
    QObject::connect(&fn,SIGNAL(sg_matcheqp1()),&me,SLOT(rcv_matcheqp1()));
    QObject::connect(&fn,SIGNAL(see_case(QString)),&sc,SLOT(rcv_seecase(QString)));
    seeeqps seeeqp;
    QObject::connect(&w,SIGNAL(sg_seeeqps()),&seeeqp,SLOT(rcv_seeeqps()));

    //////////////////////////////////////

    ///////////////////////////////////////
    return a.exec();
}
