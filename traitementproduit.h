#ifndef TRAITEMENTPRODUIT_H
#define TRAITEMENTPRODUIT_H

#include <QString>

class traitementproduit {
private:
    int id;
    double prix;
    QString typeTraitement;  // Réfrigération, Congélation, Sous-vide, etc.
    int duree;               // En jours
    double temperatureMin;
    double temperatureMax;

public:
    // Constructeurs
    traitementproduit();
    traitementproduit(int id, double prix, const QString& typeTraitement, int duree, double temperatureMin, double temperatureMax);

    // Getters
    int getId() const;
    double getPrix() const;
    QString getTypeTraitement() const;
    int getDuree() const;
    double getTemperatureMin() const;
    double getTemperatureMax() const;

    // Setters
    void setId(int id);
    void setPrix(double prix);
    void setTypeTraitement(const QString& typeTraitement);
    void setDuree(int duree);
    void setTemperatureMin(double temperatureMin);
    void setTemperatureMax(double temperatureMax);

    // Méthodes supplémentaires
    QString toString() const;
};

#endif // TRAITEMENTPRODUIT_H
