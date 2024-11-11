#include "mainwindow.h"
#include <QMessageBox>

void MainWindow::on_pushButton_ajouter_equipement_clicked() {
    int id = ui->lineEdit_equipement_id->text().toInt();
    QString nom = ui->lineEdit_equipement_nom->text();
    QDate dateAquisition = ui->dateEdit_equipement_date->date(); // Nouvelle ligne pour la date
    QString etat = ui->comboBox_equipement_etat->currentText(); // Pour l'état (utiliser un combo box)
    QString localisation = ui->lineEdit_equipement_localisation->text(); // Nouvelle ligne pour la localisation
    QString categorie = ui->lineEdit_equipement_categorie->text(); // Nouvelle ligne pour la catégorie
    double prix = ui->lineEdit_equipement_prix->text().toDouble(); // Nouvelle ligne pour le prix

    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix); // Mise à jour du constructeur

    bool test = E.ajouter();
    if (test) {
        ui->tableView_equipement->setModel(Etemp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout d'équipement effectué\n"), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout d'équipement non effectué.\n"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_equipement_clicked() {
    int id = ui->lineEdit_equipement_id->text().toInt();
    bool test = Etemp.supprimer(id);

    if (test) {
        ui->tableView_equipement->setModel(Etemp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression d'équipement effectuée\n"), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression d'équipement non effectuée.\n"), QMessageBox::Cancel);
    }
}
