#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class Employe
{
    QString nom, prenom, email, mot_de_passe, date_dembau;
    int idEm, sal, telephone;

public:

    Employe();
    Employe(int id, QString nom, QString prenom, QString email, QString mot_de_passe, QString date_dembau, int sal, int telephone);  // Parameterized constructor


    int getIdEm() const { return idEm; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    QString getMotDePasse() const { return mot_de_passe; }
    QString getDateDembau() const { return date_dembau; }
    int getSalaire() const { return sal; }
    int getTelephone() const { return telephone; }


    void setIdEm(int idEm) { this->idEm = idEm; }
    void setNom(const QString &nom) { this->nom = nom; }
    void setPrenom(const QString &prenom) { this->prenom = prenom; }
    void setEmail(const QString &email) { this->email = email; }
    void setMotDePasse(const QString &mot_de_passe) { this->mot_de_passe = mot_de_passe; }
    void setDateDembau(const QString &date_dembau) { this->date_dembau = date_dembau; }
    void setSalaire(int sal) { this->sal = sal; }
    void setTelephone(int telephone) { this->telephone = telephone; }



    bool ajouter()
};

#endif // EMPLOYE_H
