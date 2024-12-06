#include "bienvenue.h"

#include "ui_bienvenue.h"

#include <QMessageBox>

#include "employe.h"

#include "mainwindow.h"

#include <QDebug>

#include <QSqlQuery>

#include <QSqlError>

#include "smtp.h"

#include "arduino.h"

#include "arduinocl.h"

#include "employe.h"

#include "client.h"

#include <QDebug>

#include <QTime>

#include "mdpoublie.h"

bienvenue::bienvenue(QWidget *parent) :

    QDialog(parent),

    ui(new Ui::bienvenue)



{

    ui->setupUi(this);

   // connect(ui->forgetPasswordButton, &QPushButton::clicked, this, &bienvenue::onForgotPasswordClicked);


    // Initialize Arduino for RFID reading

    arduino = new Arduino(this);  // Create an instance of the Arduino class



    if (arduino->isAvailable()) {

        readDataFromArduino();  // Start listening for RFID tags

        qDebug() << "Arduino connected and ready.";

    } else {

        QMessageBox::warning(this, "Arduino Error", "Unable to connect to Arduino.");

        qDebug() << "Arduino is not available.";

    }

   }



void bienvenue::readDataFromArduino()

{



    connect(arduino, &Arduino::tagScanned, this, [this](const QString &uid) {

        rfid = uid;  // Store the scanned UID

        ui->rfidLabel->setText(rfid);  // Update the UI label with the scanned UID

        QMessageBox::information(this, "RFID Tag Scanned", "Tag UID: " + rfid);

    });



    if (!arduino->isAvailable()) {

        QMessageBox::warning(this, "Arduino Error", "Arduino device not available. Ensure it is properly connected.");

        return;

    }



    qDebug() << "Listening for RFID tags...";

}



void bienvenue::onTagScanned(const QString &uid)

{

    // Display the scanned UID in a QLabel or handle it as needed

    ui->rfidLabel->setText(uid);  // Ensure rfidLabel exists in your UI

    QMessageBox::information(this, "RFID Tag Scanned", "Tag UID: " + uid);

}

bienvenue::~bienvenue()

{

    delete ui;

        //this->setStyleSheet("background-image: url(:/photo.jpg);");

    delete arduino;

}



void bienvenue::on_pushButton_clicked()

{
    //arduino->write_arduino("notfound");
    QString email = ui->identifier->text();

    QString password = ui->password->text();

    QString post = ui->post->text();

    QString rfid = ui->rfidLabel->text(); // RFID input



    // Ensure the database connection is open

    if (!QSqlDatabase::database().isOpen()) {

        QMessageBox::critical(this, "Database Error", "Database connection is not open. Please check your connection.");

        return;

    }



    // Declare an employee object here

    Employe employee;



    // Validate by RFID if provided

    if (!rfid.isEmpty()) {

        QSqlQuery query;

        query.prepare("SELECT POST, NOM, PRENOM FROM employe WHERE RFID = :rfid");

        query.bindValue(":rfid", rfid);



        if (query.exec() && query.next()) {

            QString retrievedPost = query.value("POST").toString();

            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            QString dataToSend = nom + "," + prenom + "\n"; // Format: "id,name"


            arduino->write_arduino(dataToSend.toUtf8());

            QMessageBox::information(this, "Login Successful", "Bienvenue, " + nom + " (" + retrievedPost + ")");



            // Retrieve employee details into employee object

            if (employee.recupererEmployeByRFID(rfid, employee)) {

                // Navigate to the appropriate window based on POST value

                if (retrievedPost == "employe") {


                    employee.setpost(retrievedPost);
                    MainWindow *mainWindow = new MainWindow(employee);  // Pass the employee object

                    mainWindow->setAttribute(Qt::WA_DeleteOnClose);

                    mainWindow->show();

                    this->close();


                } else if (retrievedPost == "client") {

                    employee.setpost(retrievedPost);

                    // Create and show the client window dynamically, passing the same employee object

                    MainWindow *mainWindow = new MainWindow(employee);  // Pass employee to MainWindow

                    mainWindow->setAttribute(Qt::WA_DeleteOnClose);

                    mainWindow->show();

                    this->close();

                            // Close bienvenue window

                             // This will close the current window (bienvenue)

                } else {

                    QMessageBox::warning(this, "Invalid Post", "Unrecognized post: " + retrievedPost);

                }

            } else {

                QMessageBox::warning(this, "Login Failed", "Failed to retrieve employee data.");

            }

            return;

        } else {
            arduino->write_arduino("notfound");
            QMessageBox::warning(this, "RFID Not Found", "Invalid RFID tag. Access denied.");

            return;

        }

    }



    // Continue with email and password logic if RFID is not used

    if (email.isEmpty() || !email.contains("@") || !email.contains(".")) {

        QMessageBox::warning(this, "Validation Error", "Please enter a valid email address.");

        return;

    }



    if (password.isEmpty() || password.length() > 8) {

        QMessageBox::warning(this, "Validation Error", "Password cannot exceed 8 characters.");

        return;

    }



    if (post == "employe") {

        if (Employe::recupererEmploye(email, password, employee)) {

            QMessageBox::information(this, "Login Successful", "Bienvenue, " + employee.getNom());
            QString dataToSend = email + "," + password + "\n"; // Format: "id,name"
            arduino->write_arduino(dataToSend.toUtf8());

            // Navigate to MainWindow

            MainWindow *mainWindow = new MainWindow(employee);  // Pass employee to MainWindow

            mainWindow->setAttribute(Qt::WA_DeleteOnClose);

            mainWindow->show();

            this->close();

        } else {

            QMessageBox::warning(this, "Login Failed", "Invalid email, password, or post. Please try again.");

        }

    } else if (post == "client") {

        // Open the client-spec ific window
        QString dataToSend = email + "," + password + "\n"; // Format: "id,name"
        arduino->write_arduino(dataToSend.toUtf8());
        QMessageBox::information(this, "Login Successful", "Bienvenue, Client!");

        MainWindow *mainWindow = new MainWindow(employee);  // Pass employee to MainWindow

        mainWindow->setAttribute(Qt::WA_DeleteOnClose);

        mainWindow->show();

        this->close();

    } else {
           arduino->write_arduino("notfound");
        QMessageBox::warning(this, "Login Failed", "Invalid email, password, or post. Please try again.");

    }}









void bienvenue::on_pushButton_2_clicked()

{

       ui->identifier->clear();

       ui->password->clear();

       ui->rfidLabel->clear();

        ui->post->clear();

}

void bienvenue::on_identifier_cursorPositionChanged(int oldPos, int newPos)

{

    // Handle the cursor position change here if necessary

    qDebug() << "Cursor moved from" << oldPos << "to" << newPos;

}









void bienvenue::slot_emailStatus(QString message)

{

    if (message == "Message sent") {

        QMessageBox::information(this, "Email Status", "Email sent successfully.");

    } else {

        QMessageBox::critical(this, "Email Status", "Failed to send email: " + message);

    }

}



void bienvenue::on_pushButton_3_clicked()

{



        mdpoublie forgotPasswordDialog(this);

        forgotPasswordDialog.exec();

    }
