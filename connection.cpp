#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;


    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("sarra");
    db.setPassword("freshtrack");

    if (db.open())
        test = true;

    return test;
}
