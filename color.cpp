#include "color.h"
#include "ui_color.h"
#include <QStyleFactory>
color::color(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::color)
{
    ui->setupUi(this);
}

color::~color()
{
    delete ui;
}

void color::on_pb_go_clicked()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QColor basiccolor=QColor(ui->le_basic->text());//QColor(53,53,53)//#205c55 //#595959 //#574c45 //#322456 //#323234 //#ffffff
    QColor textcolor=QColor(ui->le_text->text());
    QColor tipcolor=QColor(ui->le_tip->text());
    //QColor textcolor=QColor("#381F21");
    //window->setAutoFillBackground(true);
    QPixmap pixmap = QPixmap("base.jpg").scaled(this->size());
    //    QPalette palette(this->palette());
    //    palette.setBrush(QPalette::Background, QBrush(pixmap));
     //   this->setPalette(palette);

    QPalette palette;
    palette.setColor(QPalette::Window, basiccolor);
    palette.setColor(QPalette::WindowText, textcolor);
    palette.setColor(QPalette::Base, QColor("#505050"));//QColor(15,15,15)
    palette.setColor(QPalette::AlternateBase, basiccolor);
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, textcolor);
    palette.setColor(QPalette::Text, textcolor);
    palette.setColor(QPalette::Button, basiccolor);
    //palette.
    palette.setColor(QPalette::ButtonText, textcolor);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Highlight, tipcolor.lighter());//142,45,197
    palette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(palette);
}
