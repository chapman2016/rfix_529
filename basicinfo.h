#ifndef BASICINFO_H
#define BASICINFO_H

#include <QWidget>
#include <QComboBox>
namespace Ui {
class basicInfo;
}

class basicInfo : public QWidget
{
    Q_OBJECT
public:
    //三个损毁下拉框的坐标和大小
    int x1=40,x2=170,x3=310,
        yn=0,y1=0,y2=0,y3=0,w1=121,w2=131,w3=131,
        hn=22;
    QComboBox *cb1[32],*cb2[32],*cb3[32];
    int cb1index[32],cb2index[32],cb3index[32];
public:
    explicit basicInfo(QWidget *parent = 0);
    ~basicInfo();
    void updateui();
    void closeEvent(QCloseEvent *event);
    void clearcbs();

private slots:
    void rcv_addcase();
    void rcv_basicinfo();
    //void on_pb_addRdDmgType_clicked();
    void rcv_cbchange(int i);
    void rcv_back_to_me();
    //void rcv_setcb3(int i);

    void on_pb_next_clicked();
    void on_pb_cancel_clicked();


signals:
    void sg_dmgscale();

private:
    Ui::basicInfo *ui;
};

#endif // BASICINFO_H
