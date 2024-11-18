#include "traitementproduit.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

#include <QSqlQueryModel>
#include <QtSql>

#include <QSqlQueryModel>
#include <QtSql>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>

#include <QPainter>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts>
// Constructeur par défaut
traitementproduit::traitementproduit() {
    id = 0;
    type_traitement = "";
    duree_traitement = 0;
    temp_min = 0;
    temp_max = 0;
    prix = 0.0;
}

// Constructeur avec paramètres
traitementproduit::traitementproduit(int id, QString type_traitement, int duree_traitement, int temp_min, int temp_max, double prix) {
    this->id = id;
    this->type_traitement = type_traitement;
    this->duree_traitement = duree_traitement;
    this->temp_min = temp_min;
    this->temp_max = temp_max;
    this->prix = prix;
}

// Getters
int traitementproduit::getId() { return id; }
QString traitementproduit::getTypeTraitement() { return type_traitement; }
int traitementproduit::getDureeTraitement() { return duree_traitement; }
int traitementproduit::getTempMin() { return temp_min; }
int traitementproduit::getTempMax() { return temp_max; }
double traitementproduit::getPrix() { return prix; }

// Setters
void traitementproduit::setId(int id) { this->id = id; }
void traitementproduit::setTypeTraitement(QString type_traitement) { this->type_traitement = type_traitement; }
void traitementproduit::setDureeTraitement(int duree_traitement) { this->duree_traitement = duree_traitement; }
void traitementproduit::setTempMin(int temp_min) { this->temp_min = temp_min; }
void traitementproduit::setTempMax(int temp_max) { this->temp_max = temp_max; }
void traitementproduit::setPrix(double prix) { this->prix = prix; }

// Ajouter un nouveau traitement
bool traitementproduit::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO TRAITEMENT_DE_PRODUIT (IDTRAIT, PRIX, TYPE, DUREE, TEMP_MIN, TEMP_MAX) "
                    "VALUES (:id, :prix, :type_traitement, :duree_traitement, :temp_min, :temp_max)");

      query.bindValue(":id", id);
      query.bindValue(":prix", prix);
      query.bindValue(":type_traitement", type_traitement);
      query.bindValue(":duree_traitement", duree_traitement);
      query.bindValue(":temp_min", temp_min);
      query.bindValue(":temp_max", temp_max);
    return query.exec();
}

// Supprimer un traitement par id
bool traitementproduit::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM TRAITEMENT_DE_PRODUIT WHERE IDTRAIT = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        return true;
    }
    else
    {

    }
    return query.exec();
}

// Afficher les traitements
QSqlQueryModel* traitementproduit::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRAITEMENT_DE_PRODUIT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Température Min"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Température Max"));

    return model;
}

