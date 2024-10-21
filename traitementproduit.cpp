#include "traitementproduit.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QVariant>
#include <QDebug>

// Constructeur par défaut
traitementproduit::traitementproduit()
    : id(0), prix(0.0), typeTraitement(""), duree(0), temperatureMin(0.0), temperatureMax(0.0) {
}

// Constructeur avec paramètres
traitementproduit::traitementproduit(int id, double prix, const QString& typeTraitement, int duree, double temperatureMin, double temperatureMax)
    : id(id), prix(prix), typeTraitement(typeTraitement), duree(duree), temperatureMin(temperatureMin), temperatureMax(temperatureMax) {
}

// Getters
int traitementproduit::getId() const {
    return id;
}

double traitementproduit::getPrix() const {
    return prix;
}

QString traitementproduit::getTypeTraitement() const {
    return typeTraitement;
}

int traitementproduit::getDuree() const {
    return duree;
}

double traitementproduit::getTemperatureMin() const {
    return temperatureMin;
}

double traitementproduit::getTemperatureMax() const {
    return temperatureMax;
}

// Setters
void traitementproduit::setId(int id) {
    this->id = id;
}

void traitementproduit::setPrix(double prix) {
    this->prix = prix;
}

void traitementproduit::setTypeTraitement(const QString& typeTraitement) {
    this->typeTraitement = typeTraitement;
}

void traitementproduit::setDuree(int duree) {
    this->duree = duree;
}

void traitementproduit::setTemperatureMin(double temperatureMin) {
    this->temperatureMin = temperatureMin;
}

void traitementproduit::setTemperatureMax(double temperatureMax) {
    this->temperatureMax = temperatureMax;
}

// Méthode toString pour formater les informations de l'objet en chaîne de caractères
QString traitementproduit::toString() const {
    return QString("ID: %1\nPrix: %2\nType de traitement: %3\nDurée: %4 jours\nTempérature min: %5°C\nTempérature max: %6°C")
        .arg(id)
        .arg(prix)
        .arg(typeTraitement)
        .arg(duree)
        .arg(temperatureMin)
        .arg(temperatureMax);
}

// Méthodes CRUD

// Créer
bool traitementproduit::create() {
    QSqlQuery query;
    query.prepare("INSERT INTO traitementproduit (prix, typeTraitement, duree, temperatureMin, temperatureMax) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(prix);
    query.addBindValue(typeTraitement);
    query.addBindValue(duree);
    query.addBindValue(temperatureMin);
    query.addBindValue(temperatureMax);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion:" << query.lastError();
        return false;
    }
    id = query.lastInsertId().toInt(); // Récupérer l'ID généré
    return true;
}

// Lire tous
QList<traitementproduit> traitementproduit::readAll() {
    QList<traitementproduit> produits;
    QSqlQuery query("SELECT * FROM traitementproduit");

    while (query.next()) {
        traitementproduit produit;
        produit.setId(query.value("id").toInt());
        produit.setPrix(query.value("prix").toDouble());
        produit.setTypeTraitement(query.value("typeTraitement").toString());
        produit.setDuree(query.value("duree").toInt());
        produit.setTemperatureMin(query.value("temperatureMin").toDouble());
        produit.setTemperatureMax(query.value("temperatureMax").toDouble());
        produits.append(produit);
    }
    return produits;
}

// Mettre à jour
bool traitementproduit::update() {
    QSqlQuery query;
    query.prepare("UPDATE traitementproduit SET prix = ?, typeTraitement = ?, duree = ?, temperatureMin = ?, temperatureMax = ? WHERE id = ?");
    query.addBindValue(prix);
    query.addBindValue(typeTraitement);
    query.addBindValue(duree);
    query.addBindValue(temperatureMin);
    query.addBindValue(temperatureMax);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour:" << query.lastError();
        return false;
    }
    return true;
}

// Supprimer
bool traitementproduit::remove() {
    QSqlQuery query;
    query.prepare("DELETE FROM traitementproduit WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError();
        return false;
    }
    return true;
}

    query.prepare("UPDATE traitementproduit SET prix = ?, typeTraitement = ?, duree = ?, temperatureMin = ?, temperatureMax = ? WHERE id = ?");
    query.addBindValue(prix);
    query.addBindValue(typeTraitement);
    query.addBindValue(duree);
    query.addBindValue(temperatureMin);
    query.addBindValue(temperatureMax);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour:" << query.lastError();
        return false;
    }
    return true;
}

// Supprimer
bool traitementproduit::remove() {
    QSqlQuery query;
    query.prepare("DELETE FROM traitementproduit WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError();
        return false;
    }
    return true;
}



// Mettre à jour
bool traitementproduit::update() {
    QSqlQuery query;
    query.prepare("UPDATE traitementproduit SET prix = ?, typeTraitement = ?, duree = ?, temperatureMin = ?, temperatureMax = ? WHERE id = ?");
    query.addBindValue(prix);
    query.addBindValue(typeTraitement);
    query.addBindValue(duree);
    query.addBindValue(temperatureMin);
    query.addBindValue(temperatureMax);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour:" << query.lastError();
        return false;
    }
    return true;
}

// Supprimer
bool traitementproduit::remove() {
    QSqlQuery query;
    query.prepare("DELETE FROM traitementproduit WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError();
        return false;
    }
    return true;
}
