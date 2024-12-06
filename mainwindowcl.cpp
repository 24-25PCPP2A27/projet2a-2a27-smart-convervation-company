#include "mainwindowcl.h"
#include "ui_mainwindowcl.h"
#include "arduinocl.h"
#include "client.h" // Include the client header
#include "connection.h"
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

using namespace QtCharts;

mainwindowcl::mainwindowcl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindowcl)
{
    ui->setupUi(this);
    int verif_arduino = A.connect_arduino();
            switch(verif_arduino){
            case(0):qDebug()<<"arduino is available and connected to :" << A.getArduinoPortName();
                break;
            case(1):qDebug()<<"arduino is available but not connected to :" << A.getArduinoPortName();
                break;
            case(-1):qDebug()<<"arduino is not available" ;
                break;
            }
        QObject::connect(A.getSerial(),SIGNAL(readyRead()),this,SLOT(update_label()));
        QStackedWidget* stackedWidget = ui->stackedWidget;
        QWidget* page = stackedWidget->widget(0);
        QTableView* tableView = page->findChild<QTableView*>("tableView");

        if (tableView) {
            client client;
            Connection c;

            if (c.createconnect()) {
                QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                         QObject::tr("Connection successful.\nClick Cancel to exit."),
                                         QMessageBox::Cancel);

                tableView->setModel(client.Afficherclients());
                tableView->resizeColumnsToContents();
                tableView->horizontalHeader()->setStretchLastSection(true);


            } else {
                QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                                      QObject::tr("Connection failed.\nClick Cancel to exit."),
                                      QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                  QObject::tr("Failed to find the table view for Client data."),
                                  QMessageBox::Cancel);
        }

        connect(ui->gostat, &QPushButton::clicked, this, [this]() { navigateToPage(1); });
        connect(ui->back, &QPushButton::clicked, this, [this]() { navigateToPage(0); });

        // PDF connect
        connect(ui->pdf, &QPushButton::clicked, this, &mainwindowcl::exportToPDF);
        // Excel connect
        connect(ui->excel, &QPushButton::clicked, this, &mainwindowcl::exportToExcel);
        // Search connect
        connect(ui->search_bar, &QLineEdit::textChanged, this, &mainwindowcl::Rechercherclient);
        // Sort connect
        connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sortComboBox_currentIndexChanged(int)));


        QDate selectedDate = ui->calendarWidget->selectedDate();
        updateCalendarAndEventDetails(selectedDate);*/
    }

    mainwindowcl::~mainwindowcl() {
        delete ui;
    }
    void mainwindowcl::on_confirm_clicked() {
        QString rfidValue = ui->rfid->text(); // Get text from QLineEdit

        if (rfidValue.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter an RFID value.");
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT NOM, PRENOM FROM employe WHERE RFID = :rfid");
        query.bindValue(":rfid", rfidValue);

        if (query.exec()) {
            if (query.next()) { // If an entry is found
                QString nom = query.value("NOM").toString();
                QString prenom = query.value("PRENOM").toString();
                sendDataToArduino(nom, prenom); // Send data to Arduino
                QMessageBox::information(this, "Success", "Employee found: " + nom + " " + prenom);
            } else {
                sendDataToArduinonotfound(); // Send "notfound" to Arduino
                QMessageBox::warning(this, "Not Found", "RFID not found in the employees table.");
            }
        } else {
            QMessageBox::critical(this, "Database Error", "Failed to query the database: " + query.lastError().text());
        }
    }



    void mainwindowcl::sendDataToArduino(const QString &nom, const QString &prenom) {// Ensure the serial connection is open and writable
            QString dataToSend = nom + "," + prenom + "\n"; // Format: "id,name"
            A.write_arduino(dataToSend.toUtf8()); // Send data to Arduino

    }
    void mainwindowcl::sendDataToArduinonotfound() {// Ensure the serial connection is open and writable
            QString dataToSend = "notfound\n"; // Format: "id,name"
            A.write_arduino(dataToSend.toUtf8()); // Send data to Arduino

    }
    void mainwindowcl::on_ajouter_clicked()
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
        QRegExp nameRx("^[a-zA-Z]+$"); // Only letters
        QRegExp telRx("^\\d{8}$"); // Exactly 8 digits
        QRegExp emailRx("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$"); // Email format

        if (!nameRx.exactMatch(nom) || !nameRx.exactMatch(prenom)) {
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom et le prénom doivent contenir uniquement des lettres."), QMessageBox::Cancel);
        } else if (!telRx.exactMatch(tel)) {
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



    void mainwindowcl::on_tableView_activated(const QModelIndex &index)
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


    void mainwindowcl::on_modifier_clicked()
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

    void mainwindowcl::on_supprimer_clicked()
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

        // Attempt deletion
        bool success = cli.Supprimerclient(ID_CL);


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


    void mainwindowcl::exportToPDF()
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

    void mainwindowcl::exportToExcel()
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

    void mainwindowcl::Rechercherclient(const QString &text)
    {
        client c;
        QSqlQueryModel *model = c.Rechercherclient(text);
        ui->tableView->setModel(model);
    }


    void mainwindowcl::displayCharts_clientByGender()
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

    void mainwindowcl::on_sortComboBox_currentIndexChanged(int index)
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


    void mainwindowcl::on_gostat_clicked()
    {
        displayCharts_clientByGender();
        ui->stackedWidget->setCurrentIndex(1);
    }




    void mainwindowcl::navigateToPage(int pageIndex)
    {
        ui->stackedWidget->setCurrentIndex(pageIndex);
    }

    void mainwindowcl::on_gocalendar_clicked()
    {
        QDate selectedDate = ui->calendarWidget->selectedDate();
        updateCalendarAndEventDetails(selectedDate);

        ui->stackedWidget->setCurrentIndex(2);
    }

    void mainwindowcl::on_back_fromcalendr_clicked()
    {
        ui->stackedWidget->setCurrentIndex(0);
    }

    void mainwindowcl::on_calendarWidget_clicked(const QDate &date)
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


    void mainwindowcl::updateCalendarAndEventDetails(const QDate &date) {
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



