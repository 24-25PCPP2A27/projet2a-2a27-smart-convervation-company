#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipement.h" // Include the Equipement class
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_ajouter_equipement_clicked(); // New slot for adding equipment
    void on_pushButton_supprimer_equipement_clicked(); // New slot for deleting equipment

private:
    Ui::MainWindow *ui;
    Equipement Etemp;  // Instance of Equipement
};

#endif // MAINWINDOW_H

