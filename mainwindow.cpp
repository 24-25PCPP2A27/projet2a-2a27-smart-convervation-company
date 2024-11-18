#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("equipement_db.sqlite");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database connected!";
    }

    // Display data in tableView
    Equipement Etemp;
    ui->tableView->setModel(Etemp.afficher());  // Initially show all records
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slot for adding equipment
void MainWindow::on_pb1_clicked() {
    int id = ui->le_ID->text().toInt();
    QString nom = ui->le_nom->text();
    QDate dateAquisition = ui->le_date->date();  // Get date from QDateEdit
    QString etat = ui->le_etat->text();   // Get selected value from ComboBox
    QString localisation = ui->le_loc->text();
    QString categorie = ui->le_cat->text();
    double prix = ui->le_prix->text().toDouble();

    // Create Equipement object
    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix);

    // Try to add the equipment
    bool success = E.ajouter();
    if (success) {
        ui->tableView->setModel(E.afficher());  // Refresh the table view with new equipment
        QMessageBox::information(this, "Success", "Equipment added successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to add equipment.");
    }
}

// Slot for deleting equipment
void MainWindow::on_pb3_clicked() {
    int id = ui->le_ID->text().toInt();

    Equipement E;
    bool success = E.supprimer(id);  // Delete the equipment based on ID
    if (success) {
        ui->tableView->setModel(E.afficher());  // Refresh the table view
        QMessageBox::information(this, "Success", "Equipment deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete equipment.");
    }
}

// Slot for modifying equipment
void MainWindow::on_pb2_clicked() {
    int id = ui->le_ID->text().toInt();
    QString nom = ui->le_nom->text();
    QDate dateAquisition = ui->le_date->date();
    QString etat = ui->le_etat->text();
    QString localisation = ui->le_loc->text();
    QString categorie = ui->le_cat->text();
    double prix = ui->le_prix->text().toDouble();

    // Create Equipement object
    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix);

    // Try to modify the equipment
    bool success = E.modifier();
    if (success) {
        ui->tableView->setModel(E.afficher());  // Refresh the table view with updated equipment
        QMessageBox::information(this, "Success", "Equipment modified successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify equipment.");
    }
}

// Slot for searching equipment by name
void MainWindow::on_pb_rech_clicked() {
    QString searchName = ui->le_rech->text(); // Get the search query from the input field

    Equipement E;
    QSqlQueryModel* model = E.rechercher(searchName); // Call the search function
    if (model) {
        ui->tableView->setModel(model); // Set the model with the search results
    } else {
        QMessageBox::warning(this, "No Results", "No equipment found matching the search criteria.");
    }
}

// Slot for sorting equipment by 'etat'
void MainWindow::on_pb_sortEtat_clicked() {
    static bool sortAscending = true; // Toggle between ascending and descending

    Equipement E;
    ui->tableView->setModel(E.afficherParEtat(sortAscending)); // Set the sorted model
    sortAscending = !sortAscending; // Toggle sort order for next click
}

void MainWindow::on_pb_Export_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;  // Exit if the user canceled the save dialog
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    pdfWriter.setResolution(300);  // Higher resolution for better clarity

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Arial", 10));

    // Adjust x and y starting offsets for a larger table
    int xOffset = 30, yOffset = 150;       // Start position for the table
    int rowHeight = 40;                    // Increased space between rows for more line spacing
    int columnWidthID = 170;               // Wider IDM column
    int columnWidthName = 250;             // Wider Name column
    int columnWidthQuantity = 400;         // Wider Quantity column
    int columnWidthPrice = 150;            // Price column

    // Title
    painter.drawText(xOffset, yOffset - 50, "Liste des Equipements");

    // Draw headers with increased spacing for clarity
    painter.drawText(xOffset, yOffset, "ID");
    painter.drawText(xOffset + columnWidthID, yOffset, "Nom");
    painter.drawText(xOffset + columnWidthID + columnWidthName, yOffset, "Etat");
    painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthQuantity, yOffset, "Localisation");
    painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthQuantity + columnWidthPrice, yOffset, "Prix");

    // Draw a separator line below headers
    yOffset += rowHeight;
    painter.drawLine(xOffset, yOffset, xOffset + columnWidthID + columnWidthName + columnWidthQuantity + columnWidthPrice, yOffset);
    yOffset += rowHeight;

    QSqlQueryModel* model = ui->tableView->model();
    int rowCount = model->rowCount();

    // Iterate through each row and add equipment data
    for (int row = 0; row < rowCount; ++row) {
        // Position each data field in a specific, larger column
        painter.drawText(xOffset, yOffset, model->data(model->index(row, 0)).toString());                        // ID
        painter.drawText(xOffset + columnWidthID, yOffset, model->data(model->index(row, 1)).toString());          // Name
        painter.drawText(xOffset + columnWidthID + columnWidthName, yOffset, model->data(model->index(row, 2)).toString());  // Etat
        painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthQuantity, yOffset, model->data(model->index(row, 3)).toString());  // Localisation
        painter.drawText(xOffset + columnWidthID + columnWidthName + columnWidthQuantity + columnWidthPrice, yOffset, model->data(model->index(row, 4)).toString());  // Prix

        yOffset += rowHeight + 10;  // Add extra padding between rows for better spacing

        // Check if yOffset exceeds page height, add new page if necessary
        if (yOffset > pdfWriter.height() - 100) {  // Increased margin before new page
            pdfWriter.newPage();
            yOffset = 100;  // Reset yOffset for the new page
        }
    }

    painter.end();
    QMessageBox::information(this, "File Saved", "PDF saved to: " + filePath);
}

void MainWindow::on_pushButton_Stats_clicked()
{
    // Clear the existing chart from the graphicsView
    if (ui->graphicsView->scene() != nullptr) {
        ui->graphicsView->scene()->clear();
    } else {
        ui->graphicsView->setScene(new QGraphicsScene(this));
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
    QBarSeries *series = new QBarSeries();
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
    ui->graphicsView->scene()->addWidget(chartView);

    // Fit the chart to the graphicsView's size
    chartView->chart()->resize(521, 401);  // Fit chart within graphicsView

    // Remove chart margins for better fit
    chart->setMargins(QMargins(0, 0, 0, 0));  // Remove any extra margins
    chart->legend()->setAlignment(Qt::AlignBottom);  // Adjust legend position if needed
}
