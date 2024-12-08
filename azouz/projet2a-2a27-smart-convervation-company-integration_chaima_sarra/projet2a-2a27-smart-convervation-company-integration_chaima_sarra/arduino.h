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

    bool isAvailable() const;  // Declaration of the method

signals:
    void tagScanned(const QString &uid);



public slots:
    void readData();
    //void writeData(const QByteArray &data);
    int write_arduino(QByteArray data);

private:
    QSerialPort *arduino;
};

#endif // ARDUINO_H
