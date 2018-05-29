#ifndef SEECASE_H
#define SEECASE_H

#include <QWidget>
//#include <QtSql/QSqlDatabase>
//#include <QtSql/QSqlQuery>
//#include <QTime>
#include <QDebug>
/*
连接数据库
*/
namespace Ui {
class seeCase;
}

class seeCase : public QWidget
{
    Q_OBJECT

public:
    explicit seeCase(QWidget *parent = 0);
    ~seeCase();

private slots:
    void rcv_seecase();

    void on_pb_read_clicked();

private:
    Ui::seeCase *ui;
};

#endif // SEECASE_H
