#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipement.h"  // Include the Equipement class
#include "connection.h"
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb1_clicked();  // Add Equipment
    void on_pb2_clicked();  // Edit Equipment
    void on_pb3_clicked();  // Delete Equipment
    void on_pb_rech_clicked(); // Search by name
    //void on_pb_Export_clicked();
    void on_pb_sortEtat_clicked(); // Sort by state
    //void on_pushButton_Stats_clicked();


    void on_pb_Export_clicked();

    void on_pushButton_Stats_clicked();

    void on_inserer_clicked();

    void on_tableView_clicked(const QModelIndex &index);
    void arduino();

private:
    Ui::MainWindow *ui;
    Equipement Etemp;  // Instance of Equipement to interact with the DB
    class arduino A;
};

#endif // MAINWINDOW_H
