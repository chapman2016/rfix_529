#ifndef EDITCONFIG_H
#define EDITCONFIG_H

#include <QWidget>
#include "config.h"
namespace Ui {
class editconfig;
}

class editconfig : public QWidget
{
    Q_OBJECT

public:
    explicit editconfig(QWidget *parent = 0);
    ~editconfig();

private slots:
    void on_pb_read_clicked();
    void rcv_show();

    void on_pb_change_clicked();

private:
    Ui::editconfig *ui;
};

#endif // EDITCONFIG_H
