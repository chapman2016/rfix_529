#ifndef DMGSCALE_H
#define DMGSCALE_H
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QWidget>
#include <QTime>
namespace Ui {
class dmgscale;
}

class dmgscale : public QWidget
{
    Q_OBJECT
public:
    //三个损毁下拉框的坐标和大小
    int x1=0,x2=80,x3=170,x4=270,x5=420,
        yn=0,ye=0,w1=71,w2=71,w3=91,w4=121,w5=121,
        hn=22;
    QComboBox *cb1[32],*cb2[32],*cb3[32];
    int cb1index[32],cb2index[32],cb3index[32];
    QLabel *ele[32][8];
    QDoubleSpinBox *eleV[32][8];
    QTime current_time;
    int sg_lastTime;//上次信号时间
public:
    explicit dmgscale(QWidget *parent = 0);
    ~dmgscale();
    void clearcbs();
    void on_pb_addMore_clicked();
    //void updateleft();
    void prt_cbs();
private slots:
    void rcv_dmgcale();
    void rcv_cbchange(int i);
   // void rcv_cb_clicked();//点击任意一个时

    void add_ele();
    void on_pb_next_clicked();
    void on_pb_add_clicked();
    void on_pb_back_clicked();
    void rcv_back_to_me();

signals:
    void sg_cal_task();
    void sg_go_back();
private:
    Ui::dmgscale *ui;
};

#endif // DMGSCALE_H
