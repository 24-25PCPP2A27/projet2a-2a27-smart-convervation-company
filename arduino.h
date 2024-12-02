#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino
{
public:
    Arduino();
    int connect_arduino();  // Permet de connecter le PC à Arduino
    int close_arduino();    // Permet de fermer la connexion
    void write_to_arduino(QByteArray);  // Envoyer des données vers Arduino
    QByteArray read_from_arduino();     // Recevoir des données de la carte Arduino
    QSerialPort* getserial();  // Accesseur pour obtenir l'objet QSerialPort
    QString getarduino_port_name();  // Accesseur pour obtenir le nom du port
private:
    QSerialPort *serial;  // Objet pour gérer la communication série
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;  // Le nom du port série pour Arduino
    bool arduino_is_available;  // Indicateur de disponibilité d'Arduino
    QByteArray data;  // Contient les données lues de l'Arduino
};

#endif // ARDUINO_H

