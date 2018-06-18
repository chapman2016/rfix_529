#include "database.h"
#include <QSqlError>
database::database()
{

    dbconn = QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName("127.0.0.1");//主机名字
    dbconn.setDatabaseName("rfix");//数据库名字
    if(!dbconn.open("root", "")){
        qDebug()<<"db open failed";
        return ;
    }//用户名、密码，成功返回1
    query = (QSqlQuery)dbconn;
    //query.exec("select * from user");//sql语言
   // while(query.next())
    //qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString();
/*
1. exe同级目录增加文件夹和文件：plugins\sqldrivers\qsqlmysql.dll （路径参考：Qt\Qt5.2.0\5.2.0\msvc2010_opengl\plugins\sqldrivers）

2. exe统计目录增加文件：libmysql.dll

3. main.c中main函数改成这样：
QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator() + "plugins");
a.addLibraryPath(strLibPath);
*/
}
bool database::login( QString name,QString pass)
{

    //name="admin";
    //pass="12346";
    query.exec("select * from user where name='"+name+"' and passwd=password('"+pass+"')");
    if(!query.next()){
        //QMessageBox::information(,);
        return 0;
    }
    ;
    qDebug()<<query.value(0).toInt()<<" "<<query.value(1).toString();

    if(query.value(0).toInt()==1)
        usertype=IS_ADMIN;
    else usertype=IS_USER;
    return 1;
}
bool database::readeqp()
{
    query.exec("select * from eqps");
    while(query.next())
    qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString();
    return 1;
}
bool database::addeqp(QString name,QString task,float eft,QString eftstr,
                      QString class1,QString class2)
{
    if(!query.exec("INSERT INTO `eqps` (`name`, `dotask`, `eft`, `eft_str`, `size`, `wight`, `infolizi`, `move`, `sp_ability`, `class1`, `class2`) VALUES"
               "('"+name+"', '"+task+"', '"+QString::number(eft,10,2)+"', '"+eftstr+"', 1, 1, 1, 1, '下', '"+class1+"', '"+class2+"');") )
    {
    QSqlError error=query.lastError();
    qDebug()<<error.text();
    }
    return 1;
}
