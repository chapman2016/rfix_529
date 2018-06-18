#ifndef DMGSCALE2_H
#define DMGSCALE2_H

#include <QWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include <QComboBox>
#include <QTableWidget>
namespace Ui {
class dmgscale2;
}

class dmgscale2 : public QWidget
{
    Q_OBJECT

public:
    explicit dmgscale2(QWidget *parent = 0);
    ~dmgscale2();
    void cb_insert_data(QComboBox*cb1,QComboBox*cb2,QComboBox*cb3,int ii1,int ii2,int ii3);
    void cb_insert_data_one(QComboBox*cb,int x,int ii1,int ii2,int ii3);
    void cb_insert_data_values(int i1,int i2,int i3,QListWidgetItem *item,QTableWidget *tw);
private slots:
    void on_pb_add_clicked();
    void on_pb_del_clicked();
    void on_update_cb_index();
    void rcv_back_to_me();
    void rcv_dmgscale();
    void on_pb_back_clicked();
    void on_pb_next_clicked();

signals:
    void sg_cal_task();
    void sg_go_back();

private:
    Ui::dmgscale2 *ui;
};

#endif // DMGSCALE2_H
