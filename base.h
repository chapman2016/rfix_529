#ifndef BASE_H
#define BASE_H

#include <QWidget>

namespace Ui {
class base;
}

class base : public QWidget
{
    Q_OBJECT

public:
    explicit base(QWidget *parent = 0);
    ~base();

private:
    Ui::base *ui;
};

#endif // BASE_H
