#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h" // Include the client header
#include "connection.h"
#include <QDebug>
#include "BackgroundColorDelegate.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

            QPalette palette;
            palette.setColor(QPalette::Background, QColor("#00FF9C"));

            tableView->setItemDelegateForColumn(9, new BackgroundColorDelegate(palette));

            QPalette palette2;
            palette2.setColor(QPalette::Background, QColor("#FF4545"));

            tableView->setItemDelegateForColumn(10, new BackgroundColorDelegate(palette2));
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
    connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::exportToPDF);
    // Excel connect
    connect(ui->excel, &QPushButton::clicked, this, &MainWindow::exportToExcel);
    // Search connect
    connect(ui->search_bar, &QLineEdit::textChanged, this, &MainWindow::Rechercherclient);
    // Sort connect
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sortComboBox_currentIndexChanged(int)));
}

MainWindow::~MainWindow() {
    delete ui;
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
        client client(0, nom, prenom, email, dateInscription, age, sexe, tel, nbServiceRecu);

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
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de l'ajout du client."), QMessageBox::Cancel);
        }
    }
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

    qry.prepare("SELECT NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU FROM client WHERE ID_CL = :ID_CL");
    qry.bindValue(":ID_CL", value);

    if(qry.exec()) {
        if(qry.next()) {
            ui->id->setText(value);
            if (index.column() == 9) {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Update Client", "Are you sure you want to update this client?",
                                              QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    ui->nom->setText(qry.value(0).toString());
                    ui->prnom->setText(qry.value(1).toString());
                    ui->mail->setText(qry.value(2).toString());
                    ui->date_inscription->setDate(qry.value(3).toDate());
                    ui->age->setText(qry.value(4).toString());
                    ui->gender->setCurrentText(qry.value(5).toString());
                    ui->nbrphone->setText(qry.value(6).toString());
                    ui->nb_service_recu->setText(qry.value(7).toString());
                    ui->id->setText(value);
                    ui->stackedWidget->setCurrentIndex(2);
                }
            }
        }
    }

    if (index.column() == 10) {
        QString clientId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();

        // Confirm the deletion
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Client", "Are you sure you want to delete this client?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            client clientToDelete; // Create an instance of client
            if (clientToDelete.Supprimerclient(clientId)) {
                QMessageBox::information(this, "Deleted", "Client successfully deleted.");
                ui->tableView->setModel(clientToDelete.Afficherclients()); // Refresh the table view
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete client.");
            }
        }
    }
    // Close the database connection
    c.closeconnection();
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

    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || sexe.isEmpty() || tel.isEmpty() || age == 0 || nbServiceRecu == 0) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez remplir tous les champs."), QMessageBox::Cancel);
        return;
    }

    client client(idCl, nom, prenom, email, dateInscription, age, sexe, tel, nbServiceRecu);

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
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la modification du client."), QMessageBox::Cancel);
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
            queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, 'Update' AS Action, 'Delete' AS Action FROM client ORDER BY PRENOM ASC";
            break;
        case 2: // Sort by ID_CL (Ascending)
            queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, 'Update' AS Action, 'Delete' AS Action FROM client ORDER BY ID_CL ASC";
            break;
        case 3: // Sort by Date Inscription (Oldest to Newest)
            queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, 'Update' AS Action, 'Delete' AS Action FROM client ORDER BY DATE_INSCRIPTION ASC";
            break;
        default:
            queryStr = "SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, 'Update' AS Action, 'Delete' AS Action FROM client";
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
    clientModel->setHeaderData(9, Qt::Horizontal, QObject::tr("Action"));
    clientModel->setHeaderData(10, Qt::Horizontal, QObject::tr("Action"));

    ui->tableView->setModel(clientModel);
}


void MainWindow::on_gostat_clicked()
{
    displayCharts_clientByGender();
    ui->stackedWidget->setCurrentIndex(1);
}




void MainWindow::navigateToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}
