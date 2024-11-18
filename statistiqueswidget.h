#ifndef STATISTIQUESWIDGET_H
#define STATISTIQUESWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class StatistiquesWidget;
}

class StatistiquesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatistiquesWidget(QWidget *parent = nullptr);
    ~StatistiquesWidget();

    void afficherStatistiques();  // Function to fetch and display statistics

private:
    Ui::StatistiquesWidget *ui;
    QSqlQueryModel *model;  // Model to display statistics
};

#endif // STATISTIQUESWIDGET_H
