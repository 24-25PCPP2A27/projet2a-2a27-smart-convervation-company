#ifndef TRAITEMENTPRODUIT_H
#define TRAITEMENTPRODUIT_H

#include <QString>
#include <QSqlQueryModel>

class traitementproduit {
private:
    int id;
    QString type_traitement;  // Réfrigération, Congélation, Sous-vide, etc.
    int duree_traitement;     // En jours
    int temp_min;
    int temp_max;
    double prix;

public:
    // Constructeurs
    traitementproduit();
    traitementproduit(int id, QString type_traitement, int duree_traitement, int temp_min, int temp_max, double prix);

    // Getters
    int getId();
    QString getTypeTraitement();
    int getDureeTraitement();
    int getTempMin();
    int getTempMax();
    double getPrix();

    // Setters
    void setId(int id);
    void setTypeTraitement(QString type_traitement);
    void setDureeTraitement(int duree_traitement);
    void setTempMin(int temp_min);
    void setTempMax(int temp_max);
    void setPrix(double prix);

    // Méthodes CRUD
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id, QString type_traitement, int duree_traitement, int temp_min, int temp_max, double prix);
    QSqlQueryModel* tri_duree();
    QSqlQueryModel* rechercher(int id);
};

#endif // TRAITEMENTPRODUIT_H
