#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QDate>

class Produit
{
private:
    int IdPr;
    int Quantite;
    QDate DateReception;
    QDate DatePrevueConservation;
    QString NomProduit;
    QString Statut;  // "prêt", "en cours", "pas encore"
    QString DescriptionProduit;

public:
    Produit();
    Produit(int id, int quantite, QDate dateReception, QDate datePrevueConservation, QString nom, QString statut, QString description);

    // Getters
    int getId() const;
    int getQuantite() const;
    QDate getDateReception() const;
    QDate getDatePrevueConservation() const;
    QString getNomProduit() const;
    QString getStatut() const;
    QString getDescription() const;

    // Setters
    void setId(int id);
    void setQuantite(int quantite);
    void setDateReception(QDate date);
    void setDatePrevueConservation(QDate date);
    void setNomProduit(QString nom);
    void setStatut(QString statut);
    void setDescription(QString description);
};

#endif // PRODUIT_H
