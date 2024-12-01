#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this); // Initialisation de QSerialPort
    portName = "";                  // À configurer automatiquement
    baudRate = QSerialPort::Baud9600; // Vitesse de communication (doit correspondre au code Arduino)
}

Arduino::~Arduino()
{
    if (serial->isOpen()) {
        serial->close();
    }
}

void Arduino::openSerialPort()
{
    // Rechercher tous les ports disponibles et essayer de se connecter
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serial->setPort(info);
        serial->setBaudRate(baudRate);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        // Ouvrir le port série
        if (serial->open(QIODevice::ReadWrite)) {
            portName = info.portName();
            qDebug() << "Port série ouvert: " << portName;
            break;
        }
    }
}

void Arduino::closeSerialPort()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Port série fermé.";
    }
}

void Arduino::sendTemperatureRequest()
{
    // Envoie de la commande 'T' pour demander la température
    if (serial->isOpen()) {
        serial->write("T");
    }
}

void Arduino::readData()
{
    QByteArray data = serial->readAll();
    qDebug() << "Data received: " << data;

    QString temperature = QString::fromUtf8(data).trimmed();
    emit dataReceived(temperature); // Emit the temperature data
}

QString Arduino::getPortName() const
{
    return portName;
}

