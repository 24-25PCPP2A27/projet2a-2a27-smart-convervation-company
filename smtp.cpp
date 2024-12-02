#include "smtp.h"

Smtp::Smtp(const QString &user, const QString &pass, const QString &host, int port, int timeout, QObject *parent)
    : QObject(parent)
{
    socket = new QSslSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->user = user;
    this->pass = pass;
    this->host = host;
    this->port = port;
    this->timeout = timeout;
}

void Smtp::sendMail(const QString &from,
                    const QString &fromName,
                    const QString &to,
                    const QString &subject,
                    const QString &body)
{
    m_encoding = "UTF-8";
    QString str64;

    // Construct the email message
    message = "";
    str64 = QByteArray().append(fromName).toBase64();
    message.append(QString("From: =?UTF-8?B?%1=?= <%2>\r\n").arg(str64).arg(from));

    str64 = QByteArray().append(subject).toBase64();
    message.append(QString("Subject: =?UTF-8?B?%1=?=\r\n").arg(str64));

    message.append(QString("To: <%1>\r\n").arg(to));

    message.append("Content-Type: text/plain; charset=\"UTF-8\"\r\n");
    message.append("Content-Transfer-Encoding: base64\r\n\r\n");

    str64 = QByteArray().append(body).toBase64();
    message.append(QString("%1\r\n").arg(str64));

    this->from = from;
    this->rcpt = to;
    state = Init;

    // Start the connection
    socket->connectToHostEncrypted(host, port);
    if (!socket->waitForConnected(timeout)) {
        qDebug() << socket->errorString();
    }

    t = new QTextStream(socket);
}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "stateChanged " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " << socketError;
}

void Smtp::disconnected()
{
    qDebug() << "disconnected";
    qDebug() << "error " << socket->errorString();
}

void Smtp::connected()
{
    qDebug() << "Connected";
}

void Smtp::readyRead()
{
    qDebug() << "readyRead";
    QString responseLine;
    do {
        responseLine = socket->readLine();
        response += responseLine;
    } while (socket->canReadLine() && responseLine[3] != ' ');

    responseLine.truncate(3);

    qDebug() << "Server response code:" << responseLine;
    qDebug() << "Server response: " << response;

    if (state == Init && responseLine == "220") {
        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = HandShake;
    } else if (state == HandShake && responseLine == "250") {
        socket->startClientEncryption();
        if (!socket->waitForEncrypted(timeout)) {
            qDebug() << socket->errorString();
            state = Close;
        }

        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = Auth;
    } else if (state == Auth && responseLine == "250") {
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = User;
    } else if (state == User && responseLine == "334") {
        *t << QByteArray().append(user).toBase64() << "\r\n";
        t->flush();
        state = Pass;
    } else if (state == Pass && responseLine == "334") {
        *t << QByteArray().append(pass).toBase64() << "\r\n";
        t->flush();
        state = Mail;
    } else if (state == Mail && responseLine == "235") {
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Rcpt;
    } else if (state == Rcpt && (responseLine == "250" || responseLine == "251")) {
        *t << "RCPT TO:<" << rcpt << ">\r\n";
        t->flush();
        state = Data;
    } else if (state == Data && responseLine == "250") {
        *t << "DATA\r\n";
        t->flush();
        state = Body;
    } else if (state == Body && responseLine == "354") {
        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    } else if (state == Quit && responseLine == "250") {
        *t << "QUIT\r\n";
        t->flush();
        state = Close;
        emit status(tr("Message sent"));
    } else if (state == Close) {
        deleteLater();
        return;
    } else {
        qDebug() << "Unexpected reply from SMTP server:\n\n" << response;
        state = Close;
        emit status(tr("Failed to send message"));
        deleteLater();
        return;
    }
    response = "";
}
