#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QString>
#include <QSqlQuery>
#include <QDialog>
#include <QDebug>
#include <QSqlError>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include "client.h" // Include the client header
#include "connection.h"
#include <QFileDialog>
#include <QInputDialog>

#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QAbstractItemModel>
#include <QDebug>
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QPdfWriter>
#include <QAxObject>
#include <QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QChartView>
#include <QVBoxLayout>
#include "arduino.h"
#include "employe.h"


using namespace QtCharts;


MainWindow::MainWindow(const Employe &employe,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
  currentEmploye(employe)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
  ui->tableView_3->setModel(Etemp.afficher());
    populateFields();
    // Initialize Arduino for RFID reading


    if(currentEmploye.getpost()=="client"){

        QStackedWidget* stackedWidget = ui->stackedWidget_2;
        QWidget* page = stackedWidget->widget(1);
        QTableView* tableView = page->findChild<QTableView*>("tableView");

                if (tableView && db.isOpen()) {
                    client client;
                    tableView->setModel(client.Afficherclients());
                    tableView->resizeColumnsToContents();
                    tableView->horizontalHeader()->setStretchLastSection(true);}

                connect(ui->gostat, &QPushButton::clicked, this, [this]() { navigateToPage(3); });
                connect(ui->back, &QPushButton::clicked, this, [this]() { navigateToPage(1); });
                connect(ui->backemp, &QPushButton::clicked, this, [this]() { navigateToPage(1); });
               // connect(ui->goback, &QPushButton::clicked, this, [this]() { navigateToPage(1); });

                // PDF connect
                connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::exportToPDF);
                // Excel connect
                connect(ui->excel, &QPushButton::clicked, this, &MainWindow::exportToExcel);
                // Search connect
                connect(ui->search_bar, &QLineEdit::textChanged, this, &MainWindow::Rechercherclient);
                // Sort connect
                connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sortComboBox_currentIndexChanged(int)));


                QDate selectedDate = ui->calendarWidget->selectedDate();
                updateCalendarAndEventDetails(selectedDate);
    }
    else if(currentEmploye.getpost()=="employe"){

        QStackedWidget* stackedWidget = ui->stackedWidget_2;
        QWidget* page = stackedWidget->widget(0);

    }
   else if(currentEmploye.getpost()=="equipement"){

        QStackedWidget* stackedWidget = ui->stackedWidget_2;
        QWidget* page = stackedWidget->widget(4);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    delete arduino;  // Clean up Arduino instance

}


void MainWindow::arduinoEq() {
QByteArray data = A.read_from_arduino();
QString etat=QString::fromUtf8(data).trimmed();
if(etat=="E")
{
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENT SET ETAT = :ETAT "
                  "WHERE IDEQ = 1");
    query.bindValue(":ETAT","en panne");
query.exec();
QMessageBox::warning(this, "Problem","EQUIPEMENT 1 est en panne (temperature elevee)");
ui->tableView->setModel(Etemp.afficher());  // Initially show all records

}


}
void MainWindow::clearInputFields() {
    ui->idEm->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->email->clear();
    ui->mot_de_passe->clear();
    ui->date_dembau->clear();
    ui->salaire->clear();
    ui->telephone->clear();
    ui->post->clear();
    ui->rfidLabel->clear();

}
void MainWindow::on_mody_Button_6_clicked() {
    int idEm = ui->idEm->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString email = ui->email->text();
    QString mot_de_passe = ui->mot_de_passe->text();
    QString date_dembau = ui->date_dembau->text();
    int sal = ui->salaire->text().toInt();
    QString  telephone = ui->telephone->text();
    QString post = ui->post->text();
    QString rfid = ui->rfidLabel->text();
    // Validate fields
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || mot_de_passe.isEmpty() ||
        date_dembau.isEmpty() || sal <= 0 || telephone.isEmpty()|| post.isEmpty() || rfid.isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("All fields must be filled correctly."));
        return;
    }

    // Create and add employee
    Employe employe(idEm, nom, prenom, email, mot_de_passe, date_dembau, sal, telephone,post);
    employe.setRfid(rfid);
    if (employe.ajouter()) {
        QMessageBox::information(this, tr("Success"), tr("Employee added successfully."));
        ui->tableView5->setModel(employe.afficher());
        clearInputFields();
    } else {
        qDebug() << "SQL Error: " << employe.getLastError();
        QMessageBox::critical(this, tr("Failed"), tr("Failed to add employee."));
    }
}

void MainWindow::readDataFromArduino()
{
    connect(arduino, &Arduino::tagScanned, this, [this](const QString &uid) {
        rfid = uid;  // Store the scanned UID
        ui->rfidLabel->setText(rfid);  // Update the UI label with the scanned UID
        QMessageBox::information(this, "RFID Tag Scanned", "Tag UID: " + rfid);
    });


    if (!arduino->isAvailable()) {
        QMessageBox::warning(this, "Arduino Error", "Arduino device not available. Ensure it is properly connected.");
        return;
    }

    qDebug() << "Listening for RFID tags...";
}


