#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
signals:
   void offline_use();
private slots:
   void on_pb_offline_clicked();

   void on_pb_login_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
