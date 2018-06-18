
#ifndef CONFIG_H
#define CONFIG_H
/*****
 *
*/
#include "rdcase.h"
//#include "ca.h"
#include <QString>
//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QTime>
#include <QDebug>
#include "eqp.h"
#include "float.h"
#include <QDoubleSpinBox>
#define MAX_SJTYPE 16
#define MAX_SITE 8
#define MAX_STRUCT 32
#define MAX_TYPE 32
#define MAX_TASK 16
#define MAX_ELE 8
#define IS_ADMIN 101
#define IS_USER 100

//extern rdcase *newcase;
extern QString gl_sjtype[MAX_SJTYPE];//事件类型
extern QString gl_site[MAX_SITE];//发生位置 路段 桥梁 隧道
extern QString gl_struct[MAX_SITE][MAX_STRUCT];//损毁结构
extern QString gl_type[MAX_SITE][MAX_STRUCT][MAX_TYPE];//损毁类型
extern QString gl_ele[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_ELE];//计算要素
extern QString gl_taskName[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_TASK];//分解任务
extern double gl_taskValue[MAX_SITE][MAX_STRUCT][MAX_TYPE][MAX_TASK];//总分解任务
extern QString gl_h_task[32*16];//总任务列表
extern QString gl_h_taskStage[32*16];//标记其使用阶段
extern QString gl_needs[64];//装备能力需求标签 //“s2=多功能化”
extern rdcase *newcase;
extern eqp eqps[512];
extern int usertype;
//extern QSqlDatabase  *m_pDB;


#endif // CONFIG_H
