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
