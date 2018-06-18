#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QDebug>
#include "config.h"
#include <QMessageBox>
class database
{
public:
    QSqlDatabase    dbconn;
    QSqlQuery       query;
public:
    database();
    bool login(QString name,QString pass);
    bool readeqp();
    bool addeqp(QString name,QString task,float eft,QString eftstr,
                QString class1,QString class2);
};

#endif // DATABASE_H
