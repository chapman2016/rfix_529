#ifndef INFOINPUT_H
#define INFOINPUT_H

#include <QWidget>

namespace Ui {
class infoinput;
}

class infoinput : public QWidget
{
    Q_OBJECT

public:
    explicit infoinput(QWidget *parent = 0);
    ~infoinput();

private:
    Ui::infoinput *ui;
};

#endif // INFOINPUT_H
