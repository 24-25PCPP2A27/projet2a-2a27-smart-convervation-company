#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#ifndef CONNECTION_H
#define CONNECTION_H


class Connection
{
    QSqlDatabase db;
public:
    Connection();
    QSqlDatabase getdb(){return db;}
    bool createconnect();
    void closeconnection();
};

#endif // CONNECTION_H
