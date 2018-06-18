#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "config.h"
#include <QMainWindow>
#include "color.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateconfig();
    void closeEvent(QCloseEvent *event);

private slots:
    void rcv_mainwindow();
    void on_pb_create_newcase_clicked();
    void on_pushButton_clicked();

    void on_pb_conf_clicked();

    void on_pb_see_saved_clicked();

    void on_pb_see_eqps_clicked();

signals:
    void sg_addCase();
    void sg_config();
   // void sg_seecase();
    void sg_seeeqps();
    void sg_caselist();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
