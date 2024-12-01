#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "traitementproduit.h"
#include <QMainWindow>
#include <QString>
#include <QSqlQueryModel>
#include <QFileDialog>
#include "arduino.h"
#include <QSerialPortInfo>

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

    void on_pushButton_clicked();

    void on_suprimer_clicked();

    void on_modifier_clicked();

    void on_afficher_clicked();

    //void on_trier_clicked();
     void on_trier_clicked();

     void on_rechercher_clicked();
     void on_pdf_clicked();

     void on_pushButton_3_clicked();

     void on_stats_clicked();

     void on_qrCode_clicked();

     void on_rech_id_textChanged(const QString &arg1);

     void on_demandetT_clicked();

     void updateTemperatureLabel(const QString &temperature);

private:
    Ui::MainWindow *ui;
    traitementproduit T; // Instance de la classe traitementproduit
    Arduino *arduino;

};

#endif // MAINWINDOW_H
