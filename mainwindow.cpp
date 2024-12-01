#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "traitementproduit.h" // Include your treatment product header file
#include <QMessageBox>
#include <QIntValidator> // If you are using validators
#include <QSqlQueryModel> // Include if you are using QSqlQueryModel
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QString>
#include <QUrl>
#include <QtCore>
#include <QFileDialog>
#include "qrcode.h"
#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_5->setModel(T.afficher());
    ui->tab_6->setModel(T.afficher());

    // Initialize arduino object
    arduino = new Arduino(this); // Initialize the Arduino object
    arduino->openSerialPort();

    // Connect the Arduino's read signal to a slot in MainWindow
    connect(arduino->serial, &QSerialPort::readyRead, this, [=]() {
        arduino->readData(); // Process incoming data
    });
}

MainWindow::~MainWindow()
{
    arduino->closeSerialPort();
    delete arduino; // Free memory
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int id = ui->id->text().toInt();
    QString type = ui->type->currentText();
    int duree = ui->duree->text().toInt();
    int tmpMax = ui->tmpMax->text().toInt();
    int tmpMin = ui->tmpMin->text().toInt();
    float prix = ui->prix->text().toFloat();

    if (ui->id->text().isEmpty() || type.isEmpty() || ui->duree->text().isEmpty() ||
        ui->tmpMax->text().isEmpty() || ui->tmpMin->text().isEmpty() || ui->prix->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }

    if (prix <= 0) {
        QMessageBox::warning(this, "Input Error", "prix must be a positive number.");
        return;
    }

    traitementproduit T(id, type, duree, tmpMax, tmpMin, prix);

    bool test = T.ajouter();
    QMessageBox msgBox;
    if (test) {
        msgBox.setText("Ajout avec succès");
        ui->tab_5->setModel(T.afficher());
        ui->tab_6->setModel(T.afficher());
        ui->id->clear();
        ui->duree->clear();
        ui->tmpMax->clear();
        ui->tmpMin->clear();
        ui->prix->clear();
    } else {
        ui->tab_5->setModel(T.afficher());
        ui->tab_6->setModel(T.afficher());
        msgBox.setText("Echec d'ajout");
    }
    msgBox.exec();
}

void MainWindow::on_suprimer_clicked()
{
    int id = ui->id_supp->text().toInt();
    bool test = T.supprimer(id);
    QMessageBox msgBox;
    if (test) {
        msgBox.setText("Supprimé avec succès");
        ui->tab_5->setModel(T.afficher());
        ui->tab_6->setModel(T.afficher());
    } else {
        msgBox.setText("Echec de suppression");
    }
    msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{
    int id = ui->id_2->text().toInt();
    QString type = ui->type_2->text();
    int duree = ui->duree_2->text().toInt();
    int tmpMax = ui->tmpMax_2->text().toInt();
    int tmpMin = ui->tempMin_2->text().toInt();
    float prix = ui->prix_2->text().toFloat();

    if (ui->id_2->text().isEmpty() || ui->type_2->text().isEmpty() || ui->duree_2->text().isEmpty() ||
        ui->tmpMax_2->text().isEmpty() || ui->tempMin_2->text().isEmpty() || ui->prix_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }

    if (prix <= 0) {
        QMessageBox::warning(this, "Input Error", "prix must be a positive number.");
        return;
    }

    bool test = T.modifier(id, type, duree, tmpMax, tmpMin, prix);
    QMessageBox msgBox;
    if (test) {
        msgBox.setText("Modifié avec succès.");
        ui->tab_5->setModel(T.afficher());
        ui->tab_6->setModel(T.afficher());
    } else {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}

void MainWindow::on_afficher_clicked()
{
    ui->tab_5->setModel(T.afficher());
    ui->tab_6->setModel(T.afficher());
}

void MainWindow::on_trier_clicked()
{
    if (ui->tri_duree->isChecked()) {
        ui->tab_tri->setModel(T.tri_duree());
    }
}

void MainWindow::on_rechercher_clicked()
{
    int id = ui->rech_id->text().toInt();

    bool test = T.rechercher(id);
    QMessageBox msgBox;

    if (test) {
        msgBox.setText("Recherche réussie.");
        ui->tab_rech->setModel(T.rechercher(id));
    } else {
        msgBox.setText("Client inexistant");
    }
    msgBox.exec();
}

void MainWindow::on_pdf_clicked()
{
    T.exportDataToPDF();

}

void MainWindow::on_qrCode_clicked()
{
    using namespace qrcodegen;

    QString value = ui->qr_code_bar->text();

    if (value.isEmpty()) {
        QMessageBox::warning(this, "Error", "QR Code cannot be empty!");
    } else {
        QString text = "Traitement produit with ID: " + value + " is validated.";
        QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

        qint32 sz = qr.getSize();
        QImage im(sz, sz, QImage::Format_RGB32);
        QRgb black = qRgb(9, 13, 12);
        QRgb white = qRgb(255, 255, 255);

        for (int y = 0; y < sz; y++) {
            for (int x = 0; x < sz; x++) {
                im.setPixel(x, y, qr.getModule(x, y) ? black : white);
            }
        }

        ui->qrcodecommande_2->setPixmap(QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));
    }
}

void MainWindow::on_rech_id_textChanged(const QString &arg1)
{
    int id = arg1.toInt();
    ui->tab_5->setModel(T.rechercher(id));
    ui->tab_5->clearSelection();
}

void MainWindow::updateTemperatureLabel(const QString &temperature)
{
    if (temperature.isEmpty()) {
       // ui->label_16->setText("Temperature: Error");
    } else {
        //ui->label_16->setText("Temperature: " + temperature + " °C");
    }
}

void MainWindow::on_demandetT_clicked()
{
    qDebug() << "Button clicked: Requesting temperature from Arduino.";

    if (!arduino || !arduino->serial) {
        qDebug() << "Arduino object or serial pointer is null.";
        //ui->label_16->setText("Error: Arduino not initialized.");
        return;
    }

    if (arduino->serial->isOpen()) {
        arduino->sendTemperatureRequest(); // Send the 'T' command to Arduino
        QThread::msleep(100); // Allow time for response

        if (arduino->serial->canReadLine()) {
            QString response = QString::fromUtf8(arduino->serial->readLine().trimmed());
            qDebug() << "Response from Arduino:" << response;
          //  ui->label_16->setText("Temperature: " + response + " °C");
        } else {
            qDebug() << "No response from Arduino.";
            //ui->label_16->setText("Error: No response.");
        }
    } else {
        //ui->label_16->setText("Serial port not open.");
        qDebug() << "Serial port is not open.";
    }
}
