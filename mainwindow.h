#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"
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
    void update_label();    // Slot pour mettre à jour le label de l'état du buzzer
    void on_pushButton_clicked();  // Bouton pour activer le buzzer
    void on_pushButton_2_clicked();  // Bouton pour désactiver le buzzer

private:
    Ui::MainWindow *ui;
    QByteArray data;  // Variable pour contenir les données reçues de l'Arduino
    Arduino A;  // Objet de la classe Arduino pour gérer la communication série
};

#endif // MAINWINDOW_H

