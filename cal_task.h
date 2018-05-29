#ifndef CAL_TASK_H
#define CAL_TASK_H

#include <QWidget>
#include "rdcase.h"
#include "config.h"
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QTableWidget>
namespace Ui {
class cal_task;
}

class cal_task : public QWidget
{
    Q_OBJECT
public:
    QDoubleSpinBox *s2_sbox[32*16];
    QComboBox *s2_cb[32*16];
    QDoubleSpinBox *s3_sbox[32*16];
    QComboBox *s3_cb[32*16];
    QDoubleSpinBox *s4_sbox[32*16];
    QComboBox *s4_cb[32*16];
    QDoubleSpinBox *a_sbox[32*16];
    QComboBox *a_cb[32*16];
public:
    explicit cal_task(QWidget *parent = 0);
    ~cal_task();
    double sub_calculator(QString formula,double a[8]);
    void printToTable(int stage);
    void save_table(QString tasks[],double tasksV[],QTableWidget *tw);
    void cal_ataskV();//保存时候更新总任务量
private slots:
    void rcv_cal_task();
    void on_pb_next_clicked();
    void on_pb_back_clicked();
    void rcv_back_to_me();

signals:
    void sg_NeedIput();
    void sg_back();
private:
    Ui::cal_task *ui;
};

#endif // CAL_TASK_H
