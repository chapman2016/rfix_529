#ifndef RDCASE_H
#define RDCASE_H
#include <QDateTime>
#include <QString>
#include "eqp.h"

class rdcase
{
public:
    int id;
    QDateTime datetime;
    QDateTime writedatetime;//写入time
    QString place;
    QString sjtype;
    //QString GEOs[32];
    QString GEOs;
    QString dmgSite[32];//发生位置
    QString dmgStruct[32];
    QString dmgType[32];
    QString dmgEleName[32][8];//计算要素名称 最多八种计算要素
    double dmgEle[32][8];//计算要素值
    QString subTask[32][16];//针对每个损毁类型的子任务
    double subtaskV[32][16];
    QString a_tasks[32*16];//<32*16//总需要执行的任务列表
    QString a_taskTag[32*16];//阶段标记
    double a_tasksV[32*16];
    QString s2_tasks[32*16];//<32*16
    double s2_tasksV[32*16];
    QString s3_tasks[32*16];//<32*16
    double s3_tasksV[32*16];
    QString s4_tasks[32*16];//<32*16
    double s4_tasksV[32*16];
    QString s2_needs[32];//需求标签
    QString s3_needs[32];
    QString s4_needs[32];
    eqp s2eqp[64];
    eqp s3eqp[64];
    eqp s4eqp[64];

public:
    rdcase();
    void ok();
};

#endif // RDCASE_H