void MainWindow::on_mody_Button_4_clicked()
{
    int idEm = ui->idEm->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString email = ui->email->text();
    QString mot_de_passe = ui->mot_de_passe->text();
    QString date_dembau = ui->date_dembau->text();
    int sal = ui->salaire->text().toInt();
    QString telephone = ui->telephone->text();
    QString post= ui->post->text();
    QString rfid= ui->rfidLabel->text();

    if (ui->idEm->text().isEmpty() || ui->nom->text().isEmpty() || ui->prenom->text().isEmpty() ||
        ui->email->text().isEmpty() || ui->mot_de_passe->text().isEmpty() || ui->date_dembau->text().isEmpty() ||
        ui->salaire->text().isEmpty() || ui->telephone->text().isEmpty() || ui->post->text().isEmpty() || ui->rfidLabel->text().isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    Employe employe(idEm, nom, prenom, email, mot_de_passe, date_dembau, sal, telephone,post );
    bool test = employe.modifier();

    if (test) {
        QMessageBox::information(this, "Update Successful", "Employee updated successfully.");
        ui->tableView5->setModel(employe.afficher());
        ui->idEm->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->email->clear();
        ui->mot_de_passe->clear();
        ui->date_dembau->clear();
        ui->salaire->clear();
        ui->telephone->clear();
        ui->rfidLabel->clear();
    } else {
        QMessageBox::critical(this, "Update Failed", "Failed to update employee.");
    }
}
void MainWindow::onTagScanned(const QString &uid)
{
    // Display the scanned UID in a QLabel or handle it as needed
    ui->rfidLabel->setText(uid);  // Ensure rfidLabel exists in your UI
    QMessageBox::information(this, "RFID Tag Scanned", "Tag UID: " + uid);
}
void MainWindow::on_mody_Button_7_clicked()
{
    int idEm = ui->idEm->text().toInt();

    if (ui->idEm->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the employee ID to delete.");
        return;
    }

    Employe employe;
    bool test = employe.supprimer(idEm);

    if (test) {
        QMessageBox::information(this, "Deletion Successful", "The employee has been deleted successfully.");
        ui->tableView5->setModel(employe.afficher());
        ui->idEm->clear();
    } else {
        QMessageBox::critical(this, "Deletion Failed", "Failed to delete the employee.");
    }
}

void MainWindow::on_mody_Button_11_clicked()
{
    Employe employe;
    ui->tableView5->setModel(employe.afficher());
}

void MainWindow::on_mody_Button_10_clicked()
{
        QString nom = ui->nom->text();
        QString prenom = ui->prenom->text();

        if (nom.isEmpty() || prenom.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir les champs Nom et Prénom.");
            return;
        }

        ui->tableView5->setModel(e.rechercherParNomEtPrenom(nom, prenom));
    }


void MainWindow::on_mody_Button_9_clicked()
{
    Employe employe;
        QSqlQueryModel *model = employe.trierParSalaire();

        if (model) {
            ui->tableView5->setModel(model);
            ui->tableView5->show();
            QMessageBox::information(this, "Tri", "La liste des employés a été triée par salaire.");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de trier la liste des employés.");
        }
    }

void MainWindow::on_mody_Button_8_clicked()
{

    if (ui->graphicsView->scene() != nullptr) {
           ui->graphicsView->scene()->clear();
       } else {
           ui->graphicsView->setScene(new QGraphicsScene(this));
       }

       // Récupérer les statistiques des employés
       QMap<QString, double> stats = e.getSalaryStatistics();

       // Préparer les données pour le graphique
       QBarSet *set = new QBarSet("Salaire");
       *set << stats["total"] << stats["average"] << stats["min"] << stats["max"];

       QBarSeries *series = new QBarSeries();
       series->append(set);

       // Configurer le graphique
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques des Salaires");
       chart->setAnimationOptions(QChart::SeriesAnimations);

       // Configurer l'axe X
       QStringList categories;
       categories << "Total" << "Moyenne" << "Minimum" << "Maximum";

       QBarCategoryAxis *axisX = new QBarCategoryAxis();
       axisX->append(categories);
       chart->addAxis(axisX, Qt::AlignBottom);
       series->attachAxis(axisX);

       // Configurer l'axe Y
       QValueAxis *axisY = new QValueAxis();
       axisY->setRange(0, stats["total"] * 1.1);
       chart->addAxis(axisY, Qt::AlignLeft);
       series->attachAxis(axisY);

       // Afficher le graphique
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(521, 401);

       ui->graphicsView->scene()->addWidget(chartView);
       chart->setMargins(QMargins(0, 0, 0, 0));
       chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), QDir::currentPath(), tr("PDF files (*.pdf)"));
        if (filePath.isEmpty()) {
            return;
        }

        QAbstractItemModel *model = ui->tableView5->model();
        if (!model) {
            QMessageBox::critical(this, tr("Error"), tr("No data to export!"));
            return;
        }

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        printer.setPageOrientation(QPageLayout::Landscape);

        QPainter painter;
        if (!painter.begin(&printer)) {
            QMessageBox::critical(this, tr("Error"), tr("Failed to open file for writing."));
            return;
        }

        // Title
        QFont titleFont("Arial", 16, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(QRect(0, 0, printer.pageRect().width(), 100), Qt::AlignCenter, "Liste des Employés");

        // Table headers
        QFont headerFont("Arial", 10, QFont::Bold);
        painter.setFont(headerFont);
        int startX = 50, startY = 150, rowHeight = 30, colWidth = 150;

        for (int col = 0; col < model->columnCount(); ++col) {
            painter.drawText(startX + col * colWidth, startY, model->headerData(col, Qt::Horizontal).toString());
        }

        // Table data
        QFont dataFont("Arial", 9);
        painter.setFont(dataFont);
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QString cellData = model->data(model->index(row, col)).toString();
                painter.drawText(startX + col * colWidth, startY + (row + 1) * rowHeight, cellData);
            }
        }

        painter.end();

        QMessageBox::information(this, tr("Export Successful"), tr("PDF has been saved successfully."));
}


void MainWindow::populateFields()
{
    ui->idEm->setText(QString::number(currentEmploye.getIdEm()));
    ui->nom->setText(currentEmploye.getNom());
    ui->prenom->setText(currentEmploye.getPrenom());
    ui->email->setText(currentEmploye.getEmail());
    ui->mot_de_passe->setText(currentEmploye.getMotDePasse());
    ui->date_dembau->setText(currentEmploye.getDateDembau());
    ui->salaire->setText(QString::number(currentEmploye.getSalaire()));
    ui->telephone->setText(currentEmploye.getTelephone());
    ui->post->setText(currentEmploye.getpost());
    ui->rfidLabel->setText(currentEmploye.getpost());
}

