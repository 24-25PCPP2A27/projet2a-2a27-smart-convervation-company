#include "traitementproduit.h"

// Constructeur par défaut
traitementproduit::traitementproduit()
    : id(0), prix(0.0), typeTraitement(""), duree(0), temperatureMin(0.0), temperatureMax(0.0) {
    // Initialisation par défaut des attributs
}

// Constructeur avec paramètres
traitementproduit::traitementproduit(int id, double prix, const QString& typeTraitement, int duree, double temperatureMin, double temperatureMax)
    : id(id), prix(prix), typeTraitement(typeTraitement), duree(duree), temperatureMin(temperatureMin), temperatureMax(temperatureMax) {
    // Initialisation des attributs avec les paramètres fournis
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
