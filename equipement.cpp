#include "equipement.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMap>

Equipement::Equipement() : id(0), nom(""), dateAquisition(QDate()), etat(""), localisation(""), categorie(""), prix(0) {}

Equipement::Equipement(int id, QString nom, QDate dateAquisition, QString etat, QString localisation, QString categorie, int prix,QString image)
    : id(id), nom(nom), dateAquisition(dateAquisition), etat(etat), localisation(localisation), categorie(categorie), prix(prix) ,image(image){}

bool Equipement::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (IDEQ, NOM, DATE_AQUISITION, ETAT, LOCALISATION, CATEGORIE, PRIX,IMAGE) "
                  "VALUES (:IDEQ, :NOM, :DATE_AQUISITION, :ETAT, :LOCALISATION, :CATEGORIE, :PRIX,:IMAGE)");

    query.bindValue(":IDEQ", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":DATE_AQUISITION", dateAquisition); // Date format as string
    query.bindValue(":ETAT", etat);
    query.bindValue(":LOCALISATION", localisation);
    query.bindValue(":CATEGORIE", categorie);
    query.bindValue(":PRIX", prix);
    query.bindValue(":IMAGE", image);

    return query.exec();
}

QSqlQueryModel* Equipement::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDEQ"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_AQUISITION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LOCALISATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("PRIX"));
    return model;
}

bool Equipement::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENT WHERE IDEQ = :IDEQ");
    query.bindValue(":IDEQ", id);
    return query.exec();
}

bool Equipement::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENT SET NOM = :NOM, DATE_AQUISITION = :DATE_AQUISITION, ETAT = :ETAT, "
                  "LOCALISATION = :LOCALISATION, CATEGORIE = :CATEGORIE, PRIX = :PRIX ,IMAGE=:image "
                  "WHERE IDEQ = :IDEQ");

    query.bindValue(":IDEQ", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":DATE_AQUISITION", dateAquisition); // Date as string
    query.bindValue(":ETAT", etat);
    query.bindValue(":LOCALISATION", localisation);
    query.bindValue(":CATEGORIE", categorie);
    query.bindValue(":PRIX", prix);
    query.bindValue(":image", image);
    return query.exec();
}

QSqlQueryModel* Equipement::rechercher(const QString &nom) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EQUIPEMENT WHERE NOM LIKE :nom");
    query.bindValue(":nom", "%" + nom + "%");  // Use wildcards for partial match
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDEQ"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date d'Acquisition"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Localisation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}

// Sorting function by 'etat'
QSqlQueryModel* Equipement::afficherParEtat(bool ascending) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = ascending
            ? "SELECT * FROM EQUIPEMENT ORDER BY ETAT ASC"
            : "SELECT * FROM EQUIPEMENT ORDER BY ETAT DESC";

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDEQ"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date d'Acquisition"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Localisation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}

QMap<QString, double> Equipement::getStatistics()
{
    QMap<QString, double> stats;
    QSqlQuery query;

    // Total quantity of items (SUM of QUANTITE_EN_STOCK)
    query.exec("SELECT SUM(QUANTITE_EN_STOCK) FROM EQUIPEMENT");
    if (query.next()) {
        stats["total_quantity"] = query.value(0).toDouble();  // Sum of quantities in stock
    }

    // Average quantity of items (AVG of QUANTITE_EN_STOCK)
    query.exec("SELECT AVG(QUANTITE_EN_STOCK) FROM EQUIPEMENT");
    if (query.next()) {
        stats["average_quantity"] = query.value(0).toDouble();  // Average of quantities in stock
    }

    // Minimum quantity of items (MIN of QUANTITE_EN_STOCK)
    query.exec("SELECT MIN(QUANTITE_EN_STOCK) FROM EQUIPEMENT");
    if (query.next()) {
        stats["min_quantity"] = query.value(0).toDouble();  // Minimum quantity in stock
    }

    // Maximum quantity of items (MAX of QUANTITE_EN_STOCK)
    query.exec("SELECT MAX(QUANTITE_EN_STOCK) FROM EQUIPEMENT");
    if (query.next()) {
        stats["max_quantity"] = query.value(0).toDouble();  // Maximum quantity in stock
    }

    // Total price of items (SUM of PRIX)
    query.exec("SELECT SUM(PRIX) FROM EQUIPEMENT");
    if (query.next()) {
        stats["total_price"] = query.value(0).toDouble();  // Sum of prices
    }

    // Average price of items (AVG of PRIX)
    query.exec("SELECT AVG(PRIX) FROM EQUIPEMENT");
    if (query.next()) {
        stats["average_price"] = query.value(0).toDouble();  // Average price
    }

    // Optionally, you could also calculate MIN and MAX for price if needed
    query.exec("SELECT MIN(PRIX) FROM EQUIPEMENT");
    if (query.next()) {
        stats["min_price"] = query.value(0).toDouble();  // Minimum price
    }

    query.exec("SELECT MAX(PRIX) FROM EQUIPEMENT");
    if (query.next()) {
        stats["max_price"] = query.value(0).toDouble();  // Maximum price
    }

    return stats;
}
