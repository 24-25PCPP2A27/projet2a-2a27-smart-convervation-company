#include "mainwindow.h"
#include "bienvenue.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "QDebug"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Connection c;

    // Create database connection
    if (!c.createconnect()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
        return -1;
    }

    // Show a success message for the connection
    QMessageBox::information(nullptr, QObject::tr("Database Connected"),
                              QObject::tr("Connection successful.\n"
                                          "Click OK to continue."),
                              QMessageBox::Ok);

    // Display the bienvenue page
    bienvenue b;
    b.show();

       return a.exec();  // Exit the application if bienvenue is closed without logging in
}
