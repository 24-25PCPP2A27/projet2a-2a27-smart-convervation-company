#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("CPP_Project");
db.setUserName("Malek");
db.setPassword("Freshtrack");

if (db.open())
test=true;





    return  test;
}
void Connection::closeconnection(){db.close();}
