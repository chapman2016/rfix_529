#ifndef EQP_H
#define EQP_H
/**
 * 装备类
 **/
#include <QString>

class eqp
{
public:
    QString name;
    //QString size;//体积
    //QString wight;//重量级
    QString doTask;//解决的task eg:"吸水/排水"
    double efficiency;//解决该task的效率
    //QString fdneeds[32];//满足的能力标签
    QString fdneed;//满足的能力标签  ："大型化/运输能力"
    int cnt;//数量
public:
    eqp();
};

#endif // EQP_H
