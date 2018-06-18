#ifndef DMGSCALE2_H
#define DMGSCALE2_H

#include <QWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include <QComboBox>
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

private slots:
    void on_pb_add_clicked();
    void on_pb_del_clicked();
    void on_update_cb_index();

private:
    Ui::dmgscale2 *ui;
};

#endif // DMGSCALE2_H
