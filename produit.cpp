#include "produit.h"

Produit::Produit() {}

Produit::Produit(int id, int quantite, QDate dateReception, QDate datePrevueConservation, QString nom, QString statut, QString description)
    : IdPr(id), Quantite(quantite), DateReception(dateReception), DatePrevueConservation(datePrevueConservation), NomProduit(nom), Statut(statut), DescriptionProduit(description) {}

// Getters
int Produit::getId() const { return IdPr; }
int Produit::getQuantite() const { return Quantite; }
QDate Produit::getDateReception() const { return DateReception; }
QDate Produit::getDatePrevueConservation() const { return DatePrevueConservation; }
QString Produit::getNomProduit() const { return NomProduit; }
QString Produit::getStatut() const { return Statut; }
QString Produit::getDescription() const { return DescriptionProduit; }

// Setters
void Produit::setId(int id) { IdPr = id; }
void Produit::setQuantite(int quantite) { Quantite = quantite; }
void Produit::setDateReception(QDate date) { DateReception = date; }
void Produit::setDatePrevueConservation(QDate date) { DatePrevueConservation = date; }
void Produit::setNomProduit(QString nom) { NomProduit = nom; }
void Produit::setStatut(QString statut) { Statut = statut; }
void Produit::setDescription(QString description) { DescriptionProduit = description; }

Produit produit(1, 100, QDate::currentDate(), QDate::currentDate().addDays(30), "Pomme", "En cours", "Une pomme rouge fraîche");

// Ensuite, vous passez cet objet à votre fonction qui ajoute le produit dans la base de données.
ajouterProduit(produit.getId(), produit.getQuantite(), produit.getDateReception().toString("yyyy-MM-dd"),
               produit.getDatePrevueConservation().toString("yyyy-MM-dd"), produit.getNomProduit(),
               produit.getStatut(), produit.getDescription());

QSqlQuery query = lireProduit(1); // Suppose que vous récupérez le produit avec l'ID 1

if (query.next()) {
    Produit produit;
    produit.setId(query.value("IdPr").toInt());
    produit.setQuantite(query.value("Quantite").toInt());
    produit.setDateReception(query.value("DateReception").toDate());
    produit.setDatePrevueConservation(query.value("DatePrevuConservation").toDate());
    produit.setNomProduit(query.value("NomProduit").toString());
    produit.setStatut(query.value("Statut").toString());
    produit.setDescription(query.value("Description").toString());

    // Vous pouvez maintenant utiliser cet objet `Produit` pour afficher ou traiter les données
}

produit.setQuantite(200);  // Par exemple, vous modifiez la quantité
produit.setStatut("Prêt");

// Appel de la fonction pour mettre à jour la base de données
mettreAJourProduit(produit.getId(), produit.getQuantite(), produit.getDateReception().toString("yyyy-MM-dd"),
                   produit.getDatePrevueConservation().toString("yyyy-MM-dd"), produit.getNomProduit(),
                   produit.getStatut(), produit.getDescription());


supprimerProduit(produit.getId());
