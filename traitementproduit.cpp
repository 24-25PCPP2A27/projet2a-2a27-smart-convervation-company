#include "traitementproduit.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

// Constructeur par défaut
traitementproduit::traitementproduit() {
    id = 0;
    type_traitement = "";
    duree_traitement = 0;
    temp_min = 0;
    temp_max = 0;
    prix = 0.0;
}

// Constructeur avec paramètres
traitementproduit::traitementproduit(int id, QString type_traitement, int duree_traitement, int temp_min, int temp_max, double prix) {
    this->id = id;
    this->type_traitement = type_traitement;
    this->duree_traitement = duree_traitement;
    this->temp_min = temp_min;
    this->temp_max = temp_max;
    this->prix = prix;
}

// Getters
int traitementproduit::getId() { return id; }
QString traitementproduit::getTypeTraitement() { return type_traitement; }
int traitementproduit::getDureeTraitement() { return duree_traitement; }
int traitementproduit::getTempMin() { return temp_min; }
int traitementproduit::getTempMax() { return temp_max; }
double traitementproduit::getPrix() { return prix; }

// Setters
void traitementproduit::setId(int id) { this->id = id; }
void traitementproduit::setTypeTraitement(QString type_traitement) { this->type_traitement = type_traitement; }
void traitementproduit::setDureeTraitement(int duree_traitement) { this->duree_traitement = duree_traitement; }
void traitementproduit::setTempMin(int temp_min) { this->temp_min = temp_min; }
void traitementproduit::setTempMax(int temp_max) { this->temp_max = temp_max; }
void traitementproduit::setPrix(double prix) { this->prix = prix; }

// Ajouter un nouveau traitement
bool traitementproduit::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO TRAITEMENT_DE_PRODUIT (IDTRAIT, PRIX, TYPE, DUREE, TEMP_MIN, TEMP_MAX) "
                    "VALUES (:id, :prix, :type_traitement, :duree_traitement, :temp_min, :temp_max)");

      query.bindValue(":id", id);
      query.bindValue(":prix", prix);
      query.bindValue(":type_traitement", type_traitement);
      query.bindValue(":duree_traitement", duree_traitement);
      query.bindValue(":temp_min", temp_min);
      query.bindValue(":temp_max", temp_max);
    return query.exec();
}

// Supprimer un traitement par id
bool traitementproduit::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM TRAITEMENT_DE_PRODUIT WHERE IDTRAIT = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        return true;
    }
    else
    {

    }
    return query.exec();
}

// Afficher les traitements
QSqlQueryModel* traitementproduit::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRAITEMENT_DE_PRODUIT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Température Min"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Température Max"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}

// Modifier un traitement
bool traitementproduit::modifier(int id, QString type_traitement, int duree_traitement, int temp_min, int temp_max, double prix) {
    QSqlQuery query;
    query.prepare("UPDATE TRAITEMENT_DE_PRODUIT SET TYPE = :type_traitement, DUREE = :duree_traitement, "
                    "TEMP_MIN = :temp_min, TEMP_MAX = :temp_max, PRIX = :prix WHERE IDTRAIT = :id");
      query.bindValue(":id", id);
      query.bindValue(":type_traitement", type_traitement);
      query.bindValue(":duree_traitement", duree_traitement);
      query.bindValue(":temp_min", temp_min);
      query.bindValue(":temp_max", temp_max);
      query.bindValue(":prix", prix);

    return query.exec();
}
QSqlQueryModel* traitementproduit::tri_duree() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRAITEMENT_DE_PRODUIT ORDER BY Durée");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Température Min"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Température Max"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}
QSqlQueryModel* traitementproduit::rechercher(int id) {
QSqlQuery query;
QSqlQueryModel* model = new QSqlQueryModel();
query.prepare("SELECT * FROM TRAITEMENT_DE_PRODUIT WHERE IDTRAIT = :id");
query.bindValue(":id", id);

if (query.exec()) {
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Température Min"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Température Max"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix"));

}
return model;
}
