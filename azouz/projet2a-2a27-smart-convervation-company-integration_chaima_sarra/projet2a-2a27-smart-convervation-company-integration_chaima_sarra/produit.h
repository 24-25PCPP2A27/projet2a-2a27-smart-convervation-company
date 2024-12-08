#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class Produit
{
private:
    int id;
    QString nom;
    int quantite;
    QString dateReception;
    QString dateConservation;
    QString statut;
    QString description;
public:
    // Constructeurs
    Produit();  // Constructeur par défaut
    Produit(int idProduit, QString n, int q, QString dr, QString dc, QString s, QString desc); // Constructeur paramétré

    // Méthodes
    bool ajouter();
    bool mettreAJour();
    QSqlQueryModel* afficher();
    bool supprimer(int idProduit);
    QSqlQueryModel* rechercherParId(int idProduit);
   static QSqlQueryModel* trier();
   static QSqlQueryModel* rechercher(const QString& nom);
   static QSqlQueryModel* statistiques();
    bool exporterPDF(int idProduit);


};

#endif // PRODUIT_H

