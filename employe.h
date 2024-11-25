#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
private:

    int idEm;
    QString nom;
    QString prenom;
    QString email;
    QString mot_de_passe;
    QString date_dembau;
    int sal;
    int telephone;
    QString rfid;
    QString lastErrorMessage;

public:

    Employe();
    Employe(int id, QString nom, QString prenom, QString email,
             QString mot_de_passe,  QString date_dembau, int sal, int telephone);

    // Getters
    int getIdEm() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getEmail() const;
    QString getMotDePasse() const;
    QString getDateDembau() const;
    int getSalaire() const;
    int getTelephone() const;

    // Setters
    void setIdEm(int idEm);
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setEmail(const QString &email);
    void setMotDePasse(const QString &mot_de_passe);
    void setDateDembau(const QString &date_dembau);
    void setSalaire(int sal);
    void setTelephone(int telephone);

    void setRfid(const QString &rfidValue) { rfid = rfidValue; }
    QString getRfid() const { return rfid; }

    bool ajouter();
    bool supprimer(int idEm);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercherParNomEtPrenom(const QString &nom, const QString &prenom);


    QString getLastError() const;
    void setLastError(const QString &error);
     QSqlQueryModel* trierParSalaire();
     QMap<QString, double> getSalaryStatistics();
      bool generatePDF(const QString &filePath) const;
      bool checkEmailExists(const QString& email);
         bool resetPassword(const QString& email);
};

#endif // EMPLOYE_H
