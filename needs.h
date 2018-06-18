#ifndef NEEDS_H
#define NEEDS_H

#include <QWidget>
#include <QListWidget>
namespace Ui {
class needs;
}

class needs : public QWidget
{
    Q_OBJECT

public:
    explicit needs(QWidget *parent = 0);
    ~needs();
    void updateui(QListWidget *lw,QString stage);
signals:
    void sg_matcheqp();
    void sg_back();
    void sg_addlist(int i);
private slots:
    void on_pb_next_clicked();
    void rcv_NeedInput();
    void on_pb_back_clicked();

    void on_pb_add_1_clicked();

    void on_pb_add_2_clicked();

    void on_pb_add_3_clicked();

    void add_to_list(int i);
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_3_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::needs *ui;
};

#endif // NEEDS_H
