#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret = A.connect_arduino();  // Lancer la connexion à l'Arduino
    switch(ret) {
    case(0): qDebug() << "arduino is available and connected to : " << A.getarduino_port_name(); break;
    case(1): qDebug() << "arduino is available but not connected to :" << A.getarduino_port_name(); break;
    case(-1): qDebug() << "arduino is not available"; break;
    }

    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));  // Connecter le signal readyRead() à update_label()
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data = A.read_from_arduino();

    if (data == "1") {
        ui->label_3->setText("Buzzer ON");  // Si les données reçues sont "1", afficher "Buzzer ON"
    } else if (data == "0") {
        ui->label_3->setText("Buzzer OFF");  // Si les données reçues sont "0", afficher "Buzzer OFF"
    }
}

void MainWindow::on_pushButton_clicked()
{
    A.write_to_arduino("1");  // Envoyer "1" à Arduino pour activer le buzzer
}

void MainWindow::on_pushButton_2_clicked()
{
    A.write_to_arduino("0");  // Envoyer "0" à Arduino pour désactiver le buzzer
}
