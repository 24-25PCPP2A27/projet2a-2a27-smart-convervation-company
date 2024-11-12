#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "traitementproduit.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();   // Bouton pour l'ajout
    void on_pb_supp_clicked();      // Bouton pour la suppression
    void on_pushButton_2_clicked(); // Bouton pour la modification

    void on_pushButton_2_clicked(bool checked);

    void on_suprimer_clicked();

    void on_modifier_clicked();

    void on_afficher_clicked();

    void on_trier_clicked();

    void on_rechercher_clicked();

private:
    Ui::MainWindow *ui;
    traitementproduit T;  // Instance de la classe traitementproduit
};

#endif // MAINWINDOW_H
