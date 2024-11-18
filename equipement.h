#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Equipement {
private:
    int id;
    QString nom;
    QDate dateAquisition;
    QString etat;
    QString localisation;
    QString categorie;
    double prix;

public:
    Equipement();
    Equipement(int id, QString nom, QDate dateAquisition, QString etat,
               QString localisation, QString categorie, double prix);

    // Getters and setters
    QString getNom() const { return nom; }
    int getID() const { return id; }
    QDate getDateAquisition() const { return dateAquisition; }
    QString getEtat() const { return etat; }
    QString getLocalisation() const { return localisation; }
    QString getCategorie() const { return categorie; }
    double getPrix() const { return prix; }

    void setNom(QString n) { nom = n; }
    void setID(int id) { this->id = id; }
    void setDateAquisition(QDate date) { dateAquisition = date; }
    void setEtat(QString e) { etat = e; }
    void setLocalisation(QString loc) { localisation = loc; }
    void setCategorie(QString cat) { categorie = cat; }
    void setPrix(double p) { prix = p; }

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier();

    QSqlQueryModel* rechercher(const QString &nom); // Search function

    // Sorting function by 'etat'
    QSqlQueryModel* afficherParEtat(bool ascending);
    QMap<QString, double> getStatistics();
};

#endif // EQUIPEMENT_H
