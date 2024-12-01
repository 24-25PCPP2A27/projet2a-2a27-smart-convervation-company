#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort>
class arduino
{
public:
    arduino();
    ~arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
   QSerialPort* get_serial(){return serial;}
    QString getarduino_port_name(){return arduino_port_name;}
     int show_message_on_lcd(const QString& message);
QString code;
private:
    QSerialPort* serial;
   static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;


};
#endif // ARDUINO_H