void MainWindow::on_mody_Button_12_clicked()
{
    ui->idEm->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->email->clear();
    ui->mot_de_passe->clear();
    ui->date_dembau->clear();
    ui->telephone->clear();
    ui->salaire->clear();
    ui->post->clear();
    ui->rfidLabel->clear();

}
void MainWindow::on_ajouter_clicked()
    {
        QString nom = ui->nom->text();
        QString prenom = ui->prnom->text();
        QString email = ui->mail->text();
        QDate dateInscription = ui->date_inscription->date();
        QString ageStr = ui->age->text();
        int age = ageStr.toInt();
        QString sexe = ui->gender->currentText();
        QString tel = ui->nbrphone->text();
        QString nbServiceRecuStr = ui->nb_service_recu->text();
        int nbServiceRecu = nbServiceRecuStr.toInt();

        QDate dateReception= ui->DATE_RECEPTION_DATE->date();
        QDate dateConservation = ui->DATE_CONSERVATION_DATE->date();


        // Input validation

        QRegExp telRx("^\\d{8}$"); // Exactly 8 digits
        QRegExp emailRx("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$"); // Email format

        if (!telRx.exactMatch(tel)) {
            QMessageBox::critical(this, tr("Erreur"), tr("Le téléphone doit comporter exactement 8 chiffres."), QMessageBox::Cancel);
        } else if (!emailRx.exactMatch(email)) {
            QMessageBox::critical(this, tr("Erreur"), tr("L'email doit être au format valide."), QMessageBox::Cancel);
        } else if (dateInscription > QDate::currentDate()) {
            QMessageBox::critical(this, tr("Erreur"), tr("La date d'inscription ne peut pas être ultérieure à aujourd'hui."), QMessageBox::Cancel);
        } else {
            client client(0, nom, prenom, email, dateInscription, age, sexe, tel, nbServiceRecu, dateReception, dateConservation);

            if (client.Ajouterclient()) {
                ui->tableView->setModel(client.Afficherclients());
                QMessageBox::information(this, tr("Succès"), tr("Ajout effectué."), QMessageBox::Cancel);

                ui->nom->clear();
                ui->prnom->clear();
                ui->mail->clear();
                ui->date_inscription->setDate(QDate::currentDate());
                ui->age->clear();
                ui->gender->setCurrentIndex(-1);
                ui->nbrphone->clear();
                ui->nb_service_recu->clear();
                ui->DATE_RECEPTION_DATE->setDate(QDate::currentDate());
                ui->DATE_CONSERVATION_DATE->setDate(QDate::currentDate());
            } else {
                QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de l'ajout du client."), QMessageBox::Cancel);
            }
        }

        QDate selectedDate = ui->calendarWidget->selectedDate();
        updateCalendarAndEventDetails(selectedDate);
    }



    void MainWindow::on_tableView_activated(const QModelIndex &index)
    {
        if (!index.isValid()) {
            qDebug() << "Invalid index";
            return;
        }
        QString value = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();

        Connection c;
        c.closeconnection();
        QSqlQuery qry;

        qry.prepare("SELECT NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION FROM client WHERE ID_CL = :ID_CL");
        qry.bindValue(":ID_CL", value);

        if(qry.exec()) {
            if(qry.next()) {
                ui->id->setText(value);
                ui->nom->setText(qry.value(0).toString());
                ui->prnom->setText(qry.value(1).toString());
                ui->mail->setText(qry.value(2).toString());
                ui->date_inscription->setDate(qry.value(3).toDate());
                ui->age->setText(qry.value(4).toString());
                ui->gender->setCurrentText(qry.value(5).toString());
                ui->nbrphone->setText(qry.value(6).toString());
                ui->nb_service_recu->setText(qry.value(7).toString());
                ui->DATE_RECEPTION_DATE->setDate(qry.value(8).toDate());
                ui->DATE_CONSERVATION_DATE->setDate(qry.value(9).toDate());

                // Switch to the modify page
                ui->stackedWidget->setCurrentIndex(0);
            }
        }

        // Close the database connection
        c.closeconnection();
        QDate selectedDate = ui->calendarWidget->selectedDate();
        updateCalendarAndEventDetails(selectedDate);
    }


    void MainWindow::on_modifier_clicked()
    {
        QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

        if (selectedIndexes.size() == 0) {
            QMessageBox::warning(this, tr("Aucune sélection"), tr("Veuillez sélectionner une ligne à modifier."), QMessageBox::Ok);
            return;
        } else if (selectedIndexes.size() > 1) {
            QMessageBox::warning(this, tr("Sélection multiple"), tr("Veuillez sélectionner une seule ligne à modifier."), QMessageBox::Ok);
            return;
        }

        int idCl = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

        QString nom = ui->nom->text();
        QString prenom = ui->prnom->text();
        QString email = ui->mail->text();
        QDate dateInscription = ui->date_inscription->date();
        int age = ui->age->text().toInt();
        QString sexe = ui->gender->currentText();
        QString tel = ui->nbrphone->text();
        int nbServiceRecu = ui->nb_service_recu->text().toInt();

        QDate dateReception= ui->DATE_RECEPTION_DATE->date();
        QDate dateConservation = ui->DATE_CONSERVATION_DATE->date();

        if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || sexe.isEmpty() || tel.isEmpty() || age == 0 || nbServiceRecu == 0) {
            QMessageBox::critical(this, tr("Erreur"), tr("Veuillez remplir tous les champs."), QMessageBox::Cancel);
            return;
        }

        client client(idCl, nom, prenom, email, dateInscription, age, sexe, tel, nbServiceRecu, dateReception, dateConservation);

        if (client.Modifierclient()) {
            ui->tableView->setModel(client.Afficherclients());
            QMessageBox::information(this, tr("Succès"), tr("Modification effectuée."), QMessageBox::Cancel);
            ui->nom->clear();
            ui->prnom->clear();
            ui->mail->clear();
            ui->date_inscription->setDate(QDate::currentDate());
            ui->age->clear();
            ui->gender->setCurrentIndex(-1);
            ui->nbrphone->clear();
            ui->nb_service_recu->clear();
            ui->DATE_RECEPTION_DATE->setDate(QDate::currentDate());
            ui->DATE_CONSERVATION_DATE->setDate(QDate::currentDate());
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la modification du client."), QMessageBox::Cancel);
        }
        QDate selectedDate = ui->calendarWidget->selectedDate();
        updateCalendarAndEventDetails(selectedDate);
    }

    void MainWindow::on_supprimer_clicked()
    {
        int id_cl = ui->id->text().toInt();

        // Check if an ID is selected
        if (id_cl == 0) {
            QMessageBox::warning(this, tr("No Selection"), tr("Please select a client to delete."), QMessageBox::Ok);
            return;
        }

        // Confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm Deletion"),
                                      tr("Are you sure you want to delete this client?"),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply != QMessageBox::Yes) {
            return;
        }

        // Create a Client instance and set the ID to delete
        client cli;
        cli.setID_CL(id_cl);

        // Retrieve client details to be deleted
        QSqlQuery query;
        query.prepare("SELECT NOM, PRENOM FROM client WHERE ID_CL = :ID_CL");
        query.bindValue(":ID_CL", id_cl);
        if (!query.exec() || !query.next()) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Failed to retrieve client details."),
                                  QMessageBox::Cancel);
            return;
        }

        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        cli.setNom(nom);
        cli.setPrenom(prenom);
        QString string = QString::number(id_cl);
        // Attempt deletion
        bool success = cli.Supprimerclient(string);


        // Prepare history details
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString TYPE_ACTION = "Suppression";
        QString DETAILS = QString("Client with ID %1 has been deleted.").arg(id_cl);

        if (success) {
            // Update the table view
            ui->tableView->setModel(cli.Afficherclients());


            // Clear form fields
            ui->id->clear();
            ui->nom->clear();
            ui->prnom->clear();
            ui->mail->clear();
            ui->date_inscription->setDate(QDate::currentDate());
            ui->age->clear();
            ui->gender->setCurrentIndex(-1);
            ui->nbrphone->clear();
            ui->nb_service_recu->clear();
            ui->DATE_RECEPTION_DATE->setDate(QDate::currentDate());
            ui->DATE_CONSERVATION_DATE->setDate(QDate::currentDate());

            // Log the deletion in history
            historique histo(0, currentDateTime, TYPE_ACTION, DETAILS);
            // Uncomment if you want to add history logging
            // if (histo.Ajouterhistorique()) {
            //     ui->historyTableView->setModel(histo.Afficherhistorique());
            // }
        } else {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Failed to delete the client."),
                                  QMessageBox::Cancel);
        }
    }


    void MainWindow::exportToPDF()
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), QDir::currentPath(), tr("PDF files (*.pdf)"));
        if (filePath.isEmpty()) {
            return;
        }

        QAbstractItemModel *model = ui->tableView->model();
        if (!model) {
            qDebug() << "Model not set for the table view!";
            return;
        }

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        printer.setOrientation(QPrinter::Landscape);

        QSizeF pageSize = printer.pageRect().size();
        pageSize.rwidth() *= 1.3; // Increase width by 30%
        pageSize.rheight() *= 1.4; // Increase height by 40%
        printer.setPageSize(QPageSize(pageSize, QPageSize::Point));

        QPainter painter;
        painter.begin(&printer);
        bool success = true;

        int columnPadding = 80;

        QFont titleFont = painter.font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        painter.setFont(titleFont);
        painter.setPen(Qt::red);
        QString titleText = "TABLEAU DE GESTION DES CLIENTS";
        int titleWidth = painter.fontMetrics().width(titleText);
        int titleXPos = (printer.pageRect().width() - titleWidth) / 2;
        int titleYPos = 50;
        painter.drawText(titleXPos, titleYPos, titleText);

        // Draw header row
        int headerYPos = 100;
        QFont headerFont = painter.font();
        headerFont.setPointSize(8);
        headerFont.setBold(true);
        painter.setFont(headerFont);
        painter.setPen(Qt::black);
        for (int col = 0; col < model->columnCount(); ++col) {
            QString headerData = model->headerData(col, Qt::Horizontal).toString();
            if (headerData == "Action") {
                continue;
            }
            int xPos = col * 100 + (col + 1) * columnPadding;
            painter.drawText(xPos, headerYPos, headerData);
        }

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QModelIndex index = model->index(row, col);
                QString data = model->data(index).toString();
                if (model->headerData(col, Qt::Horizontal).toString() == "Action") {
                    continue;
                }
                int xPos = col * 100 + (col + 1) * columnPadding;
                int yPos = (row + 1) * 20 + headerYPos;

                painter.drawText(xPos, yPos, data);
            }
        }

        painter.end();

        if (printer.newPage() || success) {
            QMessageBox::information(this, "Export Status", "Your data has been exported successfully.");
        } else {
            QMessageBox::critical(this, "Export Status", "Failed to export data to PDF.");
        }
    }

    void MainWindow::exportToExcel()
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", "", "*.xlsx");
        if (!fileName.isEmpty()) {
            QAxObject* excel = new QAxObject("Excel.Application");
            QAxObject* workbooks = excel->querySubObject("Workbooks");
            QAxObject* workbook = workbooks->querySubObject("Add");
            QAxObject* sheets = workbook->querySubObject("Worksheets");
            QAxObject* sheet = sheets->querySubObject("Item(int)", 1);

            QAbstractItemModel *model = ui->tableView->model();

            QAxObject* rangeTitle = sheet->querySubObject("Range(const QString&)", "A1:C1");
            rangeTitle->dynamicCall("Merge()"); // Merge cells for the title
            rangeTitle->setProperty("Value", "TABLEAU DE GESTION DES CLIENTS");
            QAxObject* titleFont = rangeTitle->querySubObject("Font");
            titleFont->setProperty("Bold", true);
            titleFont->setProperty("Color", QColor(Qt::red));

            for (int col = 0; col < model->columnCount(); ++col) {
                QString headerData = model->headerData(col, Qt::Horizontal).toString();

                if (headerData == "Action") {
                    continue;
                }

                QAxObject* cell = sheet->querySubObject("Cells(int,int)", 2, col + 1);
                cell->dynamicCall("SetValue(const QVariant&)", headerData);
                // Apply bold font to header cell
                QAxObject* headerFont = cell->querySubObject("Font");
                headerFont->setProperty("Bold", true);
            }

            for (int i = 0; i < model->rowCount(); ++i) {
                int excelCol = 1;
                for (int j = 0; j < model->columnCount(); ++j) {
                    if (model->headerData(j, Qt::Horizontal).toString() == "Action") {
                        continue;
                    }

                    QModelIndex index = model->index(i, j);
                    QString data = model->data(index).toString();
                    QAxObject* cell = sheet->querySubObject("Cells(int,int)", i + 3, excelCol);
                    cell->dynamicCall("SetValue(const QVariant&)", data);
                    excelCol++;
                }
            }

            QAxObject* usedRange = sheet->querySubObject("UsedRange");
            if (usedRange) {
                QAxObject* rows = usedRange->querySubObject("Rows");
                QAxObject* columns = usedRange->querySubObject("Columns");
                if (rows && columns) {
                    rows->setProperty("RowHeight", 20);
                    columns->setProperty("ColumnWidth", 20);
                }
                delete usedRange;
            }

            workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));
            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");
            delete excel;

            QMessageBox::information(this, "Export Status", "Your data has been exported successfully.");
        } else {
            QMessageBox::critical(this, "Export Status", "Failed to export data to Excel.");
        }
    }

    void MainWindow::Rechercherclient(const QString &text)
    {
        client c;
        QSqlQueryModel *model = c.Rechercherclient(text);
        ui->tableView->setModel(model);
    }


    void MainWindow::displayCharts_clientByGender()
    {
        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->setBackgroundBrush(QBrush(Qt::white));

        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        QSqlQuery query;
        query.exec("SELECT SEXE, COUNT(*) FROM client GROUP BY SEXE");

        int totalClients = 0;

        while (query.next()) {
            QString gender = query.value(0).toString();
            int count = query.value(1).toInt();
            series->append(gender + ": " + QString::number(count), count);
            totalClients += count;
        }

        chart->addSeries(series);
        chart->setTitle(QString("<div style='text-align: center;'><font size='4'>Total number of clients = %1</font></div><div style='text-align: center;'><font size='4'>Clients by Gender</font></div>").arg(totalClients));

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(700, 550);

        QPixmap pixmap = chartView->grab();
        ui->stat_gender->setPixmap(pixmap);
    }
    QSqlQueryModel *clientModel;

    void MainWindow::on_sortComboBox_currentIndexChanged(int index)
    {
        clientModel = new QSqlQueryModel(); // Create a new model each time

        QString queryStr;

        switch (index) {
            case 1: // Sort by Prénom (A-Z)
                queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION FROM client ORDER BY PRENOM ASC";
                break;
            case 2: // Sort by ID_CL (Ascending)
                queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION FROM client ORDER BY ID_CL ASC";
                break;
            case 3: // Sort by Date Inscription (Oldest to Newest)
                queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION FROM client ORDER BY DATE_INSCRIPTION ASC";
                break;
            default:
                queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION FROM client";
                break;
        }

        clientModel->setQuery(queryStr);

        clientModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CL"));
        clientModel->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        clientModel->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        clientModel->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
        clientModel->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_INSCRIPTION"));
        clientModel->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));
        clientModel->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
        clientModel->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));
        clientModel->setHeaderData(8, Qt::Horizontal, QObject::tr("NB_SERVICE_RECU"));
        clientModel->setHeaderData(9, Qt::Horizontal, QObject::tr("DATE_RECEPTION"));
        clientModel->setHeaderData(10, Qt::Horizontal, QObject::tr("DATE_CONSERVATION"));

        ui->tableView->setModel(clientModel);
    }


    void MainWindow::on_gostat_clicked()
    {
        displayCharts_clientByGender();
        ui->stackedWidget->setCurrentIndex(1);
    }




    void MainWindow::navigateToPage(int pageIndex)
    {
        ui->stackedWidget_2->setCurrentIndex(pageIndex);
    }

    void MainWindow::on_gocalendar_clicked()
    {
        QDate selectedDate = ui->calendarWidget->selectedDate();
        updateCalendarAndEventDetails(selectedDate);

        ui->stackedWidget_2->setCurrentIndex(2);
    }

    void MainWindow::on_back_fromcalendr_4_clicked()
    {
        ui->stackedWidget->setCurrentIndex(1);
    }

    void MainWindow::on_calendarWidget_clicked(const QDate &date)
    {
        // Create a QSqlQuery to fetch the idClient for the clicked date from the database
        QSqlQuery idQuery;
        idQuery.prepare("SELECT ID_CL FROM client WHERE DATE_RECEPTION >= ? AND DATE_RECEPTION < ?");
        QDateTime startOfDay = QDateTime(date);
        QDateTime endOfDay = startOfDay.addDays(1);
        idQuery.addBindValue(startOfDay);
        idQuery.addBindValue(endOfDay);

        if (!idQuery.exec()) {
            qDebug() << "Failed to execute query:" << idQuery.lastError().text();
            return;
        }

        if (idQuery.next()) {
            // Extract idClient from the query result
            QString idClient = idQuery.value(0).toString();

            // Format the string with HTML to make "ID:" red
            QString formattedIDText = "<span style='color: red;'>ID:</span> " + idClient;

            // Create a QSqlQuery to fetch all information related to the retrieved idClient
            QSqlQuery query;
            query.prepare("SELECT NOM, PRENOM, EMAIL, AGE, SEXE, TELEPHONE, DATE_RECEPTION, DATE_CONSERVATION FROM client WHERE ID_CL = ?");
            query.addBindValue(idClient);

            if (!query.exec()) {
                qDebug() << "Failed to execute query:" << query.lastError().text();
                return;
            }

            if (query.next()) {
                // Extract fields from the query result with HTML formatting
                QString nomClient = "<span style='color: red;'>Nom:</span> " + query.value(0).toString();
                QString prenom = "<span style='color: red;'>Prenom:</span> " + query.value(1).toString();
                QString email = "<span style='color: red;'>Email:</span> " + query.value(2).toString();
                QString age = "<span style='color: red;'>Age:</span> " + query.value(3).toString();
                QString sex = "<span style='color: red;'>Sex:</span> " + query.value(4).toString();
                QString telephone = "<span style='color: red;'>Telephone:</span> " + query.value(5).toString();

                QDate datereception = query.value(6).toDate();
                QString formattedDateReception = "<span style='color: red;'>Date Reception:</span> " + datereception.toString("dd/MM/yyyy");

                QDate dateconservation = query.value(7).toDate();
                QString formattedDateConservation = "<span style='color: red;'>Date Conservation:</span> " + dateconservation.toString("dd/MM/yyyy");

                // Set the retrieved values to corresponding labels
                ui->ID_client_label_cal->setText(formattedIDText);
                ui->NOM_client_label_cal->setText(nomClient);
                ui->PRENOM_client_label_cal->setText(prenom);
                ui->EMAIL_client_label_cal->setText(email);
                ui->TELEPHONE_client_label_cal->setText(telephone);
                ui->SEX_client_label_cal->setText(sex);
                ui->AGE_client_label_cal->setText(age);

                ui->D_RECEPTION_client_label_cal->setText(formattedDateReception); // Format with date
                ui->D_CONSERVATION_client_label_cal->setText(formattedDateConservation);// Format with

                // Make labels visible
                ui->ID_client_label_cal->setVisible(true);
                ui->NOM_client_label_cal->setVisible(true);
                ui->PRENOM_client_label_cal->setVisible(true);
                ui->EMAIL_client_label_cal->setVisible(true);
                ui->TELEPHONE_client_label_cal->setVisible(true);
                ui->SEX_client_label_cal->setVisible(true);
                ui->AGE_client_label_cal->setVisible(true);
                ui->D_RECEPTION_client_label_cal->setVisible(true);
                ui->D_CONSERVATION_client_label_cal->setVisible(true);


                //ui->no_events_today_image->setVisible(false);
            }
        } else {
            // No data found for the clicked date, hide labels
            ui->ID_client_label_cal->setVisible(false);
            ui->NOM_client_label_cal->setVisible(false);
            ui->PRENOM_client_label_cal->setVisible(false);
            ui->EMAIL_client_label_cal->setVisible(false);
            ui->TELEPHONE_client_label_cal->setVisible(false);
            ui->SEX_client_label_cal->setVisible(false);
            ui->AGE_client_label_cal->setVisible(false);
            ui->D_RECEPTION_client_label_cal->setVisible(false);
            ui->D_CONSERVATION_client_label_cal->setVisible(false);

            //ui->no_events_today_image->setVisible(true);
        }
    }


    void MainWindow::updateCalendarAndEventDetails(const QDate &date) {
        // Clear existing date text formats in the calendar
        ui->calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

        // Create a QSqlQuery to fetch the DATE_RECEPTION values from the database
        QSqlQuery calendarQuery("SELECT DATE_RECEPTION FROM client");

        // Iterate through the query results
        while (calendarQuery.next()) {
            // Extract the DATE_RECEPTION value from the query
            QDate dateReception = calendarQuery.value(0).toDate();

            // Set the color for the date in the calendar
            QTextCharFormat format;
            format.setBackground(Qt::green); // Set background color to green
            ui->calendarWidget->setDateTextFormat(dateReception, format);
        }

        // Create a QSqlQuery to fetch the idClient for the clicked date from the database
        QSqlQuery idQuery;
        idQuery.prepare("SELECT ID_CL FROM client WHERE DATE_RECEPTION >= ? AND DATE_RECEPTION < ?");
        QDateTime startOfDay = QDateTime(date);
        QDateTime endOfDay = startOfDay.addDays(1);
        idQuery.addBindValue(startOfDay);
        idQuery.addBindValue(endOfDay);

        if (!idQuery.exec()) {
            qDebug() << "Failed to execute query:" << idQuery.lastError().text();
            return;
        }

        if (idQuery.next()) {
            // Extract idClient from the query result
            QString idClient = idQuery.value(0).toString();

            // Format the string with HTML to make "ID:" red
            QString formattedIDText = "<span style='color: red;'>ID:</span> " + idClient;

            // Create a QSqlQuery to fetch all information related to the retrieved idClient
            QSqlQuery query;
            query.prepare("SELECT NOM, PRENOM, EMAIL, AGE, SEXE, TELEPHONE, DATE_RECEPTION, DATE_CONSERVATION FROM client WHERE ID_CL = ?");
            query.addBindValue(idClient);

            if (!query.exec()) {
                qDebug() << "Failed to execute query:" << query.lastError().text();
                return;
            }

            if (query.next()) {
                // Extract fields from the query result with HTML formatting
                QString nomClient = "<span style='color: red;'>Nom:</span> " + query.value(0).toString();
                QString prenom = "<span style='color: red;'>Prenom:</span> " + query.value(1).toString();
                QString email = "<span style='color: red;'>Email:</span> " + query.value(2).toString();
                QString age = "<span style='color: red;'>Age:</span> " + query.value(3).toString();
                QString sex = "<span style='color: red;'>Sex:</span> " + query.value(4).toString();
                QString telephone = "<span style='color: red;'>Telephone:</span> " + query.value(5).toString();

                QDate datereception = query.value(6).toDate();
                QString formattedDateReception = "<span style='color: red;'>Date Reception:</span> " + datereception.toString("dd/MM/yyyy");

                QDate dateconservation = query.value(7).toDate();
                QString formattedDateConservation = "<span style='color: red;'>Date Conservation:</span> " + dateconservation.toString("dd/MM/yyyy");

                // Set the retrieved values to corresponding labels
                ui->ID_client_label_cal->setText(formattedIDText);
                ui->NOM_client_label_cal->setText(nomClient);
                ui->PRENOM_client_label_cal->setText(prenom);
                ui->EMAIL_client_label_cal->setText(email);
                ui->TELEPHONE_client_label_cal->setText(telephone);
                ui->SEX_client_label_cal->setText(sex);
                ui->AGE_client_label_cal->setText(age);

                ui->D_RECEPTION_client_label_cal->setText(formattedDateReception);
                ui->D_CONSERVATION_client_label_cal->setText(formattedDateConservation);

                // Make labels visible
                ui->ID_client_label_cal->setVisible(true);
                ui->NOM_client_label_cal->setVisible(true);
                ui->PRENOM_client_label_cal->setVisible(true);
                ui->EMAIL_client_label_cal->setVisible(true);
                ui->TELEPHONE_client_label_cal->setVisible(true);
                ui->SEX_client_label_cal->setVisible(true);
                ui->AGE_client_label_cal->setVisible(true);
                ui->D_RECEPTION_client_label_cal->setVisible(true);
                ui->D_CONSERVATION_client_label_cal->setVisible(true);
            }
        } else {
            // No data found for the clicked date, hide labels
            ui->ID_client_label_cal->setVisible(false);
            ui->NOM_client_label_cal->setVisible(false);
            ui->PRENOM_client_label_cal->setVisible(false);
            ui->EMAIL_client_label_cal->setVisible(false);
            ui->TELEPHONE_client_label_cal->setVisible(false);
            ui->SEX_client_label_cal->setVisible(false);
            ui->AGE_client_label_cal->setVisible(false);
            ui->D_RECEPTION_client_label_cal->setVisible(false);
            ui->D_CONSERVATION_client_label_cal->setVisible(false);
        }
    }



