#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino : public QObject
{
    Q_OBJECT
public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();

    void openSerialPort();
    void closeSerialPort();
    void sendTemperatureRequest();
    void readData();
    QString getPortName() const;

    QSerialPort *serial; // Make serial a public member

private:
    QString portName;
    qint32 baudRate;

signals:
    void dataReceived(const QString &temperature); // Signal to notify data reception

};

#endif // ARDUINO_H
