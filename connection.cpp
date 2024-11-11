#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("CPP_Project");
db.setUserName("Malek");
db.setPassword("Freshtrack");

if (db.open()) test=true;
    return  test;
}
void Connection::closeConnection(){db.close();}
