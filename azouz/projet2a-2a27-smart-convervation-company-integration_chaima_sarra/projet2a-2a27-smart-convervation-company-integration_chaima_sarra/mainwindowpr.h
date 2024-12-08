
#ifndef mainwindowpr_H
#define mainwindowpr_H

#include <QMainWindow>
#include <QTableView>
#include "produit.h"  // Inclure la classe Produit
namespace Ui {
class mainwindowpr;
}

class mainwindowpr : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindowpr(QWidget *parent = nullptr);
    ~mainwindowpr();

private slots:
    void on_mody_Button_6_clicked();   // Ajouter un produit
    //void on_mody_Button_7_clicked();      // Supprimer un produit
    void on_mody_Button_10_clicked();      // Chercher un produit
    void on_modi_Button_3_clicked();     // Modifier un produit
    void on_Afficher_Button_5_clicked(); // Afficher tous les produits
    void on_Trier_Button_9_clicked();    // Trier les produits
    void on_Exporter_Button_11_clicked(); // Exporter un produit en PDF



    void on_supp_button_clicked();

    //void on_modify_Button_clicked();

    void on_Stat_Button_8_clicked();

private:
    Ui::mainwindowpr *ui;
    Produit P;  // Déclaration de l'objet Produit
    QTableView *produitTable; // Table view pour afficher les produits
};

#endif // mainwindowpr_H

