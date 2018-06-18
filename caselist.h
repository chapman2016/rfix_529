#ifndef CASELIST_H
#define CASELIST_H

#include <QWidget>
#include <QListWidgetItem>
namespace Ui {
class caseList;
}

class caseList : public QWidget
{
    Q_OBJECT

public:
    explicit caseList(QWidget *parent = 0);
    ~caseList();

private slots:
    void on_opendir_clicked();
    void rcv_caselist();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

signals:
    void see_case(QString name);

private:
    Ui::caseList *ui;
};

#endif // CASELIST_H
