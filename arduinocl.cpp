#include "arduinocl.h"

Arduinoc::Arduinoc() {
    serial = new QSerialPort(); // Create a new QSerialPort instance
    arduinoIsAvailable = false; // Initially, Arduino is not available
}
int Arduinoc::connect_arduino() {
    arduinoPortName = "COM6"; // Force the port to COM6
    serial->setPortName(arduinoPortName);

    // Attempt to open the serial port
    if (serial->open(QSerialPort::ReadWrite)) {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "Successfully connected to Arduino on port: " << arduinoPortName;
        return 0; // Success
    } else {
        qDebug() << "Failed to open serial port " << arduinoPortName << ": " << serial->errorString();
        return 1; // Error opening port
    }
}


int Arduinoc::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Serial port closed.";
        return 0; // Success: Serial port closed
    } else {
        qDebug() << "Serial port is not open.";
        return 1; // Error: Serial port not open
    }
}

int Arduinoc::write_arduino(QByteArray data) {
    if (serial->isOpen()) {
        serial->write(data);
        qDebug() << "Data written to Arduino: " << data;
        return 0; // Success: Data written to Arduino
    } else {
        qDebug() << "Serial port is not open. Cannot write data.";
        return 1; // Error: Serial port not open
    }
}

QByteArray Arduinoc::readFromArduino() {
    QByteArray responseData;

    if (serial->isOpen()) {
        responseData = serial->readAll();
        qDebug() << "Data received from Arduino: " << responseData;
    } else {
        qDebug() << "Serial port is not open. Cannot read data.";
    }

    return responseData;
}

QSerialPort* Arduinoc::getSerial() {
    return serial;
}

QString Arduinoc::getArduinoPortName() {
    return arduinoPortName;
}
