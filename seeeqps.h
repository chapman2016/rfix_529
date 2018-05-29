#ifndef SEEEQPS_H
#define SEEEQPS_H

#include <QWidget>

namespace Ui {
class seeeqps;
}

class seeeqps : public QWidget
{
    Q_OBJECT

public:
    explicit seeeqps(QWidget *parent = 0);
    ~seeeqps();

private slots:
    void on_pb_read_clicked();
    void rcv_seeeqps();

    void on_Pb_add_eqp_clicked();

    void on_pb_search_clicked();

private:
    Ui::seeeqps *ui;
};

#endif // SEEEQPS_H
