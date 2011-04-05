#ifndef MESSAGE_H
#define MESSAGE_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>
#include <QString>
#include <QMainWindow>
#include <QDialog>
#include <qobject.h>
//you'll need these includes
#include <QFile>
#include <QTextStream>


class Message
{
  //  Q_OBJECT
private:
        QUdpSocket *udpSocket;
        QUdpSocket *udpReceive;
public:
    Message();
    void treceive();
    void tsend(QString);
    int tmp;
};

#endif // MESSAGE_H

