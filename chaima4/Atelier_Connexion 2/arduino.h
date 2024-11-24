#ifndef ARDUINO_H
#define ARDUINO_H

#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QDebug>

class Arduino {
public:
    Arduino();                          // Constructor
    int connect_arduino();              // Method to connect to Arduino
    int close_arduino();                // Method to close connection to Arduino
    int write_arduino(QByteArray data); // Method to write data to Arduino
    QByteArray readFromArduino();       // Method to read data from Arduino
    QSerialPort* getSerial();           // Method to get the serial port instance ( le port usb branché)
    QString getArduinoPortName();        // Method to get the Arduino port name

private:
    QSerialPort* serial;                // Serial port object for communication
    QString arduinoPortName;            // Name of the Arduino's serial port
    bool arduinoIsAvailable;            // Flag indicating if Arduino is available

    static const quint16 arduino_uno_vendor_id = 9025; // Vendor ID for Arduino Uno
    static const quint16 arduino_uno_producy_id = 66;//66   // Product ID for Arduino Uno
    QByteArray data;                    // Data buffer for communication
};

#endif // ARDUINO_H
