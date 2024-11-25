#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QString>
#include <QSqlQuery>
#include <QDialog>
#include <QDebug>
#include <QSqlError>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

#include <QFileDialog>
#include <QInputDialog>

#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QAbstractItemModel>

#include "arduino.h"



using namespace QtCharts;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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


MainWindow::~MainWindow()
{
    delete ui;
    delete arduino;  // Clean up Arduino instance
}
void MainWindow::clearInputFields() {
    ui->idEm->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->email->clear();
    ui->mot_de_passe->clear();
    ui->date_dembau->clear();
    ui->salaire->clear();
    ui->telephone->clear();
}
void MainWindow::on_mody_Button_6_clicked() {
    int idEm = ui->idEm->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString email = ui->email->text();
    QString mot_de_passe = ui->mot_de_passe->text();
    QString date_dembau = ui->date_dembau->text();
    int sal = ui->salaire->text().toInt();
    int telephone = ui->telephone->text().toInt();

    // Validate fields
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || mot_de_passe.isEmpty() ||
        date_dembau.isEmpty() || sal <= 0 || telephone <= 0) {
        QMessageBox::warning(this, tr("Input Error"), tr("All fields must be filled correctly."));
        return;
    }

    // Create and add employee
    Employe employe(idEm, nom, prenom, email, mot_de_passe, date_dembau, sal, telephone);
    employe.setRfid(rfid);
    if (employe.ajouter()) {
        QMessageBox::information(this, tr("Success"), tr("Employee added successfully."));
        ui->tableView5->setModel(employe.afficher());
        clearInputFields();
    } else {
        qDebug() << "SQL Error: " << employe.getLastError();
        QMessageBox::critical(this, tr("Failed"), tr("Failed to add employee."));
    }
}

void MainWindow::readDataFromArduino()
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