void MainWindow::on_PartenairesRoomsOpen_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_pb3_2_clicked()
{
   int id = ui->le_ID->text().toInt();

    Equipement E;
    bool success = E.supprimer(id);  // Delete the equipment based on ID
    if (success) {
        ui->tableView_3->setModel(E.afficher());  // Refresh the table view
        QMessageBox::information(this, "Success", "Equipment deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete equipment.");
    }
}

void MainWindow::on_pushButton_Stats_2_clicked()
{
    QBarSeries *series = new QBarSeries();
 ui->stackedWidget_3->setCurrentIndex(1);
    // Clear the existing chart from the graphicsView
    if (ui->graphicsView_3->scene() != nullptr) {
        ui->graphicsView_3->scene()->clear();
    } else {
        ui->graphicsView_3->setScene(new QGraphicsScene(this));
    }

    // Get statistics from Equipement (replace Mtmp with an Equipement object)
    Equipement equip;  // Assuming Equipement has getStatistics method
    QMap<QString, double> stats = equip.getStatistics();

    // Create a new bar set and fill it with data (quantity statistics)
    QBarSet *set = new QBarSet("Statistiques Equipement");

    // Assuming stats contains: "total_quantity", "average_quantity", "min_quantity", "max_quantity", "total_price", "average_price"
    *set << stats["total_quantity"] << stats["average_quantity"]
         << stats["min_quantity"] << stats["max_quantity"]
         << stats["total_price"] << stats["average_price"];

    // Create a series and add the set to it
    //QBarSeries *series = new QBarSeries();
    series->append(set);

    // Create a chart and add the series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Equipements");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Set up the X-axis categories (for both quantity and price statistics)
    QStringList categories;
    categories << "Total Quantité" << "Moyenne Quantité" << "Min Quantité" << "Max Quantité"
               << "Total Prix" << "Moyenne Prix";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Set the Y-axis range based on statistics (for both quantity and price)
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, stats["total_quantity"] > stats["total_price"] ? stats["total_quantity"] * 1.1 : stats["total_price"] * 1.1);  // Set dynamic Y range
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create a chart view and set it to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(521, 401);  // Set the size of the chart view to match graphicsView

    // Add the chart view to the scene
    ui->graphicsView_3->scene()->addWidget(chartView);

    // Fit the chart to the graphicsView's size
    chartView->chart()->resize(521, 401);  // Fit chart within graphicsView

    // Remove chart margins for better fit
    chart->setMargins(QMargins(0, 0, 0, 0));  // Remove any extra margins
    chart->legend()->setAlignment(Qt::AlignBottom);  // Adjust legend position if needed
}

