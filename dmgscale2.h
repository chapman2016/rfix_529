#ifndef DMGSCALE2_H
#define DMGSCALE2_H

#include <QWidget>

namespace Ui {
class dmgscale2;
}

class dmgscale2 : public QWidget
{
    Q_OBJECT

public:
    explicit dmgscale2(QWidget *parent = 0);
    ~dmgscale2();

private:
    Ui::dmgscale2 *ui;
};

#endif // DMGSCALE2_H
