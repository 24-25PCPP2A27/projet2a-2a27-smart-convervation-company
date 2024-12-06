#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include "arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(const Employe &employe, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mody_Button_6_clicked();

    void clearInputFields ();

    void on_mody_Button_4_clicked();

    void on_mody_Button_7_clicked();

    void on_mody_Button_11_clicked();

    void on_mody_Button_10_clicked();

    void onTagScanned(const QString &uid);

    void on_mody_Button_9_clicked();

    void on_mody_Button_8_clicked();

    void on_pushButton_clicked();
    void on_ajouter_clicked();
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
        //void sendDataToArduinonotfound();

        void on_gocalendar_clicked();
        void on_back_fromcalendr_4_clicked();

        void on_calendarWidget_clicked(const QDate &date);
        void updateCalendarAndEventDetails(const QDate &date);
        //void sendDataToArduino(const QString &id, const QString &name);
        //void on_confirm_clicked();




    void on_mody_Button_12_clicked();


private:
    Ui::MainWindow *ui;
    Employe e;
    Arduino *arduino;
    Employe currentEmploye;
    void populateFields();
    QString rfid;  // To store the scanned RFID UID
    void readDataFromArduino();
};

#endif // MAINWINDOW_H