void MainWindow::on_mody_Button_4_clicked()
{
    int idEm = ui->idEm->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString email = ui->email->text();
    QString mot_de_passe = ui->mot_de_passe->text();
    QString date_dembau = ui->date_dembau->text();
    int sal = ui->salaire->text().toInt();
    int telephone = ui->telephone->text().toInt();

    if (ui->idEm->text().isEmpty() || ui->nom->text().isEmpty() || ui->prenom->text().isEmpty() ||
        ui->email->text().isEmpty() || ui->mot_de_passe->text().isEmpty() || ui->date_dembau->text().isEmpty() ||
        ui->salaire->text().isEmpty() || ui->telephone->text().isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    Employe employe(idEm, nom, prenom, email, mot_de_passe, date_dembau, sal, telephone);
    bool test = employe.modifier();

    if (test) {
        QMessageBox::information(this, "Update Successful", "Employee updated successfully.");
        ui->tableView5->setModel(employe.afficher());
        ui->idEm->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->email->clear();
        ui->mot_de_passe->clear();
        ui->date_dembau->clear();
        ui->salaire->clear();
        ui->telephone->clear();
    } else {
        QMessageBox::critical(this, "Update Failed", "Failed to update employee.");
    }
}
void MainWindow::onTagScanned(const QString &uid)
{
    // Display the scanned UID in a QLabel or handle it as needed
    ui->rfidLabel->setText(uid);  // Ensure rfidLabel exists in your UI
    QMessageBox::information(this, "RFID Tag Scanned", "Tag UID: " + uid);
}
void MainWindow::on_mody_Button_7_clicked()
{
    int idEm = ui->idEm->text().toInt();

    if (ui->idEm->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the employee ID to delete.");
        return;
    }

    Employe employe;
    bool test = employe.supprimer(idEm);

    if (test) {
        QMessageBox::information(this, "Deletion Successful", "The employee has been deleted successfully.");
        ui->tableView5->setModel(employe.afficher());
        ui->idEm->clear();
    } else {
        QMessageBox::critical(this, "Deletion Failed", "Failed to delete the employee.");
    }
}

void MainWindow::on_mody_Button_11_clicked()
{
    Employe employe;
    ui->tableView5->setModel(employe.afficher());
}

void MainWindow::on_mody_Button_10_clicked()
{
        QString nom = ui->nom->text();
        QString prenom = ui->prenom->text();

        if (nom.isEmpty() || prenom.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir les champs Nom et Prénom.");
            return;
        }

        ui->tableView5->setModel(e.rechercherParNomEtPrenom(nom, prenom));
    }


void MainWindow::on_mody_Button_9_clicked()
{
    Employe employe;
        QSqlQueryModel *model = employe.trierParSalaire();

        if (model) {
            ui->tableView5->setModel(model);
            ui->tableView5->show();
            QMessageBox::information(this, "Tri", "La liste des employés a été triée par salaire.");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de trier la liste des employés.");
        }
    }

void MainWindow::on_mody_Button_8_clicked()
{

    if (ui->graphicsView->scene() != nullptr) {
           ui->graphicsView->scene()->clear();
       } else {
           ui->graphicsView->setScene(new QGraphicsScene(this));
       }

       // Récupérer les statistiques des employés
       QMap<QString, double> stats = e.getSalaryStatistics();

       // Préparer les données pour le graphique
       QBarSet *set = new QBarSet("Salaire");
       *set << stats["total"] << stats["average"] << stats["min"] << stats["max"];

       QBarSeries *series = new QBarSeries();
       series->append(set);

       // Configurer le graphique
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques des Salaires");
       chart->setAnimationOptions(QChart::SeriesAnimations);

       // Configurer l'axe X
       QStringList categories;
       categories << "Total" << "Moyenne" << "Minimum" << "Maximum";

       QBarCategoryAxis *axisX = new QBarCategoryAxis();
       axisX->append(categories);
       chart->addAxis(axisX, Qt::AlignBottom);
       series->attachAxis(axisX);

       // Configurer l'axe Y
       QValueAxis *axisY = new QValueAxis();
       axisY->setRange(0, stats["total"] * 1.1);
       chart->addAxis(axisY, Qt::AlignLeft);
       series->attachAxis(axisY);

       // Afficher le graphique
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(521, 401);

       ui->graphicsView->scene()->addWidget(chartView);
       chart->setMargins(QMargins(0, 0, 0, 0));
       chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), QDir::currentPath(), tr("PDF files (*.pdf)"));
        if (filePath.isEmpty()) {
            return;
        }

        QAbstractItemModel *model = ui->tableView5->model();
        if (!model) {
            QMessageBox::critical(this, tr("Error"), tr("No data to export!"));
            return;
        }

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        printer.setPageOrientation(QPageLayout::Landscape);

        QPainter painter;
        if (!painter.begin(&printer)) {
            QMessageBox::critical(this, tr("Error"), tr("Failed to open file for writing."));
            return;
        }

        // Title
        QFont titleFont("Arial", 16, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(QRect(0, 0, printer.pageRect().width(), 100), Qt::AlignCenter, "Liste des Employés");

        // Table headers
        QFont headerFont("Arial", 10, QFont::Bold);
        painter.setFont(headerFont);
        int startX = 50, startY = 150, rowHeight = 30, colWidth = 150;

        for (int col = 0; col < model->columnCount(); ++col) {
            painter.drawText(startX + col * colWidth, startY, model->headerData(col, Qt::Horizontal).toString());
        }

        // Table data
        QFont dataFont("Arial", 9);
        painter.setFont(dataFont);
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QString cellData = model->data(model->index(row, col)).toString();
                painter.drawText(startX + col * colWidth, startY + (row + 1) * rowHeight, cellData);
            }
        }

        painter.end();

        QMessageBox::information(this, tr("Export Successful"), tr("PDF has been saved successfully."));
}

void MainWindow::on_pushButton_2_clicked()
{
    Employe employe;
        QString email = QInputDialog::getText(this, "Mot de passe oublié", "Entrez votre e-mail:");
        if (email.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un e-mail.");
            return;
        }

        if (employe.resetPassword(email)) {
            QMessageBox::information(this, "Succès", "Un nouveau mot de passe a été envoyé à votre e-mail.");
        } else {
            QMessageBox::critical(this, "Erreur", "L'e-mail n'existe pas dans la base de données.");
        }
}
