#include "statistiqueswidget.h"
#include "ui_statistiqueswidget.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

StatistiquesWidget::StatistiquesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatistiquesWidget)
{
    ui->setupUi(this);
    model = new QSqlQueryModel(this);  // Initialize the model
}

StatistiquesWidget::~StatistiquesWidget()
{
    delete ui;
}

void StatistiquesWidget::afficherStatistiques()
{
    // Create a query to get the total price and item count per category
    QSqlQuery query;

    query.prepare("SELECT CATEGORIE, COUNT(IDTR) AS ItemCount, SUM(PRIX) AS TotalPrice FROM EQUIPEMENT GROUP BY CATEGORIE");

    if (query.exec()) {
        model->setQuery(query);  // Set the query results in the model
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Category"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Item Count"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Price"));

        ui->tableView->setModel(model);  // Display the statistics in the table
    } else {
        qDebug() << "Error executing query: " << query.lastError();
    }
}
