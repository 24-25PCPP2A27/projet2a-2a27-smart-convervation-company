#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "traitementproduit.h" // Include your treatment product header file
#include <QMessageBox>
#include <QIntValidator> // If you are using validators
#include <QSqlQueryModel> // Include if you are using QSqlQueryModel
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QString>
#include <QUrl>

#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_5->setModel(T.afficher());
    ui->tab_6->setModel(T.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int id=ui->id->text().toInt();
    QString type=ui->type->text();
    int duree=ui->duree->text().toInt();
    int tmpMax=ui->tmpMax->text().toInt();
    int tmpMin=ui->tmpMin->text().toInt();
    float prix=ui->prix->text().toFloat();
    if (ui->id->text().isEmpty() || ui->type->text().isEmpty() || ui->duree->text().isEmpty() ||
        ui->tmpMax->text().isEmpty() || ui->tmpMin->text().isEmpty() || ui->prix->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

           if (id <= 0) {
               QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
               return;
           }
           if (prix <= 0) {
               QMessageBox::warning(this, "Input Error", "prix must be a positive number.");
               return;
           }
    traitementproduit T(id,type,duree,tmpMax,tmpMin,prix);


    bool test=T.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("done"),
                QObject::tr("ajout avec succés. \n"
                                             "Click Cancel to exit ."), QMessageBox::Cancel);
        ui->tab_5->setModel(T.afficher());
        ui->tab_6->setModel(T.afficher());
        ui->id->clear();
                   ui->id->clear();
                   ui->type->clear();
                   ui->duree->clear();
                   ui->tmpMax->clear();
                   ui->tmpMin->clear();
                   ui->prix->clear();
    }
    else
    { ui->tab_5->setModel(T.afficher());
        ui->tab_6->setModel(T.afficher());
        QMessageBox::critical(nullptr, QObject::tr("failed"),
                QObject::tr("ajout failed. \n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_suprimer_clicked()
{


        int id=ui->id_supp->text().toInt();
  // T.setid(ui->id_supp->text().toInt());
    bool test=T.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {
    msgBox.setText("supprimer avec succes");
    ui->tab_5->setModel(T.afficher());
    ui->tab_6->setModel(T.afficher());
    }
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{
    int id=ui->id_2->text().toInt();
    QString type=ui->type_2->text();
    int duree=ui->duree_2->text().toInt();
    int tmpMax=ui->tmpMax_2->text().toInt();
    int tmpMin=ui->tempMin_2->text().toInt();
    float prix=ui->prix_2->text().toFloat();
    // Validate input fields
    if (ui->id_2->text().isEmpty() || ui->type_2->text().isEmpty() || ui->duree_2->text().isEmpty() ||
        ui->tmpMax_2->text().isEmpty() || ui->tempMin_2->text().isEmpty() || ui->prix_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }
    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }
    if (prix <= 0) {
        QMessageBox::warning(this, "Input Error", "prix must be a positive number.");
        return;
    }


       bool test=T.modifier(id, type, duree,  tmpMax,  tmpMin,prix);
       QMessageBox msgBox;

       if(test){
           msgBox.setText("modifiee avec succes.");
            msgBox.exec();
           ui->tab_5->setModel(T.afficher());
           ui->tab_6->setModel(T.afficher());
       }

       else{
           msgBox.setText("Echec de modification");
           msgBox.exec();
           }
}

void MainWindow::on_afficher_clicked()
{
    ui->tab_5->setModel(T.afficher());
    ui->tab_6->setModel(T.afficher());
}

void MainWindow::on_trier_clicked()
{
        //if (ui->tri_duree->isChecked()) {
            //ui->tab3->setModel(T.tri_duree());
        }




void MainWindow::on_rechercher_clicked() {
{
   traitementproduit T;
//    int id = ui->rech_id->text().toInt();

   // bool test = T.rechercher(id);
    QMessageBox msgBox;

    //if (test) {
        msgBox.setText("Recherche avec succès.");
       // ui->tab_rech->setModel(T.rechercher(id));
    }
    else
    {
        msgBox.setText("Client inexistant");
        msgBox.exec();
    }
}
