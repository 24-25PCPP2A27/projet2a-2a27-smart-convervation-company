#ifndef MAINWINDOWCL_H
#define MAINWINDOWCL_H

#include <QMainWindow>
#include <QTableView>
#include <QMessageBox>
#include "arduinocl.h"
class client;

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindowcl; }
QT_END_NAMESPACE

class mainwindowcl : public QMainWindow {
    Q_OBJECT

public:
    explicit mainwindowcl(QWidget *parent = nullptr);
    ~mainwindowcl();

private slots:
    /*void on_ajouter_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_modifier_clicked();
    void on_supprimer_clicked();

    void navigateToPage(int pageIndex);
    void exportToPDF();
    void exportToExcel();
    void Rechercherclient(const QString &text);
    void on_sortComboBox_currentIndexChanged(int index);
    void displayCharts_clientByGender();
    void on_gostat_clicked();
    void sendDataToArduinonotfound();

    void on_gocalendar_clicked();
    void on_back_fromcalendr_clicked();

    void on_calendarWidget_clicked(const QDate &date);
    void updateCalendarAndEventDetails(const QDate &date);
    void sendDataToArduino(const QString &id, const QString &name);
    void on_confirm_clicked();
*/


private:
    Ui::mainwindowcl *ui;
     Arduino A;
    QString data;
};

#endif // MAINWINDOW_H
