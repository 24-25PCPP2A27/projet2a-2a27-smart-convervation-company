#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
private:
    int idCl;
    QString nom;
    QString prenom;
    QString email;
    QString dateInscription;
    int age;
    QString sexe;
    QString telephone;
    int nbServiceRecu;

public:
    Client();
    Client(int idCl, const QString& nom, const QString& prenom, const QString& email,
           const QString& dateInscription, int age, const QString& sexe,
           const QString& telephone, int nbServiceRecu);

    // Getters
    int getIdCl() const { return idCl; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    QString getDateInscription() const { return dateInscription; }
    int getAge() const { return age; }
    QString getSexe() const { return sexe; }
    QString getTelephone() const { return telephone; }
    int getNbServiceRecu() const { return nbServiceRecu; }

    // Setters
    void setIdCl(int idCl) { this->idCl = idCl; }
    void setNom(const QString& nom) { this->nom = nom; }
    void setPrenom(const QString& prenom) { this->prenom = prenom; }
    void setEmail(const QString& email) { this->email = email; }
    void setDateInscription(const QString& dateInscription) { this->dateInscription = dateInscription; }
    void setAge(int age) { this->age = age; }
    void setSexe(const QString& sexe) { this->sexe = sexe; }
    void setTelephone(const QString& telephone) { this->telephone = telephone; }
    void setNbServiceRecu(int nbServiceRecu) { this->nbServiceRecu = nbServiceRecu; }

    //  CRUD
    bool ajouter();
    bool mettreAJour();
    bool supprimer(int idCl);
    QSqlQueryModel* afficher();
};

#endif
