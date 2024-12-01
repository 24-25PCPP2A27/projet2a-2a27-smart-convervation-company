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
#include <QSqlQueryModel>
#include "Qrcode.hpp"
#include "arduino.h"
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // Display data in tableView
    ui->tableView->setModel(Etemp.afficher());  // Initially show all records

    ui->lien_image->hide();

    if (A.connect_arduino() == 0) {

              QMessageBox::information(this, "Port arduino", A.getarduino_port_name());

          } else {
        QMessageBox::information(this, "Echec", A.getarduino_port_name());
          }
          connect(A.get_serial(), &QSerialPort::readyRead, this, &MainWindow::arduino);
}

void MainWindow::arduino() {
QByteArray data=A.read_from_arduino();
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

MainWindow::~MainWindow()
{
    delete ui;
}

// Slot for adding equipment
void MainWindow::on_pb1_clicked() {
    int id = ui->le_ID->text().toInt();
    QString nom = ui->le_nom->text();
    QDate dateAquisition = ui->le_date->date();  // Get date from QDateEdit
    QString etat = ui->le_etat->currentText();   // Get selected value from ComboBox
    QString localisation = ui->le_loc->text();
    QString categorie = ui->le_cat->text();
    int prix = ui->le_prix->text().toInt();
QString image=ui->lien_image->text() ;
    // Create Equipement object
    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix,image);

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
    QString etat = ui->le_etat->currentText();
    QString localisation = ui->le_loc->text();
    QString categorie = ui->le_cat->text();
    int prix = ui->le_prix->text().toInt();
QString image=ui->lien_image->text();
    // Create Equipement object
    Equipement E(id, nom, dateAquisition, etat, localisation, categorie, prix,image);

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
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());
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


void MainWindow::on_pushButton_Stats_clicked()
{
    QBarSeries *series = new QBarSeries();

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
    ui->graphicsView->scene()->addWidget(chartView);

    // Fit the chart to the graphicsView's size
    chartView->chart()->resize(521, 401);  // Fit chart within graphicsView

    // Remove chart margins for better fit
    chart->setMargins(QMargins(0, 0, 0, 0));  // Remove any extra margins
    chart->legend()->setAlignment(Qt::AlignBottom);  // Adjust legend position if needed
}





void MainWindow::on_inserer_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

    if (!imagePath.isEmpty()) {
        // Load the image using QPixmap
        QPixmap image(imagePath);

        // Update the QLabel with the image
        ui->label_image->setPixmap(image.scaled(ui->label_image->size(), Qt::KeepAspectRatio));
        ui->lien_image->setText(imagePath);
        ui->lien_image->hide();
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    // Get the selected row index
    int row = index.row();
    QAbstractItemModel* model = ui->tableView->model();
        QString ID = model->data(model->index(row, 0)).toString();
        QString NOM = model->data(model->index(row, 1)).toString();
        QDate DATE = model->data(model->index(row, 2)).toDate();
        QString etat = model->data(model->index(row, 3)).toString();
        QString localisation = model->data(model->index(row, 4)).toString();
        QString categorie = model->data(model->index(row, 5)).toString();
        QString prix = model->data(model->index(row, 6)).toString();
        QString image = model->data(model->index(row, 7)).toString();

ui->le_ID->setText(ID);
ui->le_nom->setText(NOM);
ui->le_date->setDate(DATE);
ui->le_etat->setCurrentText(etat);
ui->le_loc->setText(localisation);
ui->le_cat->setText(categorie);
ui->le_prix->setText(prix);
ui->lien_image->setText(image);
// Load the image from the file path
QPixmap image1(image);
ui->label_image->setPixmap(image1.scaled(ui->label_image->size(), Qt::KeepAspectRatio));


QString text = "ID: " + ID + "\n"
               "Nom: " + NOM + "\n"
               "Date: " + DATE.toString("dd/MM/yyyy") + "\n"  // Format the date for better readability
               "Etat: " + etat + "\n"
               "Localisation: " + localisation + "\n"
               "Categorie: " + categorie + "\n"
               "Prix: " + prix + "\n"
               "Image Path: " + image;  // Include the image path or description


 using namespace qrcodegen;
QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

                 qint32 sz = qr.getSize();
                 QImage im(sz, sz, QImage::Format_RGB32);
                 QRgb black = qRgb(0, 0, 0);
                 QRgb white = qRgb(255, 255, 255);

                 for (int y = 0; y < sz; y++) {
                     for (int x = 0; x < sz; x++) {
                         im.setPixel(x, y, qr.getModule(x, y) ? black : white);
                     }
                 }
                 ui->label_qr->setPixmap(QPixmap::fromImage(im.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));

}
