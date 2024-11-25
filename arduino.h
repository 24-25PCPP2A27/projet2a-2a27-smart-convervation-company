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

private slots:
    void readData();

private:
    QSerialPort *arduino;
};

#endif // ARDUINO_H