void MainWindow::on_pb_Export_2_clicked()
{
    // Open a file dialog to choose the file save location
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;  // Exit if the user canceled the save dialog
    }

    // Set up the PDF writer
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    pdfWriter.setResolution(300);  // Higher resolution for better clarity

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Arial", 10));

    // Adjust x and y starting offsets for the table layout
    int xOffset = 30;               // X-axis starting position
    int yOffset = 150;              // Y-axis starting position
    int rowHeight = 40;             // Height for each row
    int columnWidthID = 170;        // Width for ID column
    int columnWidthName = 500;      // Width for Name column
    int columnWidthDate = 500;      // Width for Date column
    int columnWidthEtat = 300;      // Width for Etat column
    int columnWidthLoc = 300;       // Width for Localisation column
    int columnWidthCat = 200;       // Width for Categorie column
    int columnWidthPrix = 150;      // Width for Prix column

    // Title
    painter.drawText(xOffset, yOffset - 50, "Liste des Equipements");

    // Draw headers for the table
    painter.drawText(xOffset, yOffset, "ID");
    painter.drawText(xOffset + columnWidthID, yOffset, "Nom");
    painter.drawText(xOffset + columnWidthID + columnWidthName, yOffset, "Date");
    painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate, yOffset, "Etat");
    painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat, yOffset, "Localisation");
    painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat + columnWidthLoc, yOffset, "Categorie");
    painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat + columnWidthLoc + columnWidthCat, yOffset, "Prix");

    // Draw a separator line below headers
    yOffset += rowHeight;
    painter.drawLine(xOffset, yOffset, xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat + columnWidthLoc + columnWidthCat + columnWidthPrix, yOffset);
    yOffset += rowHeight; // Move to the next row

    // Get the model from the QTableView
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView_3->model());
    if (!model) {
        QMessageBox::warning(this, "Error", "The table model is not of type QSqlQueryModel.");
        return;
    }

    int rowCount = model->rowCount();

    // Iterate through each row and add data to the PDF
    for (int row = 0; row < rowCount; ++row) {
        // Draw each cell's text in its respective column position
        painter.drawText(xOffset, yOffset, model->data(model->index(row, 0)).toString());                        // ID
        painter.drawText(xOffset + columnWidthID, yOffset, model->data(model->index(row, 1)).toString());          // Nom
        painter.drawText(xOffset + columnWidthID + columnWidthName, yOffset, model->data(model->index(row, 2)).toString());  // Date
        painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate, yOffset, model->data(model->index(row, 3)).toString());  // Etat
        painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat, yOffset, model->data(model->index(row, 4)).toString());  // Localisation
        painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat + columnWidthLoc, yOffset, model->data(model->index(row, 5)).toString());  // Categorie
        painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthDate + columnWidthEtat + columnWidthLoc + columnWidthCat, yOffset, model->data(model->index(row, 6)).toString());  // Prix

        // Move to the next row
        yOffset += rowHeight;

        // Check if yOffset exceeds page height, and add a new page if necessary
        if (yOffset > pdfWriter.height() - 100) {  // Leave some margin before starting a new page
            pdfWriter.newPage();
            yOffset = 100;  // Reset yOffset for the new page
        }
    }

    // Finalize the painter
    painter.end();

    // Inform the user that the PDF has been saved
    QMessageBox::information(this, "File Saved", "PDF saved to: " + filePath);
}

