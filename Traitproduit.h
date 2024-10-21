#ifndef TRAITPRODUIT_H
#define TRAITPRODUIT_H
#ifndef TRAITEMENTDEPRODUIT_H
#define TRAITEMENTDEPRODUIT_H
#include <QString>

class TraitementDeProduit {
private:
    int id;
    double prix;
    QString typeTraitement;  // Réfrigération, Congélation, Sous-vide, etc.
    int duree;               // En jours
    double temperatureMin;
    double temperatureMax;

public:
    // Constructeurs
    TraitementDeProduit();
    TraitementDeProduit(int id, double prix, const QString& typeTraitement, int duree, double temperatureMin, double temperatureMax);

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
};

#endif // TRAITEMENTDEPRODUIT_H



#endif // TRAITPRODUIT_H
