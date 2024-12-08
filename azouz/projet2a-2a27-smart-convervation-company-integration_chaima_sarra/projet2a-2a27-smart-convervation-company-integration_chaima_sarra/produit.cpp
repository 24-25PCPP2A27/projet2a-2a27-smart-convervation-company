#include "produit.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QMessageBox>
#include <QDate>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>

// Constructeur par défaut
Produit::Produit() : id(0), nom(""), quantite(0), dateReception(""), dateConservation(""), statut(""), description("") {}

// Constructeur paramétré
Produit::Produit(int idProduit, QString n, int q, QString dr, QString dc, QString s, QString desc)
    : id(idProduit), nom(n), quantite(q), dateReception(dr), dateConservation(dc), statut(s), description(desc) {}

// Ajouter un produit
bool Produit::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO PRODUITS (IDPR, NOM, QUANTITE, DATE_RECEPTION, DATE_CONSERVATION, STATUT, DESCRIPTION) "
                  "VALUES (:ID, :NOM, :QUANTITE, :DATE_RECEPTION, :DATE_CONSERVATION, :STATUT, :DESCRIPTION)");

    query.bindValue(":ID", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":QUANTITE", quantite);
    query.bindValue(":DATE_RECEPTION", dateReception);
    query.bindValue(":DATE_CONSERVATION", dateConservation);
    query.bindValue(":STATUT", statut);
    query.bindValue(":DESCRIPTION", description);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du produit :" << query.lastError().text();
        return false;
    }

    return true;
}

// Mettre à jour un produit
bool Produit::mettreAJour() {
    QSqlQuery query;
    query.prepare("UPDATE PRODUITS SET NOM = :nom, QUANTITE = :quantite, DATE_RECEPTION = :dateReception, "
                  "DATE_CONSERVATION = :dateConservation, STATUT = :statut, DESCRIPTION = :description "
                  "WHERE IDPR = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":quantite", quantite);
    query.bindValue(":dateReception", dateReception);
    query.bindValue(":dateConservation", dateConservation);
    query.bindValue(":statut", statut);
    query.bindValue(":description", description);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du produit :" << query.lastError().text();
        return false;
    }

    return true;
}

// Afficher tous les produits
QSqlQueryModel* Produit::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PRODUITS");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'affichage des produits : " << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Réception"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de Conservation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));

    return model;
}

// Supprimer un produit par ID
bool Produit::supprimer(int idProduit) {
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUITS WHERE IDPR = :id");
    query.bindValue(":id", idProduit);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du produit :" << query.lastError().text();
        return false;
    }

    return true;
}

// Rechercher un produit par ID
QSqlQueryModel* Produit::rechercherParId(int idProduit) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUITS WHERE IDPR = :id");
    query.bindValue(":id", idProduit);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Réception"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de Conservation"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    } else {
        qDebug() << "Erreur lors de la recherche du produit par ID : " << query.lastError().text();
    }

    return model;
}

// Statistiques des produits
QSqlQueryModel* Produit::statistiques() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT STATUT, COUNT(*) AS Nombre FROM PRODUITS GROUP BY STATUT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));

    return model;
}


// Exporter un produit en PDF
bool Produit::exporterPDF(int idProduit)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUITS WHERE IDPR = :id");
    query.bindValue(":id", idProduit);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(nullptr, "Erreur", "Produit introuvable.");
        return false;
    }

    QString nom = query.value("NOM").toString();
    int quantite = query.value("QUANTITE").toInt();
    QString dateReception = query.value("DATE_RECEPTION").toString();
    QString dateConservation = query.value("DATE_CONSERVATION").toString();
    QString statut = query.value("STATUT").toString();
    QString description = query.value("DESCRIPTION").toString();

    QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return false;
    }

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    QPainter painter;

    if (!painter.begin(&printer)) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ouvrir le fichier PDF.");
        return false;
    }

    painter.setFont(QFont("Arial", 12));
    painter.drawText(100, 100, "Informations sur le produit:");
    painter.drawText(100, 130, "Nom : " + nom);
    painter.drawText(100, 160, "Quantité : " + QString::number(quantite));
    painter.drawText(100, 190, "Date de réception : " + dateReception);
    painter.drawText(100, 220, "Date de conservation : " + dateConservation);
    painter.drawText(100, 250, "Statut : " + statut);
    painter.drawText(100, 280, "Description : " + description);

    painter.end();

    return true;
}
