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
#include "employe.h"
#include <QDebug>
#include <QTime>

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
    QString email = ui->identifier->text();
        QString password = ui->password->text();
    ui->rfidLabel->setText(rfid);



        if (email.isEmpty() || !email.contains("@") || !email.contains(".")) {
            QMessageBox::warning(this, "Validation Error", "Please enter a valid email address.");
            return;
        }


        if (password.isEmpty() || password.length() > 8) {
            QMessageBox::warning(this, "Validation Error", "Password cannot exceed 8 characters.");
            return;
        }


        Employe employee;
        if (Employe::recupererEmploye(email, password, employee)) {
            if (rfid.isEmpty()) {
                        QMessageBox::warning(this, "RFID Error", "RFID value is empty. Please scan a valid RFID tag.");
                        return;
                    }

                    // Ensure database connection is open
                    if (!QSqlDatabase::database().isOpen()) {
                        QMessageBox::critical(this, "Database Error", "Database connection is not open. Please check your connection.");
                        return;
                    }

                    // Check if RFID exists in the database
                    QSqlQuery query;
                    query.prepare("SELECT COUNT(*) FROM employe WHERE RFID = :rfid");
                    query.bindValue(":rfid", rfid);

                    if (query.exec() && query.next()) {
                        int count = query.value(0).toInt();
                        if (count > 0) {
                            QMessageBox::information(this, "Login Successful", "Bienvenue, " + employee.getNom() + "! RFID recognized.");
                            QString recipientEmail = ui->identifier->text();

                                // Hardcoded sender details
                                QString senderEmail = "arouasarra5@gmail.com";
                                QString senderPassword = "xuwn qgph xgdk gtuy";
                                QString smtpServer = "smtp.gmail.com";
                                QString senderName = "FreshTrack";

                                // Hardcoded subject and message
                                QString emailSubject = "Default Subject";
                                QString emailMessage = "Bienvenue dans notre application.";

                                // Initialize the SMTP object
                                m_smtp = new Smtp(senderEmail,
                                                  senderPassword,
                                                  smtpServer,
                                                  465,
                                                  30000);

                                // Connect the SMTP status signal to the status slot
                                connect(m_smtp, SIGNAL(status(QString)), this, SLOT(slot_emailStatus(QString)));

                                // Send the email
                                m_smtp->sendMail(senderEmail,
                                                 senderName,
                                                 recipientEmail, // Single recipient
                                                 emailSubject,
                                                 emailMessage
                                                );
                            // Navigate to MainWindow and pass the employee object

                            MainWindow *mainWindow = new MainWindow(employee);
                            mainWindow->setAttribute(Qt::WA_DeleteOnClose);// Pass Employe to MainWindow
                            mainWindow->show();

                            this->close();
                        } else {
                            QMessageBox::warning(this, "RFID Not Found", "RFID does not exist in the database. Access denied.");
                        }
                    } else {
                        QMessageBox::critical(this, "Database Error", "Failed to query the database for RFID. Error: " + query.lastError().text());
                        qDebug() << "Query Error: " << query.lastError().text();
                    }
                } else {
                    QMessageBox::warning(this, "Login Failed", "Email or password is incorrect. Please try again.");
                }
}

void bienvenue::on_pushButton_2_clicked()
{
       ui->identifier->clear();
       ui->password->clear();
       ui->rfidLabel->clear();
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
