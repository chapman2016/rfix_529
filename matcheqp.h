#ifndef MATCHEQP_H
#define MATCHEQP_H

#include <QWidget>
#include "config.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QScrollBar>
namespace Ui {
class matcheqp;
}

class matcheqp : public QWidget
{
    Q_OBJECT
public:
    eqp tempe[256];
    eqp tempeqp2[256];
    int nowstage;//2 3 4
    bool cal=false;//是否点击过计算建议数量
public:
    explicit matcheqp(QWidget *parent = 0);
    ~matcheqp();
    void match(QString tasks[],eqp e[]);//匹配装备任务名称
    void print_to_table(QString tasks[],double tasksV[],QTableWidget *tw);//打印任务列表
    void print_eqp(eqp e[],QTableWidget *tw);//
    void saveeqp(eqp e[]);//保存勾选的装备
    void cal_cnt(QString tasks[],double tasksV[],eqp e[]);//计算建议数量
    void cal_time(QString tasks[], double tasksV[], eqp e[]);//计算各阶段作业时间
    void print_task_eqp();
    void save_table(QString tasks[], double tasksV[], QTableWidget *tw);
    void cal_ataskV();

signals:
    void sg_final();
    void sg_back();
private slots:
    void on_pb_next_clicked();
    void rcv_matcheqp();
    void rcv_matcheqp1();
    void on_pb_conferm_clicked();

    void on_pb_realnext_clicked();

    void on_pb_back_clicked();

    void on_pb_flush_time_clicked();

private:
    Ui::matcheqp *ui;
};

#endif // MATCHEQP_H
