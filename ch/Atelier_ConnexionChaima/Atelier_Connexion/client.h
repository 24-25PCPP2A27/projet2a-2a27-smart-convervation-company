#ifndef CLIENT_H
#define CLIENT_H

#include "connection.h"
#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDate>

class historique
{
private:
    int ID_ACTION;
    QDateTime DATE_ACTION;
    QString TYPE_ACTION;
    QString DETAILS;

public:
    historique();
    historique(int ID_ACTION , QDateTime DATE_ACTION, QString TYPE_ACTION, QString DETAILS)
    {
        this->ID_ACTION = ID_ACTION;
        this->DATE_ACTION = DATE_ACTION;
        this->TYPE_ACTION = TYPE_ACTION;
        this->DETAILS = DETAILS;
    }

    // Setters
    void setID_ACTION(int i) { ID_ACTION = i; }
    void setDATE_ACTION(QDateTime h) { DATE_ACTION = h; }
    void setTYPE_ACTION(QString g) { TYPE_ACTION = g; }
    void setDETAILS(QString k) { DETAILS = k; }

    // Getters
    int getID_ACTION() const { return ID_ACTION; }
    QDateTime getDATE_ACTION() const { return DATE_ACTION; }
    QString getTYPE_ACTION() const { return TYPE_ACTION; }
    QString getDETAILS() const { return DETAILS; }

    bool Ajouterhistorique();
    QSqlQueryModel *Afficherhistorique();
};

class client
{
private:
    int ID_CL;
    QString NOM;
    QString PRENOM;
    QString EMAIL;
    QDate DATE_INSCRIPTION;
    int AGE;
    QString SEXE;
    QString TELEPHONE;
    int NB_SERVICE_RECU;

public:
    client();
    client(int ID_CL, QString NOM, QString PRENOM, QString EMAIL, QDate DATE_INSCRIPTION, int AGE, QString SEXE, QString TELEPHONE, int NB_SERVICE_RECU)
    {
        this->ID_CL = ID_CL;
        this->NOM = NOM;
        this->PRENOM = PRENOM;
        this->EMAIL = EMAIL;
        this->DATE_INSCRIPTION = DATE_INSCRIPTION;
        this->AGE = AGE;
        this->SEXE = SEXE;
        this->TELEPHONE = TELEPHONE;
        this->NB_SERVICE_RECU = NB_SERVICE_RECU;
    }

    // Setters
    void setID_CL(int id_cl) { ID_CL = id_cl; }
    void setNom(QString nom) { NOM = nom; }
    void setPrenom(QString prenom) { PRENOM = prenom; }
    void setEmail(QString email) { EMAIL = email; }
    void setDateInscription(QDate dateInscription) { DATE_INSCRIPTION = dateInscription; }
    void setAge(int age) { AGE = age; }
    void setSexe(QString sexe) { SEXE = sexe; }
    void setTelephone(QString telephone) { TELEPHONE = telephone; }
    void setNbServiceRecu(int nbServiceRecu) { NB_SERVICE_RECU = nbServiceRecu; }

    // Getters
    int getID_CL() { return ID_CL; }
    QString getNom() { return NOM; }
    QString getPrenom() { return PRENOM; }
    QString getEmail() { return EMAIL; }
    QDate getDateInscription() { return DATE_INSCRIPTION; }
    int getAge() { return AGE; }
    QString getSexe() { return SEXE; }
    QString getTelephone() { return TELEPHONE; }
    int getNbServiceRecu() { return NB_SERVICE_RECU; }

    bool Ajouterclient();
    QSqlQueryModel* Afficherclients();
    bool Modifierclient();
    bool Supprimerclient(const QString &ID_CL);
    QSqlQueryModel *Rechercherclient(const QString &text);
};

#endif // CLIENT_H
