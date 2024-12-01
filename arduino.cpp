
#include "arduino.h"
#include <QSerialPortInfo>
#include <QDebug>

arduino::arduino() {
    serial = new QSerialPort();
}

arduino::~arduino() {
    if (serial->isOpen())
        serial->close();
    delete serial;
}

int arduino::connect_arduino() {
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }

    qDebug() << "arduino_port_name is:" << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
    }

    return 1;
}

int arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray arduino::read_from_arduino() {
    if (serial->isReadable()) {
        data = serial->readAll();
        return data;
    } else {
        qDebug() << "No data available";
        return QByteArray(); // Valeur par défaut
    }
}

int arduino::write_to_arduino(QByteArray d) {
    if (serial->isWritable()) {
        serial->write(d);
        return 0;
    } else {
        qDebug() << "Unable to write to serial port";
        return 1; // Indique l'échec
    }
}

int arduino::show_message_on_lcd(const QString& message) {
    QByteArray data = message.toUtf8();
    return write_to_arduino(data);
}
