#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    arduino = new QSerialPort(this);

    // Detect available serial ports
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.manufacturer().contains("Arduino") || info.description().contains("Arduino")) {
            arduino->setPort(info);
            break;
        }
    }

    // Configure the serial port if found
    if (!arduino->portName().isEmpty()) {
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

        if (!arduino->open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open serial port:" << arduino->errorString();
        } else {
            connect(arduino, &QSerialPort::readyRead, this, &Arduino::readData);
        }
    }
}

Arduino::~Arduino()
{
    if (arduino->isOpen()) {
        arduino->close();
    }
}

bool Arduino::isAvailable() const
{
    return !arduino->portName().isEmpty();  // Returns true if a valid port is assigned
}
int Arduino::write_arduino(QByteArray data) {
    if (arduino->isOpen()) {
        arduino->write(data);
        qDebug() << "Data written to Arduino: " << data;
        return 0; // Success: Data written to Arduino
    } else {
        qDebug() << "Serial port is not open. Cannot write data.";
        return 1; // Error: Serial port not open
    }
}
void Arduino::readData()
{
    static QString buffer;  // Persistent buffer to store incoming data

    QByteArray data = arduino->readAll();  // Read all available data
    buffer.append(QString(data));  // Append data to the buffer

    // Check if the data ends with a newline (indicates a complete UID)
    if (buffer.endsWith("\n")) {
        buffer = buffer.trimmed();  // Remove extra whitespace and newline
        emit tagScanned(buffer);  // Emit the complete UID
        buffer.clear();  // Clear the buffer for the next read
    }
}

