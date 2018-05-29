#ifndef FINAL_H
#define FINAL_H

#include <QWidget>
#include "config.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QScrollBar>
#include <QLabel>
//#include "matcheqp.h"
namespace Ui {
class final;
}

class final : public QWidget
{
    Q_OBJECT

public:
    explicit final(QWidget *parent = 0);
    ~final();
    void print_to_table(QString tasks[],double tasksV[],QTableWidget *tw);
    void print_eqps(QTableWidget *tw);
    int add_to_eqptb(int startrow,eqp e[],QTableWidget *tw);
    double cal_time();
    double cal_time_sub(QString tasks[],double tasksV[],eqp e[]);
private slots:
    void on_pb_save_clicked();
    void rcv_final();
private:
    Ui::final *ui;

};

#endif // FINAL_H
