#include "arduino.h"

Arduino::Arduino() {
    serial = new QSerialPort(); // Create a new QSerialPort instance
    arduinoIsAvailable = false; // Initially, Arduino is not available
}

int Arduino::connect_arduino() {
    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                // Arduino Uno is found
                arduinoIsAvailable = true;
                arduinoPortName = serial_port_info.portName();
                qDebug() << "Arduino port name is: " << arduinoPortName;

                // Configure the serial port
            }
        }
    }
    if(arduinoIsAvailable){
        serial->setPortName(arduinoPortName);
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
           serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    qDebug() << "Arduino not found.";
    return -1; // Error: Arduino not found
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Serial port closed.";
        return 0; // Success: Serial port closed
    } else {
        qDebug() << "Serial port is not open.";
        return 1; // Error: Serial port not open
    }
}

int Arduino::write_arduino(QByteArray data) {
    if (serial->isOpen()) {
        serial->write(data);
        qDebug() << "Data written to Arduino: " << data;
        return 0; // Success: Data written to Arduino
    } else {
        qDebug() << "Serial port is not open. Cannot write data.";
        return 1; // Error: Serial port not open
    }
}

QByteArray Arduino::readFromArduino() {
    QByteArray responseData;

    if (serial->isOpen()) {
        responseData = serial->readAll();
        qDebug() << "Data received from Arduino: " << responseData;
    } else {
        qDebug() << "Serial port is not open. Cannot read data.";
    }

    return responseData;
}

QSerialPort* Arduino::getSerial() {
    return serial;
}

QString Arduino::getArduinoPortName() {
    return arduinoPortName;
}
