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
#include <QSortFilterProxyModel>

#include "arduino.h"
#include "employe.h"
#include "produit.h"


using namespace QtCharts;


MainWindow::MainWindow(const Employe &employe,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
  currentEmploye(employe)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();

    populateFields();
    // Initialize Arduino for RFID reading


    if(currentEmploye.getpost()=="client"){
        ui->stackedWidget_2->setCurrentIndex(1);
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
    if(currentEmploye.getpost()=="employee"){
        ui->stackedWidget_2->setCurrentIndex(0);
    }
    else if(currentEmploye.getpost()=="produit"){
        ui->stackedWidget_2->setCurrentIndex(5);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    delete arduino;  // Clean up Arduino instance

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



void MainWindow::on_mody_Button_13_clicked()
{
    int id = ui->id_2->text().toInt();
    QString nom = ui->nom_3->text().trimmed();
    int quantite = ui->quantite->text().toInt();
    QString dateReception = ui->dateReception->text().trimmed();
    QString dateConservation = ui->dateConservation->text().trimmed();
    QString statut = ui->statut->text().trimmed();
    QString description = ui->description->text().trimmed();

    // Vérification des champs vides
    if (nom.isEmpty() || dateReception.isEmpty() || dateConservation.isEmpty() ||
        statut.isEmpty() || description.isEmpty() || ui->id_2->text().isEmpty() ||
        ui->quantite->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validation des entrées
    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }
    if (quantite < 0) {
        QMessageBox::warning(this, "Input Error", "Quantity must be a positive number.");
        return;
    }

    // Création et ajout du produit
    Produit produit(id, nom, quantite, dateReception, dateConservation, statut, description);
    bool test = produit.ajouter();

    if (test) {
        QMessageBox::information(this, "Done", "Product added successfully.");
        // Mise à jour de la table et réinitialisation des champs
        ui->tableView5_2->setModel(P.afficher());
        ui->id_2->clear();
        ui->nom_3->clear();
        ui->quantite->clear();
        ui->dateReception->clear();
        ui->dateConservation->clear();
        ui->statut->clear();
        ui->description->clear();
    } else {
        QMessageBox::critical(this, "Failed", "Failed to add product.");
    }

}

void MainWindow::on_modi_Button_3_clicked()
{
    int id = ui->id_2->text().toInt();
    QString nom = ui->nom_3->text();
    int quantite = ui->quantite->text().toInt();
    QString dateReception = ui->dateReception->text();
    QString dateConservation = ui->dateConservation->text();
    QString statut = ui->statut->text();
    QString description = ui->description->text();

    if (ui->id_2->text().isEmpty() || ui->nom_3->text().isEmpty() || ui->quantite->text().isEmpty() ||
        ui->dateReception->text().isEmpty() || ui->dateConservation->text().isEmpty() || ui->statut->text().isEmpty() ||
        ui->description->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "ID must be a positive number.");
        return;
    }
    if (quantite < 0) {
        QMessageBox::warning(this, "Input Error", "Quantity must be a positive number.");
        return;
    }

    // Création et mise à jour du produit
    Produit produit(id, nom, quantite, dateReception, dateConservation, statut, description);
    bool test = produit.mettreAJour();

    if (test) {
        QMessageBox::information(this, "Success", "Product updated successfully.");
        ui->tableView5_2->setModel(P.afficher());
        ui->id_2->clear();
        ui->nom_3->clear();
        ui->quantite->clear();
        ui->dateReception->clear();
        ui->dateConservation->clear();
        ui->statut->clear();
        ui->description->clear();
    } else {
        QMessageBox::critical(this, "Failure", "Failed to update product.");
    }
}

void MainWindow::on_supp_button_clicked()
{
    int id = ui->id_2->text().toInt();

    if (ui->id_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the product ID to delete.");
        return;
    }

    Produit produit;
    bool test = produit.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Deletion Successful", "The product has been deleted successfully.");
        ui->tableView5->setModel(P.afficher());
        ui->id_2->clear();
    } else {
        QMessageBox::critical(this, "Deletion Failed", "Failed to delete the product. Please try again.");
    }
}

void MainWindow::on_mody_Button_14_clicked()
{
    int id = ui->id_2->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid ID.");
        return;
    }

    QSqlQueryModel *model = P.rechercherParId(id);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Not Found", "No product found with this ID.");
        return;
    }

    ui->tableView5->setModel(model);
}

void MainWindow::on_Trier_Button_9_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(P.afficher());
    int colonneTri = 2;  // Assurez-vous que cette colonne existe
    proxyModel->sort(colonneTri, Qt::AscendingOrder);
    ui->tableView5->setModel(proxyModel);
    QMessageBox::information(this, "Sorting", "The products have been sorted successfully.");
}

void MainWindow::on_Stat_Button_8_clicked()
{

}