void MainWindow::on_pb_rech_2_clicked()
{
    QString searchName = ui->le_rech_2->text(); // Get the search query from the input field

    Equipement E;
    QSqlQueryModel* model = E.rechercher(searchName); // Call the search function
    if (model) {
        ui->tableView_3->setModel(model); // Set the model with the search results
    } else {
        QMessageBox::warning(this, "No Results", "No equipment found matching the search criteria.");
    }
}

void MainWindow::on_pb_sortEtat_2_clicked()
{
    static bool sortAscending = true; // Toggle between ascending and descending

    Equipement E;
    ui->tableView_3->setModel(E.afficherParEtat(sortAscending)); // Set the sorted model
    sortAscending = !sortAscending; // Toggle sort order for next click
}

void MainWindow::on_pb2_2_clicked()
{
    int id = ui->le_ID->text().toInt();
    QString nom = ui->le_nom_2->text();
    QDate dateAquisition = ui->le_date_2->date();
    QString etat = ui->le_etat_2->currentText();
    QString localisation = ui->le_loc_2->text();
    QString categorie = ui->le_cat_2->text();
    int prix = ui->le_prix_2->text().toInt();
QString image=ui->lien_image_2->text();
    // Create Equipement object
    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix,image);

    // Try to modify the equipment
    bool success = E.modifier();
    if (success) {
        ui->tableView_3->setModel(E.afficher());  // Refresh the table view with updated equipment
        QMessageBox::information(this, "Success", "Equipment modified successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify equipment.");
    }
}

void MainWindow::on_pb1_2_clicked()
{
    int id = ui->le_ID->text().toInt();
    QString nom = ui->le_nom_2->text();
    QDate dateAquisition = ui->le_date_2->date();  // Get date from QDateEdit
    QString etat = ui->le_etat_2->currentText();   // Get selected value from ComboBox
    QString localisation = ui->le_loc_2->text();
    QString categorie = ui->le_cat_2->text();
    int prix = ui->le_prix_2->text().toInt();
QString image=ui->lien_image_2->text() ;
    // Create Equipement object
    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix,image);

    // Try to add the equipment
    bool success = E.ajouter();
    if (success) {
        ui->tableView_3->setModel(E.afficher());  // Refresh the table view with new equipment
        QMessageBox::information(this, "Success", "Equipment added successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to add equipment.");
    }
}

void MainWindow::on_back_2_clicked()
{
     ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_inserer_2_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

    if (!imagePath.isEmpty()) {
        // Load the image using QPixmap
        QPixmap image(imagePath);

        // Update the QLabel with the image
        ui->label_image_2->setPixmap(image.scaled(ui->label_image_2->size(), Qt::KeepAspectRatio));
        ui->lien_image_2->setText(imagePath);
        ui->lien_image_2->hide();
    }
}
