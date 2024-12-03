#ifndef BIENVENUE_H
#define BIENVENUE_H

#include <QDialog>
#include "employe.h"
#include <QMainWindow>
#include "arduino.h"
#include "smtp.h"
namespace Ui {
class bienvenue;
}

class bienvenue : public QDialog
{
    Q_OBJECT

public:
    explicit bienvenue( QWidget *parent = nullptr);
    ~bienvenue();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_identifier_cursorPositionChanged(int oldPos, int newPos); // Add this declaratio

    void onTagScanned(const QString &uid);
    void slot_emailStatus(QString message);


    void on_pushButton_3_clicked();

private:
    Ui::bienvenue *ui;
    Arduino *arduino;
    QString rfid;  // To store the scanned RFID UID
    void readDataFromArduino();
    bool checkRfidInDatabase(const QString &uid); // Check if RFID exists in database
    Smtp *m_smtp;
};

#endif // BIENVENUE_H
