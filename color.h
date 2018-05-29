#ifndef COLOR_H
#define COLOR_H

#include <QWidget>

namespace Ui {
class color;
}

class color : public QWidget
{
    Q_OBJECT

public:
    explicit color(QWidget *parent = 0);
    ~color();

public slots:
    void on_pb_go_clicked();

private:
    Ui::color *ui;
};

#endif // COLOR_H
