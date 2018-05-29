#include "mainwindow.h"
#include <QApplication>
#include "basicinfo.h"
#include "dmgscale.h"
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
//#include "ui_base.h"
#include <QStyleFactory>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    //QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);

    QApplication a(argc, argv);
   // QWidget *ba=(QWidget*)new base;
   // ba->show();
    MainWindow w;
    w.show();
    editconfig ec;
    //ec.show();
    QObject::connect(&w,SIGNAL(sg_config()),&ec,SLOT(rcv_show()));
    basicInfo bi;
    //bi.setParent(ba);

    //ba->setLayout(bi.layout());
    QObject::connect(&w,SIGNAL(sg_addCase()),&bi,SLOT(rcv_addcase()));
    dmgscale ds;
    //ds.setParent(ba);
    QObject::connect(&bi,SIGNAL(sg_dmgscale()),&ds,SLOT(rcv_dmgcale()));
    QObject::connect(&ds,SIGNAL(sg_go_back()),&bi,SLOT(rcv_back_to_me()));
    //Form f;
    //f.show();
    //infoinput ip;
    //ip.show();
    cal_task ct;
    QObject::connect(&ds,SIGNAL(sg_cal_task()),&ct,SLOT(rcv_cal_task()));
    QObject::connect(&ct,SIGNAL(sg_back()),&ds,SLOT(rcv_back_to_me()));
    needs nd;
    QObject::connect(&ct,SIGNAL(sg_NeedIput()),&nd,SLOT(rcv_NeedInput()));
    QObject::connect(&nd,SIGNAL(sg_back()),&ct,SLOT(rcv_back_to_me()));
    seeCase sc;
    //sc.show();
    QObject::connect(&w,SIGNAL(sg_seecase()),&sc,SLOT(rcv_seecase()));
    matcheqp me;
    QObject::connect(&nd,SIGNAL(sg_matcheqp()),&me,SLOT(rcv_matcheqp()));
    QObject::connect(&me,SIGNAL(sg_back()),&nd,SLOT(rcv_NeedInput()));
    final fn;
    QObject::connect(&me,SIGNAL(sg_final()),&fn,SLOT(rcv_final()));

    seeeqps seeeqp;
    QObject::connect(&w,SIGNAL(sg_seeeqps()),&seeeqp,SLOT(rcv_seeeqps()));

    //////////////////////////////////////

    ///////////////////////////////////////
    return a.exec();
}
