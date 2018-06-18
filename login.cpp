#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "color.h"
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap("base.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

}

login::~login()
{
    delete ui;
}

void login::on_pb_offline_clicked()
{
    emit offline_use();
    this->hide();
}

void login::on_pb_login_clicked()
{
    if(1)
        QMessageBox::warning(this,tr("提示信息"),tr("数据库连接失败"));
}
