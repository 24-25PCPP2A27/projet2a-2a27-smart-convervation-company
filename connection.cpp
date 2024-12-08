#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{

}

bool Connection::createconnect() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Set ODBC connection parameters
    db.setDatabaseName("Source_Projet2A"); // ODBC DSN name
    db.setUserName("amen");                // Database username
    db.setPassword("freshtrack");          // Database password

    if (db.open()) {
        qDebug() << "Database connection established successfully.";
        test = true;
    } else {
        qDebug() << "Database connection failed:"
                 << db.lastError().text();
    }

    return test;
}
void Connection::closeconnection(){db.close();}
