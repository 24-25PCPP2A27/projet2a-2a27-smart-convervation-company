#include "mainwindowpr.h"                   // Pour la classe mainwindowpr
#include "ui_mainwindowpr.h"                // Pour l'interface générée par Qt Designer
#include "produit.h"                      // Pour la classe Produit
#include <QMessageBox>                    // Pour les boîtes de dialogue
#include <QIntValidator>                  // Pour la validation des entiers
#include <QSqlQueryModel>                 // Pour la gestion des modèles SQL
#include <QtPrintSupport/QPrinter>        // Pour l'impression (si nécessaire)
#include <QPainter>                       // Pour le dessin dans les vues (si nécessaire)
#include <QDate>                          // Pour manipuler les dates
#include <QRegularExpression>             // Pour la validation des chaînes (email, téléphone)
#include <QSortFilterProxyModel>          // Pour trier les modèles
#include <QFileDialog>                    // Pour la gestion de la sélection de fichiers
#include <QFile>                          // Pour la gestion des fichiers
#include <QTextStream>                    // Pour écrire dans les fichiers
#include <QtCharts>

// Constructeur
mainwindowpr::mainwindowpr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindowpr)
{
    ui->setupUi(this);
}

// Destructeur
mainwindowpr::~mainwindowpr()
{
    delete ui;
}


// Fonction on_modi_Button_3_clicked
void mainwindowpr::on_modi_Button_3_clicked() {
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    int quantite = ui->quantite->text().toInt();
    QString dateReception = ui->dateReception->text();
    QString dateConservation = ui->dateConservation->text();
    QString statut = ui->statut->text();
    QString description = ui->description->text();

    if (ui->id->text().isEmpty() || ui->nom->text().isEmpty() || ui->quantite->text().isEmpty() ||
        ui->dateReception->text().isEmpty() || ui->dateConservation->text().isEmpty() || ui->statut->text().isEmpty() ||
        ui->description->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }
    if (quantite < 0) {
        QMessageBox::warning(this, "Input Error", "Quantity must be a positive number.");
        return;
    }

    // Création et mise à jour du produit
    Produit produit(id, nom, quantite, dateReception, dateConservation, statut, description);
    bool test = produit.mettreAJour();

    if (test) {
        QMessageBox::information(this, "Success", "Product updated successfully.");
        ui->tableView5->setModel(P.afficher());
        ui->id->clear();
        ui->nom->clear();
        ui->quantite->clear();
        ui->dateReception->clear();
        ui->dateConservation->clear();
        ui->statut->clear();
        ui->description->clear();
    } else {
        QMessageBox::critical(this, "Failure", "Failed to update product.");
    }
}

// Fonction on_Afficher_Button_5_clicked
void mainwindowpr::on_Afficher_Button_5_clicked()
{
    QSqlQueryModel *model = P.afficher();

    if (model) {
        ui->tableView5->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Unable to load the data.");
    }
}

// Fonction on_Trier_Button_9_clicked
void mainwindowpr::on_Trier_Button_9_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(P.afficher());
    int colonneTri = 2;  // Assurez-vous que cette colonne existe
    proxyModel->sort(colonneTri, Qt::AscendingOrder);
    ui->tableView5->setModel(proxyModel);
    QMessageBox::information(this, "Sorting", "The products have been sorted successfully.");
}

// Fonction on_Exporter_Button_11_clicked
void mainwindowpr::on_Exporter_Button_11_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Products", "", "CSV Files (*.csv)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Unable to open the file for writing.");
        return;
    }

    QTextStream out(&file);
    QAbstractItemModel *model = ui->tableView5->model();

    // Export column headers
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    out << headers.join(",") << "\n";

    // Export data rows
    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < model->columnCount(); ++col) {
            rowData << model->data(model->index(row, col)).toString();
        }
        out << rowData.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export Successful", "The products have been successfully exported.");
}

void mainwindowpr::on_mody_Button_6_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text().trimmed();
    int quantite = ui->quantite->text().toInt();
    QString dateReception = ui->dateReception->text().trimmed();
    QString dateConservation = ui->dateConservation->text().trimmed();
    QString statut = ui->statut->text().trimmed();
    QString description = ui->description->text().trimmed();

    // Vérification des champs vides
    if (nom.isEmpty() || dateReception.isEmpty() || dateConservation.isEmpty() ||
        statut.isEmpty() || description.isEmpty() || ui->id->text().isEmpty() ||
        ui->quantite->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validation des entrées
    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }
    if (quantite < 0) {
        QMessageBox::warning(this, "Input Error", "Quantity must be a positive number.");
        return;
    }

    // Création et ajout du produit
    Produit produit(id, nom, quantite, dateReception, dateConservation, statut, description);
    bool test = produit.ajouter();

    if (test) {
        QMessageBox::information(this, "Done", "Product added successfully.");
        // Mise à jour de la table et réinitialisation des champs
        ui->tableView5->setModel(P.afficher());
        ui->id->clear();
        ui->nom->clear();
        ui->quantite->clear();
        ui->dateReception->clear();
        ui->dateConservation->clear();
        ui->statut->clear();
        ui->description->clear();
    } else {
        QMessageBox::critical(this, "Failed", "Failed to add product.");
    }
}

void mainwindowpr::on_supp_button_clicked()
{
    int id = ui->id->text().toInt();

    if (ui->id->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the product ID to delete.");
        return;
    }

    Produit produit;
    bool test = produit.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Deletion Successful", "The product has been deleted successfully.");
        ui->tableView5->setModel(P.afficher());
        ui->id->clear();
    } else {
        QMessageBox::critical(this, "Deletion Failed", "Failed to delete the product. Please try again.");
    }
}

void mainwindowpr::on_mody_Button_10_clicked()
{
    int id = ui->id->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid ID.");
        return;
    }

    QSqlQueryModel *model = P.rechercherParId(id);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Not Found", "No product found with this ID.");
        return;
    }

    ui->tableView5->setModel(model);
}



void mainwindowpr::on_Stat_Button_8_clicked()
{

}