// Modifier un traitement
bool traitementproduit::modifier(int id, QString type_traitement, int duree_traitement, int temp_min, int temp_max, double prix) {
    QSqlQuery query;
    query.prepare("UPDATE TRAITEMENT_DE_PRODUIT SET TYPE = :type_traitement, DUREE = :duree_traitement, "
                    "TEMP_MIN = :temp_min, TEMP_MAX = :temp_max, PRIX = :prix WHERE IDTRAIT = :id");
      query.bindValue(":id", id);
      query.bindValue(":type_traitement", type_traitement);
      query.bindValue(":duree_traitement", duree_traitement);
      query.bindValue(":temp_min", temp_min);
      query.bindValue(":temp_max", temp_max);
      query.bindValue(":prix", prix);

    return query.exec();
}
//trier selon duree
QSqlQueryModel* traitementproduit::tri_duree() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRAITEMENT_DE_PRODUIT ORDER BY Duree");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Température Min"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Température Max"));


    return model;
}
//rechercher selon id
QSqlQueryModel* traitementproduit::rechercher(int id) {
QSqlQuery query;
QSqlQueryModel* model = new QSqlQueryModel();
query.prepare("SELECT * FROM TRAITEMENT_DE_PRODUIT WHERE IDTRAIT = :id");
query.bindValue(":id", id);

if (query.exec()) {
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Température Min"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Température Max"));

}
return model;
}
void traitementproduit::exportDataToPDF() {
    QSqlQuery query;

    // Create a PDF file
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        qDebug() << "No file selected. Aborting PDF generation.";
        return; // Exit if no file is selected
    }

    // Prepare query to retrieve all traitementproduit records
    query.prepare("SELECT IDTRAIT, TYPE, DUREE, TEMP_MIN, TEMP_MAX, PRIX FROM TRAITEMENT_DE_PRODUIT");

    // Create a QPrinter object
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter;
    if (!painter.begin(&printer)) {
        qDebug() << "Failed to begin painting on printer.";
        return; // Exit if painter fails to start
    }

    // HTML for better styling
    QString html = "<html><head><style>"
                   "body { font-family: Arial, sans-serif; margin: 20px; }"
                   "h1 { text-align: center; }"
                   "table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
                   "th, td { border: 1px solid black; padding: 8px; text-align: center; }"
                   "th { background-color: #f2f2f2; }"
                   "</style></head><body>"
                   "<h1>Traitement de Produit</h1>"
                   "<table>"
                   "<tr><th>ID</th><th>Type</th><th>Durée</th><th>Temp Min</th><th>Temp Max</th><th>Prix</th></tr>";

    // Execute the query
    if (query.exec()) {
        while (query.next()) {
            html += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td></tr>")
                        .arg(query.value("IDTRAIT").toString())
                        .arg(query.value("TYPE").toString())
                        .arg(query.value("DUREE").toString())
                        .arg(query.value("TEMP_MIN").toString())
                        .arg(query.value("TEMP_MAX").toString())
                        .arg(query.value("PRIX").toString());
        }
    } else {
        qDebug() << "Error retrieving data for TRAITEMENT_DE_PRODUIT table:" << query.lastError().text();
    }

    html += "</table></body></html>"; // Close the HTML tags

    // Create a QTextDocument and set its HTML content
    QTextDocument document;
    document.setHtml(html);

    // Draw the document to the painter
    document.drawContents(&painter);
    painter.end(); // Ensure the painter is ended

    qDebug() << "PDF generated successfully!";
}
QChartView* traitementproduit::type1() {
    // Initialize counters for each type category
    int refrigeration = 0;
    int congelation = 0;
    int stockage_sous_vide = 0;

    // Query to select all the type_traitement from the TRAITEMENT_DE_PRODUIT table
    QSqlQuery query("SELECT TYPE FROM TRAITEMENT_DE_PRODUIT");

    // Process the query result
    while (query.next()) {
        QString type = query.value(0).toString();

        // Increment the respective counter based on type category
        if (type == "refrigeration") {
            refrigeration++;
        } else if (type == "congelation") {
            congelation++;
        } else if (type == "stockage sous vide") {
            stockage_sous_vide++;
        }
    }

    // Create a bar set for the treatments
    QBarSet* treatmentSet = new QBarSet("Traitements");

    // Set the values for each category
    *treatmentSet << refrigeration << congelation << stockage_sous_vide;

    // Set custom colors for the bars
    treatmentSet->setColor(QColor("#FF5733"));  // Color for "réfrigération"
     // Color for "stockage sous vide"

    // Create a bar series and add the set to it
    QBarSeries* series = new QBarSeries();
    series->append(treatmentSet);

    // Create a chart and add the series to it
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des types de traitement");

    // Set up categories for the x-axis
    QStringList categories;
    categories << "Réfrigération" << "Congélation" << "Stockage Sous Vide";

    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    // Create a chart view and enable animations
    QChartView* chartView = new QChartView(chart);
    chartView->chart()->setAnimationOptions(QChart::AllAnimations);

    return chartView;
}
