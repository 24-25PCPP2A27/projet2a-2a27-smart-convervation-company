
#include "equipement.h"

Equipement::Equipement() : id(0), nom(""), dateAquisition(QDate()), etat(""), localisation(""), categorie(""), prix(0.0) {}

Equipement::Equipement(int id, QString nom, QDate dateAquisition, QString etat, QString localisation, QString categorie, double prix) {
    this->id = id;
    this->nom = nom;
    this->dateAquisition = dateAquisition;
    this->etat = etat;
    this->localisation = localisation;
    this->categorie = categorie;
    this->prix = prix;
}

bool Equipement::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (IDTR, NOM, DATE_AQUISITION, ETAT, LOCALISATION, CATEGORIE, PRIX) "
                  "VALUES (:IDTR, :NOM, :DATE_AQUISITION, :ETAT, :LOCALISATION, :CATEGORIE, :PRIX)");

    query.bindValue(":IDTR", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":DATE_AQUISITION", dateAquisition);
    query.bindValue(":ETAT", etat);
    query.bindValue(":LOCALISATION", localisation);
    query.bindValue(":CATEGORIE", categorie);
    query.bindValue(":PRIX", prix);

    return query.exec();
}

QSqlQueryModel* Equipement::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDTR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE D'ACQUISITION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LOCALISATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("PRIX"));
    return model;
}

bool Equipement::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENT WHERE IDTR = :idTR");
    query.bindValue(":idTR", id);
    return query.exec();
}
